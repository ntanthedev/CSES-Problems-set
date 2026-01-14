# 1653 - Elevator Rides

## Faulty greedy approaches

Initially it might seem that a greedy approach could solve the problem: choose
people into one elevator ride as long as someone fits. However, no simple way
of choosing the next person is known that would work optimally in all cases.

For example, consider the input

$$\begin{align\*}
x &= 8 \\
w &= 4, 3, 3, 2, 2, 2.
\end{align\*}$$

Neither a strategy which always chooses the heaviest person that still fits in
the elevator, nor one that chooses the lightest, are able to find the optimal
solution, which is two full elevators:

$$(4, 2, 2), (3, 3, 2)$$

## Permutations

Iterating through all permutations of people suffices to solve the problem. The
idea is to add people to the elevator one by one as long as the next person
fits, and starting a new ride otherwise. Any elevator assignment will correspond
to some permutation from which the solution can be reconstructed.

There are at most $20! \approx 10^{18}$ different permutations, so each one of
them cannot be checked individually. The idea can be optimized by instead
doing dynamic programming over subsets of people, also called bitmask dynamic
programming.

## Permutations to subsets

When choosing people one by one, the only information that needs to be
considered is the *subset* of people that have already been assigned elevator
rides. The order in which the previous people were chosen does not matter as
long as it is optimal.

Let the function $\mathrm{best}$ have values of the form $\mathrm{best}(S) =
(r, l)$ where the pair $(r, l)$ describes the optimal number of elevator rides
$r$ and weight already used from the last ride $l$ for any subset $S$ of
people. Among solutions with the same amount of rides, the one with the least
$l$ is considered better.

The function can be computed recursively by individually trying each person
in the subset as the last person to be considered.

$$\mathrm{best}(S) = \min\_{p\in S} \mathrm{add}(\mathrm{best}(S \setminus \{p\}), w\_p)$$

Here, $\mathrm{add}((r, l), w\_p)$ tries to add the person $p$ into the last
elevator ride as $(r, l + w\_p)$, or establishes a new one as $(r+1, w\_p)$
if $l + w\_p > x$.

We set $\mathrm{best}(\emptyset)=(1, 0)$ as the base case to make the rest of
the values correct even though zero rides are technically needed.

It would be possible to make the amount of elevator rides a variable of the
function, as $\mathrm{best}(S, r) = l$, and minimize only the total weight of
the last elevator ride. However, this is not necessary because there is never
any ambiguity comparing pairs $(r, l)$. That is, a pair with less rides is
always strictly better than one with more. This allows us to find the optimal
pair much like a single number can be optimized with dynamic programming. In
fact, the default comparison operators for `std::pair` work in the correct way.

The subset $S$ is conveniently represented as a bitmask in the solution below.
Iterating over the bitmasks in the order corresponding to their numeric values
guarantees that all smaller subsets are computed before the current one. The
solution has a time complexity of $O(n 2^n)$.

```cpp
#include <iostream>
#include <vector>
using namespace std;

const int N = 20;
pair<int, int> best[1 << N];

int main() {
    int n, x;
    cin >> n >> x;

    vector<int> w(n);
    for (int i = 0; i < n; ++i) cin >> w[i];

    best[0] = {1, 0};
    for (int s = 1; s < (1 << n); ++s) {
        best[s] = {n + 1, 0};

        for (int p = 0; p < n; ++p) {
            if (s & (1 << p)) {
                auto [r, l] = best[s ^ (1 << p)];
                pair<int, int> added;
                if (l + w[p] <= x) {
                    added = {r, l + w[p]};
                } else {
                    added = {r + 1, w[p]};
                }
                best[s] = min(best[s], added);
            }
        }
    }

    cout << best[(1 << n) - 1].first << endl;
}
```

## References

* [CPHB (Competitive Programmer's Handbook)](https://cses.fi/book), Chapter 10,
  From permutations to subsets