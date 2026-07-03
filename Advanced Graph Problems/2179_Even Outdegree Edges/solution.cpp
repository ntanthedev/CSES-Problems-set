#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> g(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back({b, i});
        g[b].push_back({a, i});
    }

    vector<char> seen(n + 1, 0);
    for (int s = 1; s <= n; s++) {
        if (seen[s]) continue;
        queue<int> q;
        q.push(s);
        seen[s] = 1;
        int edge_cnt = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (auto [v, id] : g[u]) {
                if (u < v) edge_cnt++;
                if (!seen[v]) {
                    seen[v] = 1;
                    q.push(v);
                }
            }
        }
        if (edge_cnt % 2 == 1) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
    }

    vector<int> tin(n + 1, 0), tout(n + 1, 0);
    vector<char> even(n + 1, 1);
    vector<int> parent(n + 1, -1), parent_edge(n + 1, -1);
    vector<int> next_idx(n + 1, 0);
    vector<pair<int, int>> ans(m);
    int timer = 0;

    for (int start = 1; start <= n; start++) {
        if (tin[start]) continue;

        vector<int> stack;
        stack.push_back(start);
        tin[start] = ++timer;
        parent[start] = -1;

        while (!stack.empty()) {
            int u = stack.back();
            if (next_idx[u] < (int)g[u].size()) {
                auto [v, id] = g[u][next_idx[u]++];
                if (v == parent[u]) continue;
                if (!tin[v]) {
                    parent[v] = u;
                    parent_edge[v] = id;
                    tin[v] = ++timer;
                    stack.push_back(v);
                } else if (!tout[v] && tin[v] < tin[u]) {
                    even[u] ^= 1;
                    ans[id] = {u, v};
                }
            } else {
                tout[u] = timer;
                stack.pop_back();
                if (parent[u] != -1) {
                    int p = parent[u];
                    int id = parent_edge[u];
                    if (even[u]) {
                        ans[id] = {p, u};
                        even[p] ^= 1;
                    } else {
                        ans[id] = {u, p};
                        even[u] ^= 1;
                    }
                }
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        if (!even[i]) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
    }

    for (int i = 0; i < m; i++)
        cout << ans[i].first << ' ' << ans[i].second << '\n';
    return 0;
}
