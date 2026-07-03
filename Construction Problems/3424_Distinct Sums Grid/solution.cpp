#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    if (n <= 3) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    vector<vector<int>> g(n + 1, vector<int>(n + 1));
    vector<int> row(n + 1, 0), col(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            g[i][j] = i;
            row[i] += i;
            col[j] += i;
        }
    }

    map<int, int> freq;
    int cnt = 0;
    auto add = [&](int x) {
        if (++freq[x] == 1) ++cnt;
    };
    auto rem = [&](int x) {
        if (--freq[x] == 0) --cnt;
    };
    for (int i = 1; i <= n; ++i) {
        add(row[i]);
        add(col[i]);
    }

  mt19937 rng((unsigned)chrono::steady_clock::now().time_since_epoch().count());

    for (int iter = 0; iter < 50000 && cnt < 2 * n; ++iter) {
        int r1 = uniform_int_distribution<int>(1, n)(rng);
        int c1 = uniform_int_distribution<int>(1, n)(rng);
        int r2 = uniform_int_distribution<int>(1, n)(rng);
        int c2 = uniform_int_distribution<int>(1, n)(rng);
        if (r1 == r2 && c1 == c2) continue;

        int old = g[r1][c1];
        int neu = g[r2][c2];
        if (old == neu) continue;

        int ori = cnt;
        rem(row[r1]); rem(row[r2]); rem(col[c1]); rem(col[c2]);
        row[r1] += neu - old;
        col[c1] += neu - old;
        row[r2] += old - neu;
        col[c2] += old - neu;
        add(row[r1]); add(row[r2]); add(col[c1]); add(col[c2]);

        if (cnt >= ori) {
            swap(g[r1][c1], g[r2][c2]);
        } else {
            rem(row[r1]); rem(row[r2]); rem(col[c1]); rem(col[c2]);
            row[r1] -= neu - old;
            col[c1] -= neu - old;
            row[r2] -= old - neu;
            col[c2] -= old - neu;
            add(row[r1]); add(row[r2]); add(col[c1]); add(col[c2]);
        }
    }

    if (cnt < 2 * n) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (j > 1) cout << ' ';
            cout << g[i][j];
        }
        cout << '\n';
    }
    return 0;
}
