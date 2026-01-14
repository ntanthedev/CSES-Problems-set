# 1672 - Shortest Routes II

To solve the problem, we use the Floyd-Warshall algorithm.
We find the shortest distances between all pairs of cities and store
these in the `dist` array. We can then answer the queries
by printing the corresponding values in the `dist` array.

The time complexity of the Floyd-Warshall algorithm is $O(n^3)$ and
answering the queries takes $O(q)$ time.

```cpp
#include <iostream>
using namespace std;
using ll = long long;
const int N = 501;
const ll INF = 1e18;
ll dist[N][N];

int main() {
    int n, m, q;
    cin >> n >> m >> q;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            dist[i][j] = i == j ? 0 : INF;
        }
    }
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        dist[a][b] = min(dist[a][b], (ll)c);
        dist[b][a] = min(dist[b][a], (ll)c);
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            for (int k = 1; k <= n; ++k) {
                dist[j][k] = min(dist[j][k], dist[j][i] + dist[i][k]);
            }
        }
    }

    for (int i = 0; i < q; ++i) {
        int a, b;
        cin >> a >> b;
        if (dist[a][b] == INF) {
            cout << -1 << '\n';
        } else {
            cout << dist[a][b] << '\n';
        }
    }
}
```

## References

* [CPHB (Competitive Programmer's Handbook)](https://cses.fi/book), Chapter 7.3.3, Floyd-Warshall Algorithm