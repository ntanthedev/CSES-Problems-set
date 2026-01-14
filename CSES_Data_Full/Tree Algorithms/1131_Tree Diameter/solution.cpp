#include <iostream>
#include <vector>
using namespace std;

const int N = 200001;
vector<int> g[N];
int dist[N];
int diameter = 0;

void dfs(int node, int parent) {
    int max_distance = 0;
    for (int child : g[node]) {
        if (child != parent) {
            dfs(child, node);
            diameter = max(diameter, max_distance + dist[child] + 1);
            max_distance = max(max_distance, dist[child] + 1);
        }
    }
    dist[node] = max_distance;
}

int main() {
    int n;
    cin >> n;

    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    dfs(1, 1);

    cout << diameter << '\n';
}
