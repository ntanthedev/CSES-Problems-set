# 2229 - Permutation Inversions

## Solution 1: $O(n ^ 4)$ approach

We will first present a $O(n^4)$ approach. The approach is a bit too
slow, but it can be easily sped up. Let us use dynamic programming to compute
the answer. Let $\mathrm{dp}[i][j]$ represent the number of permutations of the
numbers $1\ldots i$ with exactly $j$ inversions.

Now, when we are placing the number $i+1$, we have $i+1$ places for it. If we
place the number at the end of the permutation, no new inversion will be formed.
Each place to the left of this will add a new inversion as all numbers are smaller
than the new one.

These observations lead to a solution where we loop through the numbers, the
place for each number and the number of previous inversions. This leads to the
recurrence

$$\mathrm{dp}[i+1][j]=
\sum\_{0 \le \mathrm{pos} \le i}
\mathrm{dp}[i][j-\mathrm{pos}].$$

The table may be filled with this recurrence in $O(n^4)$ time.

```cpp
#include <iostream>
using namespace std;

const int M = 1e9 + 7;
const int N = 501;
const int K = 124751;
int dp[N][K];

int main() {
    int n, k;
    cin >> n >> k;

    dp[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int h = 0; h <= k; ++h) {
            for (int j = 0; j <= min(h, i - 1); ++j) {
                dp[i][h] += dp[i - 1][h - j];
                dp[i][h] %= M;
            }
        }
    }

    cout << dp[n][k] << '\n';
}
```

## Solution 2: $O(n ^ 3)$ approach

Note that the value of each dp position corresponds to a sum of a range of
values from the previous layer. Further, the ranges are all the same length and
their starting positions differ by one. We can, thus, maintain the sum while
filling the dp layer. This leads to a solution with a time complexity of
$O(n^3)$.

```cpp
#include <iostream>
using namespace std;

const int M = 1e9 + 7;
const int N = 501;
const int K = 124751;
int dp[N][K];

int main() {
    int n, k;
    cin >> n >> k;

    dp[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        int sum = 0;
        for (int h = 0; h <= k; ++h) {
            sum += dp[i - 1][h];
            sum %= M;
            if (h >= i) {
                sum -= dp[i - 1][h - i];
                sum += M;
                sum %= M;
            }
            dp[i][h] = sum;
        }
    }

    cout << dp[n][k] << '\n';
}
```