# 1694 - Download Speed

## Solution 1: Scaling algorithm

This algorithm, sometimes known as the *Scaling algorithm*, calculates the
maximum flow in a graph. It uses the same ideas as the Ford-Fulkerson algorithm,
except that it uses depth-first search for finding augmenting paths where each
edge weight is larger than a threshold value.

Initially the threshold value $C$ is chosen as a large number, for example, the
maximum edge weight of the graph. Then, the algorithm will run $O(\log C)$
phases after each of which the threshold value is halved. The algorithm has a
running time of $O(m^2\log C)$.

The two flow algorithms shown here are given as black boxes: they are complete
implementations which can be easily used in other problems. Most of the time,
there is no need to modify the algorithms.

```cpp
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

// Scaling algorithm for computing the maximum flow in a flow network.
// Runs in O(m^2 log C) time.
struct MaxFlow {
    static const ll INF = 1e18;

    struct Edge {
        int from;
        int to;
        ll w;
    };

    int n, source, sink;
    vector<vector<int>> g;
    vector<Edge> edges;
    vector<bool> seen;
    ll flow = 0;

    MaxFlow(int n, int source, int sink)
        : n(n), source(source), sink(sink), g(n) {}

    int add_edge(int from, int to, ll forward, ll backward = 0) {
        const int id = (int)edges.size();
        g[from].emplace_back(id);
        edges.push_back({from, to, forward});
        g[to].emplace_back(id + 1);
        edges.push_back({to, from, backward});
        return id;
    }

    bool dfs(int node, ll lim) {
        if (node == sink) return true;
        if (seen[node]) return false;
        seen[node] = true;
        for (int i : g[node]) {
            auto &e = edges[i];
            auto &back = edges[i ^ 1];
            if (e.w >= lim) {
                if (dfs(e.to, lim)) {
                    e.w -= lim;
                    back.w += lim;
                    return true;
                }
            }
        }
        return false;
    }

    ll max_flow() {
        for (ll bit = 1ll << 62; bit > 0; bit /= 2) {
            bool found = false;
            do {
                seen.assign(n, false);
                found = dfs(source, bit);
                flow += bit * found;
            } while (found);
        }
        return flow;
    }
};

int main() {
    int n, m;
    cin >> n >> m;

    MaxFlow flow(n, 0, n - 1);
    for (int i = 0; i < m; ++i) {
        int a, b, w;
        cin >> a >> b >> w;
        a--;
        b--;
        flow.add_edge(a, b, w, 0);
    }

    cout << flow.max_flow() << '\n';
}
```

## Solution 2: Dinic's algorithm

Dinic's algorithm was conceived by Yefim A. Dinitz and is based on the ideas of
the Edmonds-Karp algorithm. Dinic's algorithm, however, uses a few optimizations
to reduce the time complexity to $O(n^2\cdot m)$ when there are $n$ nodes and
$m$ edges.

There are a few cases where Dinic's algorithm has a better time complexity than
$O(n^2\cdot m)$. One of them is bipartite matching which the algorithm is able
to solve in $O(\sqrt{n}m)$. It turns out that this bound holds in any unit
network, where the incoming or outgoing capacity of each node is at most $1$.

These bounds make Dinic's algorithm fast enough for most flow problems in
competitive programming.

```cpp
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
using ll = long long;

// Dinic's algorithm for computing the maximum flow in a flow network.
// Runs in O(m n^2) time.
struct MaxFlow {
    static const ll INF = 1e18;

    struct Edge {
        int from;
        int to;
        ll w;
    };

    int n, source, sink;
    vector<vector<int>> g;
    vector<Edge> edges;
    vector<int> level;
    vector<int> ptr;
    ll flow = 0;

    MaxFlow(int n, int source, int sink)
        : n(n), source(source), sink(sink), g(n), level(n), ptr(n) {}

    int add_edge(int from, int to, ll forward, ll backward = 0) {
        const int id = (int)edges.size();
        g[from].emplace_back(id);
        edges.push_back({from, to, forward});
        g[to].emplace_back(id + 1);
        edges.push_back({to, from, backward});
        return id;
    }

    bool bfs() {
        level.assign(n, -1);
        queue<int> q;
        q.push(source);
        level[source] = 0;
        while (!q.empty()) {
            int s = q.front();
            q.pop();
            for (int i : g[s]) {
                auto &e = edges[i];
                if (level[e.to] == -1 && e.w > 0) {
                    level[e.to] = level[s] + 1;
                    q.push(e.to);
                }
            }
        }
        return level[sink] != -1;
    }

    ll dfs(int node, ll flow) {
        if (node == sink) return flow;
        for (int &it = ptr[node]; it < g[node].size(); ++it) {
            int i = g[node][it];
            auto &e = edges[i];
            auto &back = edges[i ^ 1];
            if (e.w > 0 && level[e.to] == level[node] + 1) {
                ll f = dfs(e.to, min(flow, e.w));
                if (f > 0) {
                    e.w -= f;
                    back.w += f;
                    return f;
                }
            }
        }
        return 0;
    }

    ll max_flow() {
        while (bfs()) {
            ptr.assign(n, 0);
            ll f;
            while ((f = dfs(source, INF)) > 0) flow += f;
        }
        return flow;
    }
};

int main() {
    int n, m;
    cin >> n >> m;

    MaxFlow flow(n, 0, n - 1);
    for (int i = 0; i < m; ++i) {
        int a, b, w;
        cin >> a >> b >> w;
        a--;
        b--;
        flow.add_edge(a, b, w, 0);
    }

    cout << flow.max_flow() << '\n';
}
```

## References

* [CPHB (Competitive Programmer's Handbook)](https://cses.fi/book), Chapter 20, Ford–Fulkerson algorithm
* [Dinic's algorithm (Wikipedia)](https://en.wikipedia.org/wiki/Dinic%27s_algorithm)