#include <iostream>
#include <vector>
using namespace std;

static const long long INF = (1LL << 60);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, long long>>> g(n + 1);
    for (int i = 0; i < m; i++) {
        int l, r;
        long long s;
        cin >> l >> r >> s;
        g[l - 1].push_back({r, s});
        g[r].push_back({l - 1, -s});
    }

    vector<long long> dist(n + 1, 0);
    bool ok = true;

    for (int i = 0; i <= n; i++) {
        bool updated = false;
        for (int u = 0; u <= n; u++) {
            for (auto [v, w] : g[u]) {
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    updated = true;
                    if (i == n) ok = false;
                }
            }
        }
        if (!updated) break;
    }

    if (!ok) {
        cout << "NO\n";
        return 0;
    }

    cout << "YES\n";
    for (int i = 1; i <= n; i++) {
        if (i > 1) cout << ' ';
        cout << dist[i] - dist[i - 1];
    }
    cout << '\n';
}
