#include <iostream>
#include <vector>
using namespace std;

const int N = 1e5 + 1;
vector<int> g[N];
vector<pair<int, int>> bridges;
bool visited[N];
int depth[N], min_depth[N];

void dfs(int node, int prev) {
    visited[node] = true;
    min_depth[node] = depth[node];
    for (int nxt : g[node]) {
        if (nxt == prev) continue;
        if (visited[nxt]) {
            min_depth[node] = min(min_depth[node], depth[nxt]);
        } else {
            depth[nxt] = depth[node] + 1;
            dfs(nxt, node);
            min_depth[node] = min(min_depth[node], min_depth[nxt]);
            if (min_depth[nxt] > depth[node]) {
                bridges.emplace_back(node, nxt);
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= m; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    dfs(1, 0);

    cout << bridges.size() << '\n';
    for (auto [a, b] : bridges) {
        cout << a << ' ' << b << '\n';
    }
}
