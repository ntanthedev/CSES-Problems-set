# 1636 - Coin Combinations II

For this problem it is helpful to consider a function of two variables which
counts possible *sequences* of coins.

Notice that the coins do not necessarily need to be sorted numerically. The
order in which they appear in the input suffices. Put another way, it may be
assumed that $c\_1 < c\_2 < \cdots < c\_n$.

Let $\mathrm{ways}(x, j)$ be the amount of distinct sorted sequences that sum
to $x$, containing nothing outside of the first $j$ coins, i.e.
$c\_1, c\_2, \ldots, c\_j$.

The answer to the problem can be read from $\mathrm{ways}(x, n)$, where all
coins are available.

When no coin can be used, the only possible sum is $0$:

$$\mathrm{ways}(x, 0) =
\begin{cases}
1 & \text{if } x=0 \\
0 & \text{otherwise}
\end{cases}$$

In the general case of $\mathrm{ways}(x, j)$, consider the last coin in the
sequence. Coins with value $c\_j$ should be sorted to the end, so either the
last coin is $c\_j$ or the sequence contains none of them.

In the latter case, the wanted amount of sequences is given by
$\mathrm{ways}(x, j-1)$.

$$\mathrm{ways}(x, j) = \mathrm{ways}(x-c\_j, j) + \mathrm{ways}(x, j-1)$$

While the two dimensional array with size $n \times (x+1)$ would narrowly fit
inside the memory limit, it is actually not necessary. By iterating over the
different coins in an outer for loop, the intermediary results can all be
stored in the same array of size $x+1$.

```cpp
#include <iostream>
#include <vector>
using namespace std;
const int M = 1000000007;

int main() {
    int n, x;
    cin >> n >> x;

    vector<int> c(n);
    for (int j = 0; j < n; ++j) {
        cin >> c[j];
    }

    vector<int> ways(x + 1);
    ways[0] = 1;
    for (int j = 0; j < n; ++j) {
        for (int i = c[j]; i <= x; ++i) {
            ways[i] = (ways[i - c[j]] + ways[i]) % M;
        }
    }

    cout << ways[x] << "\n";
}
```