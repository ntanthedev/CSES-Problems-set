# 2087 - Houses and Schools

There are a few different approaches to this problem. Most of them will have a
dynamic programming table similar to the following one:

$$\mathrm{dp}[j][i], 1 \le j \le k, 1 \le i \le n$$

denotes the minimum
possible sum of walking distances for the first $i$ children provided there are
$j$ schools with the last of them at index $i$.

We will use $\mathrm{cost}(i, j)$ to denote the sum of walking distances for the
children in houses from $i$ to $j$, provided that there are schools in houses
$i$ and $j$. Simply filling this table according to the recurrence

$$\mathrm{dp}[j][i] = \min\_{p < i} \mathrm{dp}[j - 1][p] + \mathrm{cost}(p, i)$$

would result in an algorithm with a time complexity of $O(n^2k)$. This may be
sped up with a DP optimization called *divide and conquer*. It can be applied
only if the $\mathrm{cost}$ function satisfies the *quadrangle inequality*

$$\mathrm{cost}(a, c) + \mathrm{cost}(b, d)
\le
\mathrm{cost}(a, d) + \mathrm{cost}(b, c)$$

for all $a \le b \le c \le d$. It may be proven that our $\mathrm{cost}$
function (the sum of walking distances between schools) satisfies the
inequality.

Let $\mathrm{pos}\_j(i)$ denote the minimum position $p$ that minimizes the value
of

$$\min\_{p < i} \mathrm{dp}[j - 1][p] + \mathrm{cost}(p, i).$$

It may be proven that if the quadrangle inequality holds, then
$\mathrm{pos}\_j(i)$ forms an increasing sequence for all $i$, i.e.
$\mathrm{pos}\_j(i) \le \mathrm{pos}\_j(i + 1)$. This fact allows us to make a
recursive function that fills one layer of the dp table, for a fixed $j$.

The idea is to start with a search range of $[0, n)$, and at each step, split
the range in half and recursively process the two parts. The range $[i, j)$ becomes
$[i, m)$ and $[m, r)$, where $m$ denotes the midpoint of the range $m=\lfloor
\frac {l+r} {2} \rfloor$. Then, if we are able to find $\mathrm{dp}[j][m]$ and
thus, $\mathrm{pos}\_j(m)$, we know that $\mathrm{pos}\_j(i) \le
\mathrm{pos}\_j(m)$, for all $i < m$ and $\mathrm{pos}\_j(m) \le
\mathrm{pos}\_j(i)$, for all $m < i$. This allows us to reduce the search space
for $p$ in the subsequent calls, making the time complexity of filling a dp
layer $O(n\log n)$ and the total time complexity $O(nk\log n)$.

There are more advanced solutions to this problem, for example, using a
technique called the *aliens trick* combined with the *convex hull trick*.

```cpp
#include <iostream>
using namespace std;
using ll = long long;

const ll INF = 1e18;
const int N = 3000;

int c[N];
ll lcost[N][N];
ll rcost[N][N];

ll left_cost(int l, int r) {
    return l <= r ? lcost[l][r] : 0;
}
ll right_cost(int l, int r) {
    return l <= r ? rcost[l][r] : 0;
}

ll cost(int l, int r) {
    int mid = (l + r) / 2;
    return left_cost(l, mid) + right_cost(mid + 1, r);
}

ll dp[N][N];

void recurse(int lvl, int l, int r, int pos_l, int pos_r) {
    if (l > r) return;

    int mid = (l + r) / 2;
    ll best = INF;
    int pos = l;

    for (int k = pos_l; k <= min(mid, pos_r); k++) {
        ll offer = dp[lvl - 1][k] + cost(k, mid);
        if (offer < best) {
            best = offer;
            pos = k;
        }
    }

    dp[lvl][mid] = best;

    recurse(lvl, l, mid - 1, pos_l, pos);
    recurse(lvl, mid + 1, r, pos, pos_r);
}

int main() {
    int n, k;
    cin >> n >> k;

    for (int i = 0; i < n; ++i) {
        cin >> c[i];
    }

    for (int i = 0; i < n; ++i) {
        ll s = 0;
        for (int j = i; j < n; ++j) {
            s += ll(j - i) * c[j];
            lcost[i][j] = s;
        }
    }

    for (int i = 0; i < n; ++i) {
        ll s = 0;
        for (int j = i; j >= 0; --j) {
            s += ll(i - j) * c[j];
            rcost[j][i] = s;
        }
    }

    for (int i = 0; i < n; ++i) {
        dp[0][i] = right_cost(0, i);
    }

    for (int i = 1; i < k; ++i) {
        recurse(i, 0, n, 0, n);
    }

    ll ans = INF;
    for (int i = 0; i < n; ++i) {
        ans = min(ans, dp[k - 1][i] + left_cost(i, n - 1));
    }

    cout << ans << '\n';
}
```