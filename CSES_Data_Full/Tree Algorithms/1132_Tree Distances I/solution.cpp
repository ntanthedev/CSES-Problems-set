#include <iostream>
#include <vector>
using namespace std;

const int N = 200001;
vector<int> g[N];
int max_dist[N][2];

void update(int node, int offer) {
    if (offer > max_dist[node][0]) {
        max_dist[node][1] = max_dist[node][0];
        max_dist[node][0] = offer;
    } else if (offer > max_dist[node][1]) {
        max_dist[node][1] = offer;
    }
}

void dfs1(int node, int parent) {
    for (int child : g[node]) {
        if (child == parent) continue;
        dfs1(child, node);
        update(node, max_dist[child][0] + 1);
    }
}

void dfs2(int node, int parent) {
    for (int child : g[node]) {
        if (child == parent) continue;
        if (max_dist[node][0] == max_dist[child][0] + 1) {
            update(child, max_dist[node][1] + 1);
        } else {
            update(child, max_dist[node][0] + 1);
        }
        dfs2(child, node);
    }
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

    dfs1(1, 1);

    dfs2(1, 1);

    for (int i = 1; i <= n; ++i) {
        cout << max_dist[i][0] << ' ';
    }
    cout << '\n';
}
