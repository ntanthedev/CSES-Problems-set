#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<string> orig, g;
const string ABC = "ABC";

bool ok(int i, int j, char c) {
    if (c == orig[i][j]) return false;
    if (i > 0 && g[i - 1][j] == c) return false;
    if (j > 0 && g[i][j - 1] == c) return false;
    return true;
}

bool dfs(int idx) {
    if (idx == n * m) return true;
    int i = idx / m, j = idx % m;
    for (char c : ABC) {
        if (!ok(i, j, c)) continue;
        g[i][j] = c;
        if (dfs(idx + 1)) return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    orig.resize(n);
    g.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> orig[i];
        g[i] = string(m, ' ');
    }

    if (1LL * n * m <= 20000) {
        if (!dfs(0)) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
        for (auto& row : g) cout << row << '\n';
        return 0;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char chosen = 0;
            for (int t = 0; t < 3; t++) {
                char c = ABC[(i + j + t) % 3];
                if (c == orig[i][j]) continue;
                if (i > 0 && g[i - 1][j] == c) continue;
                if (j > 0 && g[i][j - 1] == c) continue;
                chosen = c;
                break;
            }
            if (!chosen) {
                cout << "IMPOSSIBLE\n";
                return 0;
            }
            g[i][j] = chosen;
        }
    }

    for (auto& row : g) cout << row << '\n';
}
