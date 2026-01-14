#include <iostream>
#include <vector>
using namespace std;

void fail() {
    cout << "IMPOSSIBLE" << '\n';
    exit(0);
}

const int N = 100001;
vector<int> g[N];
vector<pair<int, int>> ans;
bool visited[N];
int depth[N], min_depth[N];

void dfs(int node, int prev) {
    visited[node] = true;
    min_depth[node] = depth[node];
    for (int nxt : g[node]) {
        if (nxt == prev) continue;
        if (visited[nxt]) {
            if (depth[nxt] < depth[node]) {
                ans.emplace_back(node, nxt);
            }
            min_depth[node] = min(min_depth[node], depth[nxt]);
        } else {
            depth[nxt] = depth[node] + 1;
            dfs(nxt, node);
            min_depth[node] = min(min_depth[node], min_depth[nxt]);
            ans.emplace_back(node, nxt);
            if (min_depth[nxt] > depth[node]) fail();
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    dfs(1, -1);

    if (ans.size() != m) fail();

    for (auto [a, b] : ans) {
        cout << a << ' ' << b << '\n';
    }
}
