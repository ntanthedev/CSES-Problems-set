# 1694 - Tốc độ Tải xuống

## Giải pháp 1: Giải thuật Scaling

Giải thuật này, đôi khi được gọi là *Giải thuật Scaling*, tính toán
luồng cực đại trong một đồ thị. Nó sử dụng các ý tưởng giống như giải thuật Ford-Fulkerson,
ngoại trừ việc nó sử dụng tìm kiếm theo chiều sâu để tìm các đường tăng luồng trong đó mỗi
trọng số cạnh lớn hơn một giá trị ngưỡng.

Ban đầu, giá trị ngưỡng $C$ được chọn là một số lớn, ví dụ,
trọng số cạnh lớn nhất của đồ thị. Sau đó, giải thuật sẽ chạy $O(\log C)$
pha, sau mỗi pha giá trị ngưỡng được giảm một nửa. Giải thuật có
thời gian chạy là $O(m^2\log C)$.

Hai giải thuật luồng được trình bày ở đây được đưa ra dưới dạng hộp đen: chúng là các cài đặt
hoàn chỉnh có thể dễ dàng sử dụng trong các bài toán khác. Hầu hết thời gian,
không cần phải sửa đổi các giải thuật.

```cpp
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

// Giải thuật Scaling tính luồng cực đại trong mạng luồng.
// Chạy trong thời gian O(m^2 log C).
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

## Giải pháp 2: Giải thuật Dinic

Giải thuật Dinic được phát triển bởi Yefim A. Dinitz và dựa trên các ý tưởng của
giải thuật Edmonds-Karp. Tuy nhiên, giải thuật Dinic sử dụng một vài tối ưu hóa
để giảm độ phức tạp thời gian xuống còn $O(n^2\cdot m)$ khi có $n$ đỉnh và
$m$ cạnh.

Có một số trường hợp mà giải thuật Dinic có độ phức tạp thời gian tốt hơn
$O(n^2\cdot m)$. Một trong số đó là ghép cặp hai phía mà giải thuật có thể
giải trong $O(\sqrt{n}m)$. Hóa ra cận này đúng trong mọi mạng đơn vị,
nơi dung lượng vào hoặc ra của mỗi đỉnh tối đa là $1$.

Những cận này làm cho giải thuật Dinic đủ nhanh cho hầu hết các bài toán luồng trong
lập trình thi đấu.

```cpp
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
using ll = long long;

// Giải thuật Dinic tính luồng cực đại trong mạng luồng.
// Chạy trong thời gian O(m n^2).
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

## Tài liệu tham khảo

* [CPHB (Sổ tay Lập trình viên)](https://cses.fi/book), Chương 20, Giải thuật Ford–Fulkerson
* [Giải thuật Dinic (Wikipedia)](https://en.wikipedia.org/wiki/Dinic%27s_algorithm)
