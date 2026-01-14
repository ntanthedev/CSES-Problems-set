#include <iostream>
#include <queue>
using namespace std;
using ll = long long;
template <typename T>
using reverse_priority_queue = priority_queue<T, vector<T>, greater<T>>;
const int N = 100001;
const ll INF = 1e18;
vector<pair<int, int>> g[N];
ll dist[N];

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].emplace_back(b, c);
    }

    for (int i = 1; i <= n; ++i) {
        dist[i] = INF;
    }

    reverse_priority_queue<pair<ll, int>> queue;
    queue.emplace(0, 1);
    dist[1] = 0;

    while (!queue.empty()) {
        auto [d, x] = queue.top();
        queue.pop();
        if (dist[x] < d) continue;
        for (auto [y, len] : g[x]) {
            ll new_d = d + len;
            if (new_d < dist[y]) {
                dist[y] = new_d;
                queue.emplace(new_d, y);
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        cout << dist[i] << ' ';
    }
    cout << '\n';
}
