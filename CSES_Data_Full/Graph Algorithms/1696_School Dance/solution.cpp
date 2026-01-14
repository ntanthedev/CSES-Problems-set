#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

struct MaxFlow {
    static const ll INF = 1e18;

    struct Edge {
        int from;
        int to;
        ll w;
        bool real;
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
        edges.push_back({from, to, forward, true});
        g[to].emplace_back(id + 1);
        edges.push_back({to, from, backward, false});
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
    int n, m, k;
    cin >> n >> m >> k;

    MaxFlow flow(n + m + 2, 0, n + m + 1);

    for (int i = 1; i <= n; i++) {
        flow.add_edge(0, i, 1);
    }
    for (int i = 1; i <= m; i++) {
        flow.add_edge(n + i, n + m + 1, 1);
    }

    for (int i = 1; i <= k; i++) {
        int a, b;
        cin >> a >> b;
        flow.add_edge(a, n + b, 1);
    }

    cout << flow.max_flow() << "\n";

    for (int node = 1; node <= n; node++) {
        for (auto id : flow.g[node]) {
            auto edge = flow.edges[id];
            if (edge.w == 0 && edge.real) {
                cout << node << " " << edge.to - n << "\n";
            }
        }
    }
}
