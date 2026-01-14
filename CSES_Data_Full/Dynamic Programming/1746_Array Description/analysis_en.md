# 1746 - Array Description

This problem can be solved with dynamic programming. Let $\mathrm{count}(i, j)$
count the valid combinations for values in the array at indices $1,\dots,i$,
such that the last of them, at index $i$, is equal to $j$.

Let us define $\mathrm{count}(1, j)$ as a base case: If $x\_1 = 0$,
then all values $1 \le j \le m$ are possible. Otherwise only $j = x\_1$ is
possible.

$$\mathrm{count}(1, j) =
\begin{cases}
1 & \text{if } x\_1 = 0 \text{ or } x\_1 = j \\
0 & \text{otherwise}
\end{cases}$$

Assuming that the array is valid up to the index $i-1$, it is enough to ensure
that the values at indices $i-1$ and $i$ have absolute difference at most one.
The amount of combinations is set to zero if $j$ does not match the description.

$$\mathrm{count}(i, j) =
\begin{cases}
{ \displaystyle \small \sum\_{k=-1}^{1} } \mathrm{count}(i-1, j+k)
& \text{if } x\_i = 0 \text{ or } x\_i = j \\
0 & \text{otherwise}
\end{cases}$$

This makes for a time complexity of $O(nm)$.

In the implementation below, the dynamic programming array is padded with zeros
at `count[i][0]` and `count[i][m + 1]` to avoid going out of bounds.

```cpp
#include <iostream>
#include <vector>
using namespace std;
const int M = 1000000007;
const int N = 100001;

int count[N][102];

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> x(n + 1);
    for (int i = 1; i <= n; ++i) cin >> x[i];

    for (int j = 1; j <= m; ++j) {
        if (x[1] == 0 || x[1] == j) {
            count[1][j] = 1;
        }
    }
    for (int i = 2; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (x[i] == 0 || x[i] == j) {
                for (int k = -1; k <= 1; ++k) {
                    count[i][j] = (count[i][j] + count[i - 1][j + k]) % M;
                }
            }
        }
    }

    int result = 0;
    for (int j = 1; j <= m; ++j) {
        result = (result + count[n][j]) % M;
    }
    cout << result << "\n";
}
```