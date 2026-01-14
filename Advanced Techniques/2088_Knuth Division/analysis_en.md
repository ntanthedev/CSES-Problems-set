# 2088 - Knuth Division

We will solve this problem using dynamic programming. If $\mathrm{dp}[l][r]$
represents the cost to divide the subarray $[l, r]$, we will have the following
recurrence

$$\mathrm{dp}[i][j]=
\min\_{i \le k < j}
\mathrm{dp}[i][k]
+\mathrm{dp}[k + 1][j]
+\mathrm{cost}(i, j),$$

where $\mathrm{cost}(i, j)$ represents the cost to split the subarray $[i, j]$,
in this case that is the sum of the subarray. Filling the dynamic programming
table according to this rule would result in an algorithm with a time complexity
of $O(n ^ 3)$ which is too slow.

To speed up the solution, we will use a dynamic programming optimization called
*Knuth's optimization*. The optimization is applicable to any recurrence similar
to the above one if the cost function satisfies these two inequalities:

$$\begin{align\*}
\mathrm{cost}(b, c) &\le
\mathrm{cost}(a, d) \\
\mathrm{cost}(a, c)
+\mathrm{cost}(b, d)
&\le
\mathrm{cost}(a, d)
+\mathrm{cost}(b, c)
\end{align\*}$$

for all $a \le b \le c \le d$.

Let $\mathrm{pos}(i, j)$ denote the $k$ that minimizes the original recurrence,
for $i$ and $j$. We know that, if the above inequalities hold,

$$\mathrm{pos}(i, j - 1) \le \mathrm{pos}(i, j) \le \mathrm{pos}(i + 1, j).$$

This allows us to fill the DP table efficiently. Let us process the subarrays in
increasing order of their length. Now, when we are processing the subarray $[i,
j]$, we have already computed the answer for the arrays $[i, j - 1]$ and $[i +
1, j]$ and thus we know their $\mathrm{pos}$-values. The $\mathrm{pos}$-values
of the previous length are increasing when sorted by the starting index. This
means that they divide the search space for the next $\mathrm{pos}$-values into
disjoint intervals, which allows us to fill each layer in $O(n)$ time, making
the total time complexity of the solution $O(n^2)$.

```cpp
#include <iostream>
using namespace std;
using ll = long long;
const ll INF = 1e18;

const int N = 5000;
int x[N], pos[N][N];
ll s[N + 1], dp[N][N];

int main() {
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> x[i];
        s[i + 1] = s[i] + x[i];
        dp[i][i] = 0;
        pos[i][i] = i + 1;
    }

    for (int len = 2; len <= n; ++len) {
        for (int l = 0; l <= n - len; ++l) {
            int r = l + len - 1;
            dp[l][r] = INF;
            for (int p = pos[l][r - 1]; p <= pos[l + 1][r]; ++p) {
                ll off = dp[l][p - 1] + dp[p][r] + (s[r + 1] - s[l]);
                if (off < dp[l][r]) {
                    dp[l][r] = off;
                    pos[l][r] = p;
                }
            }
        }
    }

    cout << dp[0][n - 1] << endl;
}
```