#include <bitset>
#include <iostream>
#include <vector>
using namespace std;

const int N = 5e4 + 1;

vector<int> g[N];
bitset<N> reach[N];
bool visited[N];

void dfs(int node) {
    if (visited[node]) return;
    visited[node] = true;
    reach[node][node] = true;
    for (int nxt : g[node]) {
        dfs(nxt);
        reach[node] |= reach[nxt];
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= m; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
    }

    for (int i = 1; i <= n; ++i) {
        dfs(i);
        cout << reach[i].count() << ' ';
    }
    cout << '\n';
}
