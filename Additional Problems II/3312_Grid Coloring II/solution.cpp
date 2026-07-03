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

bool patternColoring() {
    for (int rot = 0; rot < 3; rot++) {
        vector<string> out(n, string(m, ' '));
        bool good = true;
        for (int i = 0; i < n && good; i++) {
            for (int j = 0; j < m; j++) {
                char c = ABC[(i + j + rot) % 3];
                if (c == orig[i][j]) {
                    good = false;
                    break;
                }
                if (j > 0 && c == out[i][j - 1]) {
                    good = false;
                    break;
                }
                if (i > 0 && c == out[i - 1][j]) {
                    good = false;
                    break;
                }
                out[i][j] = c;
            }
        }
        if (good) {
            g = out;
            return true;
        }
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

    if (1LL * n * m <= 40000) {
        if (!dfs(0)) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
    } else if (!patternColoring()) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    for (auto& row : g) cout << row << '\n';
    return 0;
}
