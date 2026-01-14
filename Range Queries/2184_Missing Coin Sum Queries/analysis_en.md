# 2184 - Missing Coin Sum Queries

We process each query in $B$ steps where $B=\lfloor \log\_2 10^9 \rfloor = 30$.
In each step, $b=0,1,\dots,B-1$, we consider all coins in the query range
such that the most significant bit of the coin value is in position $b$.

For each query $i$, we maintain a value $\textrm{result}[i]$,
which indicates that we can produce all coin sums
between $1$ and $\textrm{result}[i]$ using the coins.
Initially $\textrm{result}[i]=0$ for each $i=1,2,\dots,q$.

In each step, we update the result for each query.
Let $\textrm{sum}(i,b)$ and $\textrm{min}(i,b)$
denote the sum and minimum of coin values in the range of query $i$
whose most significant bit is in position $b$.
Always when $\textrm{min}(i,b) \le \textrm{result}[i]+1$,
we can extend the range of possible sums
by adding $\textrm{sum}(i,b)$ to $\textrm{result}[i]$.
Finally, $\textrm{result}[i]+1$ is the smallest missing coin sum.

We use data structures for efficient range sum and range minimum queries.
Using these data structures,
we can process range sum queries in $O(1)$ time after $O(n)$ time preprocessing
and range minimum queries in $O(1)$ time after $O(n \log n)$ time preprocessing.

The resulting algorithm works in $O(B(n \log n + q))$ time.

```cpp
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

const int INF = 1e9 + 1;
const int B = 30;
const int K = 18;

int main() {
    int n, q;
    cin >> n >> q;

    vector<int> x(n + 1);
    vector<int> bit(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> x[i];
        bit[i] = 31 - __builtin_clz(x[i]);
    }

    vector<pair<int, int>> query(q + 1);
    for (int i = 1; i <= q; i++) {
        cin >> query[i].first >> query[i].second;
    }

    vector<ll> result(q + 1);
    vector<ll> sumq(n + 1);
    vector<vector<int>> minq(K, vector<int>(n + 1));

    for (int b = 0; b < B; b++) {
        for (int i = 1; i <= n; i++) {
            sumq[i] = sumq[i - 1];
            if (bit[i] == b) {
                sumq[i] += x[i];
            }
        }

        for (int i = 1; i <= n; i++) {
            minq[0][i] = bit[i] == b ? x[i] : INF;
        }
        for (int k = 1; k < K; k++) {
            for (int i = 1; i <= n - (1 << (k - 1)); i++) {
                minq[k][i] =
                    min(minq[k - 1][i], minq[k - 1][i + (1 << (k - 1))]);
            }
        }

        for (int i = 1; i <= q; i++) {
            auto [a, b] = query[i];
            int level = 31 - __builtin_clz(b - a + 1);
            int min_x = min(minq[level][a], minq[level][b - (1 << level) + 1]);
            if (min_x <= result[i] + 1) {
                result[i] += sumq[b] - sumq[a - 1];
            }
        }
    }

    for (int i = 1; i <= q; i++) {
        cout << result[i] + 1 << "\n";
    }
}
```