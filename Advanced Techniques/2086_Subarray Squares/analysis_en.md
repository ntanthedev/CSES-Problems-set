# 2086 - Subarray Squares

We will solve this problem using dynamic programming. We will have a dp table,
where $\mathrm{dp}[j][i]$ refers to the minimum price to divide the first $i$
elements into $j$ subarrays, the last of which ends at $i$.

We will fill the table according to the recurrence

$$\mathrm{dp}[j][i] =
\min\_{k< i}\mathrm{dp}[j-1][k]+(x\_k+x\_{k+1}+\dots+x\_{i-1})^2.$$

If we build a prefix sum array $\mathrm{sum}$, where $\mathrm{sum}[i]$ refers
to the sum of the first $i$ elements, the recurrence turns into

$$\mathrm{dp}[j][i] =
\min\_{k < i}\mathrm{dp}[j-1][k]+(\mathrm{sum}[i]-\mathrm{sum}[k-1])^2.$$

Note that if we expand the expression

$$(\mathrm{sum}[i]-\mathrm{sum}[k-1])^2=
\mathrm{sum}[i]^2
-2\cdot\mathrm{sum}[i]\cdot\mathrm{sum}[k-1]
+\mathrm{sum}[k-1]^2,$$

we may rearrange the recurrence into

$$\mathrm{dp}[j][i] =\mathrm{sum}[i]^2+
\min\_{k < i}\mathrm{dp}[j-1][k]
-2\cdot\mathrm{sum}[i]\cdot\mathrm{sum}[k-1]
+\mathrm{sum}[k-1]^2.$$

Now, each previous position $k < i$ can be thought of as a line

$$y\_k=x\cdot
(-2\cdot\mathrm{sum}[k-1])
+\mathrm{dp}[j-1][k]
+\mathrm{sum}[k-1]^2,$$

and we are asked to find the minimum height of a line at position
$x = \mathrm{sum}[i]$.

A technique known as the *convex hull trick* does exactly this. As the sequence
of slopes ($-2\cdot\mathrm{sum}[k-1]$) is decreasing, we only need to maintain a
stack of lines. Furthermore, as the sequence of query points ($\mathrm{sum}[i]$)
is increasing, we can maintain a pointer to the array and find the answer to
each query with an amortized cost of $O(1)$.

Note that, at all times, we are using only the two latest layers of the dp
table. For this reason, it suffices to store only two arrays, representing the
last two layers.

This approach fills each layer in linear time and thus has a time complexity of
$O(nk)$. It is possible to solve the problem even quicker, using a
techinique known as the *Aliens trick* (linked below).

## References

* [CP-Algorithms, *Convex Hull Trick*](https://cp-algorithms.com/geometry/convex_hull_trick.html)
* [serbanology.com, *The Trick From Aliens*](http://www.serbanology.com/article/The%20Trick%20From%20Aliens)

```cpp
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const ll INF = 1e18;

struct Line {
    ll a, b;  // Represents the line y = ax + b
    // Returns the height of the line at x.
    ll operator()(ll x) { return a * x + b; }
};

int main() {
    int n, k;
    cin >> n >> k;

    vector<int> x(n);
    vector<ll> sum(n + 1);
    for (int i = 0; i < n; ++i) {
        cin >> x[i];
        sum[i + 1] = sum[i] + x[i];
    }

    vector<ll> dp(n + 1, INF);
    dp[0] = 0;

    for (int i = 0; i < k; ++i) {
        vector<Line> lines;
        int pos = 0;  // Stores the index of the current lowest line.

        // Finds the height of the lowest line at position x.
        // Assumes that the sequence of x's is increasing.
        auto get_best = [&](ll x) {
            while (pos + 1 < size(lines) && lines[pos + 1](x) < lines[pos](x)) {
                pos++;
            }
            return lines[pos](x);
        };

        vector<ll> ndp(n + 1);
        for (int j = i; j <= n; ++j) {
            if (j != i) {
                ndp[j] = sum[j] * sum[j] + get_best(sum[j]);
            }
            Line l = {-2 * sum[j], dp[j] + sum[j] * sum[j]};
            while (lines.size() > 1) {
                auto a = lines[lines.size() - 2];
                auto b = lines[lines.size() - 1];
                if ((l.b - a.b) * (a.a - b.a) <= (b.b - a.b) * (a.a - l.a)) {
                    lines.pop_back();
                } else {
                    break;
                }
            }
            lines.push_back(l);
        }
        swap(dp, ndp);
    }
    cout << dp[n] << '\n';
}
```