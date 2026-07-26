#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<bool>> adj(n, vector<bool>(n, false));
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        adj[a][b] = adj[b][a] = true;
    }

    int best_k = n + 1;
    vector<int> best_col(n, 0), col(n, 0);

    function<bool(int, int)> can_color = [&](int v, int k) -> bool {
        if (v == n) return true;
        for (int c = 1; c <= k; ++c) {
            bool ok = true;
            for (int u = 0; u < v; ++u) {
                if (adj[v][u] && col[u] == c) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                col[v] = c;
                if (can_color(v + 1, k)) return true;
                col[v] = 0;
            }
        }
        return false;
    };

    for (int k = 1; k <= n; ++k) {
        fill(col.begin(), col.end(), 0);
        if (can_color(0, k)) {
            best_k = k;
            best_col = col;
            break;
        }
    }

    cout << best_k << '\n';
    for (int i = 0; i < n; ++i) {
        if (i) cout << ' ';
        cout << best_col[i];
    }
    cout << '\n';
    return 0;
}
