#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const int N = 200001;

int n;
vector<int> g[N];
int subtree[N];  // subtree sizes

ll dfs(int node, int parent) {
    subtree[node] = 1;
    ll distance_sum = 0;
    for (int child : g[node]) {
        if (child == parent) continue;
        distance_sum += dfs(child, node);
        subtree[node] += subtree[child];
    }
    distance_sum += subtree[node] - 1;
    return distance_sum;
}

ll ans[N];

void calc(int node, int parent) {
    for (int child : g[node]) {
        if (child == parent) continue;
        ans[child] = ans[node] - subtree[child] + (n - subtree[child]);
        calc(child, node);
    }
}

int main() {
    cin >> n;

    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    ans[1] = dfs(1, 1);
    calc(1, 1);

    for (int i = 1; i <= n; ++i) {
        cout << ans[i] << ' ';
    }
    cout << '\n';
}
