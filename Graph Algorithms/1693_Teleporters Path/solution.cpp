#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> eu(m), ev(m);
    vector<vector<int>> adj(n + 1);
    vector<int> inDeg(n + 1), outDeg(n + 1);

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        eu[i] = a;
        ev[i] = b;
        adj[a].push_back(i);
        outDeg[a]++;
        inDeg[b]++;
    }

    inDeg[1]++;
    outDeg[n]++;

    for (int i = 1; i <= n; i++) {
        if (inDeg[i] != outDeg[i]) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
    }

    vector<int> ptr(n + 1, 0);
    vector<char> used(m, 0);
    vector<int> path;

    auto dfs = [&](auto &&self, int v) -> void {
        while (ptr[v] < (int)adj[v].size()) {
            int e = adj[v][ptr[v]++];
            if (used[e])
                continue;
            used[e] = 1;
            self(self, ev[e]);
        }
        path.push_back(v);
    };

    dfs(dfs, 1);
    reverse(path.begin(), path.end());

    if ((int)path.size() != m + 1 || path.front() != 1 || path.back() != n) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    for (int i = 0; i <= m; i++) {
        if (i)
            cout << ' ';
        cout << path[i];
    }
    cout << '\n';
    return 0;
}
