#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> in_degree(n + 1);
    vector<vector<int>> g(n + 1);

    for (int i = 1; i <= m; ++i) {
        int a, b;
        cin >> a >> b;
        ++in_degree[b];
        g[a].push_back(b);
    }

    vector<int> no_incoming;

    for (int i = 1; i <= n; ++i) {
        if (in_degree[i] == 0) {
            no_incoming.push_back(i);
        }
    }

    for (int i = 0; i < no_incoming.size(); ++i) {
        int x = no_incoming[i];
        for (int y : g[x]) {
            --in_degree[y];
            if (in_degree[y] == 0) {
                no_incoming.push_back(y);
            }
        }
    }

    if (no_incoming.size() < n) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    for (int x : no_incoming) {
        cout << x << ' ';
    }
    cout << '\n';
}
