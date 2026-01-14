#include <iostream>
#include <set>
#include <vector>
using namespace std;

const int N = 200001;
vector<int> g[N];
int answer[N], color[N];

set<int> dfs(int node, int parent) {
    set<int> colors{color[node]};
    for (int child : g[node]) {
        if (child == parent) continue;
        auto child_colors = dfs(child, node);
        // `swap` is guaranteed to work in O(1) for stl containers.
        if (child_colors.size() > colors.size()) {
            swap(colors, child_colors);
        }
        colors.merge(child_colors);
    }
    answer[node] = colors.size();
    return colors;
}

int main() {
    int n;
    cin >> n;

    for (int i = 1; i <= n; ++i) {
        cin >> color[i];
    }

    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    dfs(1, -1);

    for (int i = 1; i <= n; ++i) {
        cout << answer[i] << ' ';
    }
    cout << '\n';
}
