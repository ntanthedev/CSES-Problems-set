#include <bits/stdc++.h>
using namespace std;

struct HopcroftKarp {
    int n;
    vector<vector<int>> g;
    vector<int> dist, matchL, matchR;

    HopcroftKarp(int n_) : n(n_), g(n_ + 1), dist(n_ + 1), matchL(n_ + 1, 0), matchR(n_ + 1, 0) {}

    void add_edge(int u, int v) { g[u].push_back(v); }

    bool bfs() {
        queue<int> q;
        for (int u = 1; u <= n; ++u) {
            if (!matchL[u]) {
                dist[u] = 0;
                q.push(u);
            } else {
                dist[u] = -1;
            }
        }
        bool found = false;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : g[u]) {
                int w = matchR[v];
                if (w == 0) found = true;
                else if (dist[w] == -1) {
                    dist[w] = dist[u] + 1;
                    q.push(w);
                }
            }
        }
        return found;
    }

    bool dfs(int u) {
        for (int v : g[u]) {
            int w = matchR[v];
            if (!w || (dist[w] == dist[u] + 1 && dfs(w))) {
                matchL[u] = v;
                matchR[v] = u;
                return true;
            }
        }
        dist[u] = -1;
        return false;
    }

    int max_matching() {
        int matching = 0;
        while (bfs()) {
            for (int u = 1; u <= n; ++u) {
                if (!matchL[u] && dfs(u)) ++matching;
            }
        }
        return matching;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    HopcroftKarp hk(n);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        hk.add_edge(a, b);
    }

    int match = hk.max_matching();
    if (match < n - 2) {
        cout << "NO\n";
        return 0;
    }

    vector<int> nxt(n + 1, 0);
    for (int u = 1; u <= n; ++u)
        if (hk.matchL[u]) nxt[u] = hk.matchL[u];

    vector<char> has_in(n + 1, 0);
    for (int u = 1; u <= n; ++u)
        if (nxt[u]) has_in[nxt[u]] = 1;

    vector<vector<int>> paths;
    for (int v = 1; v <= n; ++v) {
        if (!has_in[v]) {
            vector<int> path;
            for (int cur = v; cur; cur = nxt[cur]) path.push_back(cur);
            paths.push_back(path);
        }
    }

    while ((int)paths.size() < 2) paths.push_back({});
    while ((int)paths.size() > 2) {
        paths[1].insert(paths[1].begin(), paths.back().begin(), paths.back().end());
        paths.pop_back();
    }

    cout << "YES\n";
    for (int i = 0; i < 2; ++i) {
        cout << paths[i].size();
        for (int v : paths[i]) cout << ' ' << v;
        cout << '\n';
    }
    return 0;
}
