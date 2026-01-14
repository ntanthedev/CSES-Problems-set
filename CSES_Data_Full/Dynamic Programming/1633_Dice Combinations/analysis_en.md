# 1633 - Dice Combinations

This problem can be solved with *dynamic programming*.

Let $\mathrm{ways}(n)$ be a function which answers the question "how many ways
are there to land on sum $n$ by throwing a dice zero or more times?"

This is subtly different from the task statement, since it says "one or more
times". These are equivalent for $n \ge 1$, however.

As a base case, we have $\mathrm{ways}(0) = 1$. There is exactly one way to land
on the sum $0$, that is, throwing zero dice.

For higher $n$, we can deduce a recursive relation:

Assume that the first throw results in value $v$ (between 1 and 6). After this,
the process continues as if from the beginning, except $v$ is added to the
total sum. Thus the target sum is now $n-v$, for which the amount of
combinations is given by $\mathrm{ways}(n-v)$.

Accounting for each possible first value $v$, we arrive at

$$\mathrm{ways}(n) = \sum\_{v=1}^{6} \mathrm{ways}(n-v).$$

Note that terms with $n-v<0$ are omitted as these cases
are impossible.

In the solution below, the values of this function are computed iteratively in
increasing order. Each value is computed in constant time by adding together
six other values, so time complexity is $O(n)$.

```cpp
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const int M = 1000000007;

int main() {
    int n;
    cin >> n;

    vector<ll> ways(n + 1);
    ways[0] = 1;
    for (int i = 1; i <= n; ++i) {
        ways[i] = 0;
        for (int v = 1; v <= 6; ++v) {
            if (i - v >= 0) ways[i] += ways[i - v];
        }
        ways[i] %= M;
    }

    cout << ways[n] << "\n";
}
```

## References

* [CPHB (Competitive Programmer's Handbook)](https://cses.fi/book), Chapter 7