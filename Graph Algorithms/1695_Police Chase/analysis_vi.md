# 1695 - Cuộc rượt đuổi của Cảnh sát

Nhiệm vụ của chúng ta là tìm một lát cắt nhỏ nhất trong đồ thị, việc này có thể được thực hiện bằng giải thuật luồng cực đại. Giải pháp sau đây sử dụng giải thuật scaling để xác định luồng cực đại.

Chúng ta cũng cần xác định một tập các cạnh tương ứng với lát cắt nhỏ nhất. Gọi $R$ là tập các đỉnh có thể đến được từ nguồn bằng cách sử dụng các cạnh có dung lượng dương sau khi tính luồng cực đại. Một cạnh $a \rightarrow b$ thuộc lát cắt nhỏ nhất khi và chỉ khi $a \in R$, $b \notin R$, và có luồng từ $a$ đến $b$.

```cpp
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
    int n, m;
    cin >> n >> m;

    MaxFlow flow(n + 1, 1, n);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        flow.add_edge(a, b, 1, 1);
    }

    cout << flow.max_flow() << "\n";

    for (int node = 1; node <= n; node++) {
        if (!flow.seen[node]) continue;
        for (auto id : flow.g[node]) {
            auto edge = flow.edges[id];
            if (!flow.seen[edge.to] && edge.w == 0 && edge.real) {
                cout << node << " " << edge.to << "\n";
            }
        }
    }
}
```
