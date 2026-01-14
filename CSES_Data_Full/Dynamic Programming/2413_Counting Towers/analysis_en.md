# 2413 - Counting Towers

## Solution 1

To solve this problem using dynamic programming, the choice of *state space* is
not obvious.

For example, using only the height of the tower $n$ as state does not seem
sufficient. A solution could try to split the tower into two pieces with heights
$a+b=n$, but towers which cannot be split also exhibit complex patterns and are
hard to count. This suggests that some more information about the tower needs to
be encoded in the state.

One suitable state space is determined by the height of the tower, and whether
or not the topmost two squares are disjoint. In other words, whether there is a
"line" drawn between the squares.

Let the function $\mathrm{towers}(i, s)$ describe the amount of towers with
height $i$, where $s \in \{ 1, 0 \}$ indicates whether the topmost squares are
disjoint, as $1$, or not, as $0$.

Define towers with height one as base cases: $\mathrm{towers}(1, 1) = 1$ (two
$1 \times 1$ blocks) and $\mathrm{towers}(1, 0) = 1$ (one $2 \times
1$ block).

Now let us explore the *transitions* between states with height $i-1$ and $i$.
How many ways are there to add one layer to a tower in each case, by starting
new blocks or extending existing ones?

![transitions](477c37c3fb6e8fb2dfd150ebfec2dd20337508b3bf25e11b54d9e7cf651ecdac)

The recurrence corresponding to this tabulation is as follows:

$$\begin{align\*}
\mathrm{towers}(i, 1) &=
4\cdot\mathrm{towers}(i-1, 1) + \mathrm{towers}(i-1, 0) \\
\mathrm{towers}(i, 0) &=
\mathrm{towers}(i-1, 1) + 2\cdot\mathrm{towers}(i-1, 0)
\end{align\*}$$

The implementation below precomputes these values for all $i \le 10^6$, so each
test can be answered efficiently.

```cpp
#include <iostream>
using namespace std;
using ll = long long;
const int M = 1000000007;
const int N = 1000001;

ll towers[N][2];

int main() {
    towers[1][1] = 1;
    towers[1][0] = 1;

    for (int i = 2; i < N; ++i) {
        towers[i][1] = (4 * towers[i - 1][1] + towers[i - 1][0]) % M;
        towers[i][0] = (towers[i - 1][1] + 2 * towers[i - 1][0]) % M;
    }

    int t;
    cin >> t;
    for (int ti = 0; ti < t; ++ti) {
        int n;
        cin >> n;
        cout << (towers[n][0] + towers[n][1]) % M << "\n";
    }
}
```

## Solution 2

Despite it seeming challenging, there is an explicit formula for counting towers
which cannot be split further. Such a tower consists of either one $2 \times n$
block or two columns of $1 \times x$ blocks, where block boundaries do not
coincide at any height.

In the latter case, there are three possible configurations at each intermediary
height: neither of the columns have a block boundary, only the left one has a
block boundary, or only the right one has a block boundary. If both columns
had a boundary, the tower could be split at that height.

Let the height of this indivisible tower be $a$. The total amount of
combinations for constructing it is

$$1 + 3^{a-1}.$$

Now we may formulate a recurrence with only one variable. The topmost
indivisible part can have any height $1 \le a \le i$.

$$\mathrm{towers}(i) = \sum\_{a=1}^i (1 + 3^{a-1}) \mathrm{towers}(i-a)$$

We may set $\mathrm{towers}(0) = 1$ to fit the pattern: if $a=i$, then
the part left over has height zero, and this case is valid.

Using this recurrence directly would yield a time complexity of $O(N^2)$,
where $N=10^6$ is the largest $i$ needed. However, the equation can be
simplified.

For brevity, $f(i)$ shall denote the same as $\mathrm{towers}(i)$.

$$f(i) = \sum\_{a=1}^i (1 + 3^{a-1}) f(i-a)
\tag{1}$$

Observe that the first term is $(1 + 3^0) f(i-1) = 2f(i-1)$. It can be moved
to the left side of the equation.

$$f(i) - 2f(i-1) = \sum\_{a=2}^i (1 + 3^{a-1}) f(i-a)$$

The powers of three may be canceled by subtracting $3f(i-1)$ on both sides,
substituting $i-1$ for $i$ in equation (1).

$$\begin{align\*}
f(i) - 5f(i-1) &= \sum\_{a=2}^i (1 + 3^{a-1} - 3(1 + 3^{a-2})) f(i-a) \\
&= \sum\_{a=2}^i (1 + 3^{a-1} - 3 - 3\cdot3^{a-2}) f(i-a) \\
&= \sum\_{a=2}^i (1 + 3^{a-1} - 3 - 3^{a-1}) f(i-a) \\
&= -2 \sum\_{a=2}^i f(i-a)
\tag{2}
\end{align\*}$$

Finally, subtract $f(i-1)-5f(i-2)$ on both sides according to equation (2).

$$\begin{align\*}
f(i) - 6f(i-1) + 5f(i-2) &= -2 \sum\_{a=2}^i f(i-a) +2 \sum\_{a=2}^{i-1} f(i-1-a) \\
&= -2\sum\_{a=2}^i f(i-a) +2 \sum\_{a=3}^i f(i-a) \\
&= -2 f(i-2)
\end{align\*}$$

Rearrange to find

$$f(i) = 6f(i-1) - 7f(i-2).$$

```cpp
#include <iostream>
using namespace std;
using ll = long long;
const int M = 1000000007;
const int N = 1000001;

ll towers[N];

int main() {
    towers[0] = 1;
    towers[1] = 2;

    for (int i = 2; i < N; ++i) {
        towers[i] = (6 * towers[i - 1] + (M - 7) * towers[i - 2]) % M;
    }

    int t;
    cin >> t;
    for (int ti = 0; ti < t; ++ti) {
        int n;
        cin >> n;
        cout << towers[n] << "\n";
    }
}
```

## References

* [The On-Line Encyclopedia of Integer Sequences, A034999](http://oeis.org/A034999)