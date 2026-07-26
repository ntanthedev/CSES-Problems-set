#include <bits/stdc++.h>
using namespace std;

vector<int> g[100005], rg[100005];
bool vis[100005];
vector<int> order, comp;
int cid;

void dfs1(int u) {
    vis[u] = true;
    for (int v : g[u])
        if (!vis[v]) dfs1(v);
    order.push_back(u);
}

void dfs2(int u) {
    vis[u] = true;
    comp.push_back(u);
    for (int v : rg[u])
        if (!vis[v]) dfs2(v);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        rg[b].push_back(a);
    }

    for (int i = 1; i <= n; ++i)
        if (!vis[i]) dfs1(i);

    fill(vis + 1, vis + n + 1, false);
    vector<vector<int>> sccs;
    for (int i = n - 1; i >= 0; --i) {
        int v = order[i];
        if (!vis[v]) {
            comp.clear();
            dfs2(v);
            sccs.push_back(comp);
        }
    }

    int scc_cnt = (int)sccs.size();
    if (scc_cnt == 1) {
        cout << 0 << '\n';
        return 0;
    }

    vector<int> scc_id(n + 1);
    for (int i = 0; i < scc_cnt; ++i)
        for (int v : sccs[i]) scc_id[v] = i;

    vector<bool> is_source(scc_cnt, true), is_sink(scc_cnt, true);
    for (int u = 1; u <= n; ++u) {
        for (int v : g[u]) {
            if (scc_id[u] != scc_id[v]) {
                is_sink[scc_id[u]] = false;
                is_source[scc_id[v]] = false;
            }
        }
    }

    vector<int> sources, sinks;
    for (int i = 0; i < scc_cnt; ++i) {
        if (is_source[i]) sources.push_back(i);
        if (is_sink[i]) sinks.push_back(i);
    }

    int k = max((int)sources.size(), (int)sinks.size());
    cout << k << '\n';

    for (int i = 0; i < k; ++i) {
        int from_scc = sinks[i % sinks.size()];
        int to_scc = sources[(i + 1) % sources.size()];
        cout << sccs[from_scc][0] << ' ' << sccs[to_scc][0] << '\n';
    }

    return 0;
}
