#include <bitset>
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>
using namespace std;
using ll = long long;
const ll INF = 1e18;
const int N = 2501;

bitset<N> bfs(int s, vector<vector<int>>& g) {
    bitset<N> visited;
    queue<int> q;
    q.push(s);
    visited[s] = true;
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int y : g[x]) {
            if (!visited[y]) {
                visited[y] = true;
                q.push(y);
            }
        }
    }
    return visited;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<tuple<int, int, int>> edges;
    vector<vector<int>> g(n + 1);
    vector<vector<int>> rev_g(n + 1);

    for (int i = 1; i <= m; ++i) {
        int a, b, x;
        cin >> a >> b >> x;
        edges.emplace_back(a, b, -x);
        g[a].push_back(b);
        rev_g[b].push_back(a);
    }

    auto included = bfs(1, g) & bfs(n, rev_g);

    vector<ll> distance(n + 1, INF);
    distance[1] = 0;

    for (int i = 1; i <= n; ++i) {
        for (auto [from, to, score] : edges) {
            if (!included[from] || !included[to]) continue;
            ll new_distance = min(distance[to], distance[from] + score);
            if (i == n && new_distance < distance[to]) {
                cout << -1 << '\n';
                return 0;
            }
            distance[to] = new_distance;
        }
    }
    cout << -distance[n] << '\n';
}
