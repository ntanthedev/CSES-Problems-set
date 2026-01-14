# 1197 - Cycle Finding

We solve the problem with the Bellman-Ford algorithm in $O(nm)$ time.

As we are only interested in finding a negative cycle, we initialize
the $\mathrm{distance}$ array used in Bellman-Ford with zeros.
We also associate with each node $x$ the previous
node on the shortest path to $x$ and store it in the $\mathrm{previous}$ array.

We run $n$ rounds of the Bellman-Ford algorithm. If the $\mathrm{distance}$
array is not modified on the $n$th round, the graph does not contain a
negative cycle. Otherwise the graph contains a negative cycle.

To construct the negative cycle, we start by choosing some node $x\_1$
for which $\mathrm{distance}[x\_1]$ was updated during the $n$th round.
We then form a path $x\_1, x\_2, \dots$ by setting
$x\_{i+1} = \mathrm{previous}[x\_i]$ and extract the negative cycle from
this path.

Let us first show that the path contains a cycle.
As $\mathrm{distance}[x\_1]$ was updated during round $n$,
we know that node $x\_2=\mathrm{previous}[x\_1]$ exists and
$\mathrm{distance}[x\_2]$ was updated during round $n-1$ or later.
Using induction, we can show that node $x\_{n+1}$ exists.
The graph consists of $n$ nodes, so there has to be a cycle.

Let us then focus on the cycle $y\_1, \dots y\_k$, where $y\_1 = y\_k$ and
$y\_{i+1} = \mathrm{previous}[y\_i]$.
We denote the edge lengths in the cycle by $c\_1, \dots, c\_{k-1}$
where $c\_i$ corresponds to the edge from $y\_{i+1}$ to $y\_i$.
We know that
$$\mathrm{distance}[y\_{i+1}] + c\_i \le \mathrm{distance}[y\_i]$$
in all cycle nodes. In addition, let $y\_a$ denote the node whose
distance has been updated most recently in the cycle.
Since $\mathrm{distance}[y\_a]$ decreased last,
we get a stronger bound on the preceding edge
(wrapping to the end of the cycle if necessary),
$$\mathrm{distance}[y\_a] + c\_{a-1} < \mathrm{distance}[y\_{a-1}].$$

This yields
$$\sum\_{i=1}^{k-1} c\_i < \sum\_{i=1}^{k-1} \mathrm{distance}[y\_{i}] -
\mathrm{distance}[y\_{i+1}] = 0$$
which shows that the cycle length is negative.

```cpp
#include <algorithm>
#include <iostream>
#include <optional>
#include <tuple>
#include <vector>
using namespace std;
using ll = long long;

int main() {
    int n, m;
    vector<tuple<int, int, int>> edges;

    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        edges.emplace_back(a, b, c);
    }

    vector<ll> distance(n + 1);
    vector<int> previous(n + 1);
    optional<int> path_end;

    for (int i = 1; i <= n; ++i) {
        for (auto [from, to, len] : edges) {
            ll new_distance = distance[from] + len;
            if (new_distance < distance[to]) {
                distance[to] = new_distance;
                previous[to] = from;
                if (i == n) {
                    path_end = to;
                }
            }
        }
    }

    if (!path_end) {
        cout << "NO\n";
        return 0;
    }

    vector<char> visited(n + 1);
    vector<int> path;
    int x = *path_end;
    while (true) {
        path.push_back(x);
        if (visited[x]) break;
        visited[x] = 1;
        x = previous[x];
    }
    reverse(path.begin(), path.end());

    cout << "YES\n";
    for (int i = 0; i < path.size(); ++i) {
        cout << path[i] << ' ';
        if (i > 0 && path[i] == path.front()) break;
    }
    cout << '\n';
}
```

## References

* [CPHB (Competitive Programmer's Handbook)](https://cses.fi/book),
  Chapter 7.3.1, Bellman-Ford Algorithm