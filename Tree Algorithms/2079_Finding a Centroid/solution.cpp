#include <iostream>
#include <vector>
using namespace std;

const int N = 200001;
vector<int> g[N];
int sz[N], max_child[N];

void dfs(int node, int parent) {
    sz[node] = 1;
    for (int child : g[node]) {
        if (child == parent) continue;
        dfs(child, node);
        sz[node] += sz[child];
        max_child[node] = max(max_child[node], sz[child]);
    }
}

int main() {
    int n;
    cin >> n;

    for (int i = 1; i <= n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    dfs(1, -1);

    for (int i = 1; i <= n; ++i) {
        if (max(max_child[i], n - sz[i]) <= n / 2) {
            cout << i << '\n';
            break;
        }
    }
}
