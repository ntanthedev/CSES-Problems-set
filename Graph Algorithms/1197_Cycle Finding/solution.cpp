#include <algorithm>
#include <iostream>
#include <optional>
#include <tuple>
#include <vector>
using namespace std;
using ll = long long;

int main() {
    int n, m;
    vector<tuple<int, int, int>> edges;

    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        edges.emplace_back(a, b, c);
    }

    vector<ll> distance(n + 1);
    vector<int> previous(n + 1);
    optional<int> path_end;

    for (int i = 1; i <= n; ++i) {
        for (auto [from, to, len] : edges) {
            ll new_distance = distance[from] + len;
            if (new_distance < distance[to]) {
                distance[to] = new_distance;
                previous[to] = from;
                if (i == n) {
                    path_end = to;
                }
            }
        }
    }

    if (!path_end) {
        cout << "NO\n";
        return 0;
    }

    vector<char> visited(n + 1);
    vector<int> path;
    int x = *path_end;
    while (true) {
        path.push_back(x);
        if (visited[x]) break;
        visited[x] = 1;
        x = previous[x];
    }
    reverse(path.begin(), path.end());

    cout << "YES\n";
    for (int i = 0; i < path.size(); ++i) {
        cout << path[i] << ' ';
        if (i > 0 && path[i] == path.front()) break;
    }
    cout << '\n';
}
