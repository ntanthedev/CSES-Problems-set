# 1673 - High Score

We start by modifying the problem statement slightly: Instead of maximizing
the score, we first negate the scores and then attempt to minimize the total
score. We also remove all the rooms from the game that cannot be reached from
node $1$ or from which node $n$ cannot be reached. This is done by running
breadth-first search twice, from node $1$ and from node $n$, and storing the
remaining nodes in the `included` bitset.

After that, we run the Bellman-Ford algorithm for $n$ iterations to find the
shortest path from node $1$ to node $n$. If none of the distances decrease on
the $n$th iteration we can negate the distance from node $1$ to node $n$, print
it and exit. Otherwise we know that the graph contains a negative cycle.

Because of how we modified the graph in the beginning, we know that we can
reach the negative cycle from node $1$, use the cycle to make the score
arbitrarily small, and then continue to node $n$. Therefore detecting a negative
cycle means that we can make the score arbitrarily small.

The preprocessing takes $O(n + m)$ time and the time complexity
of the Bellman-Ford algorithm is $O(nm)$.

```cpp
#include <bitset>
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>
using namespace std;
using ll = long long;
const ll INF = 1e18;
const int N = 2501;

bitset<N> bfs(int s, vector<vector<int>>& g) {
    bitset<N> visited;
    queue<int> q;
    q.push(s);
    visited[s] = true;
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int y : g[x]) {
            if (!visited[y]) {
                visited[y] = true;
                q.push(y);
            }
        }
    }
    return visited;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<tuple<int, int, int>> edges;
    vector<vector<int>> g(n + 1);
    vector<vector<int>> rev_g(n + 1);

    for (int i = 1; i <= m; ++i) {
        int a, b, x;
        cin >> a >> b >> x;
        edges.emplace_back(a, b, -x);
        g[a].push_back(b);
        rev_g[b].push_back(a);
    }

    auto included = bfs(1, g) & bfs(n, rev_g);

    vector<ll> distance(n + 1, INF);
    distance[1] = 0;

    for (int i = 1; i <= n; ++i) {
        for (auto [from, to, score] : edges) {
            if (!included[from] || !included[to]) continue;
            ll new_distance = min(distance[to], distance[from] + score);
            if (i == n && new_distance < distance[to]) {
                cout << -1 << '\n';
                return 0;
            }
            distance[to] = new_distance;
        }
    }
    cout << -distance[n] << '\n';
}
```

## References

* [CPHB (Competitive Programmer's Handbook)](https://cses.fi/book), Chapter 7.3.1, Bellman-Ford Algorithm