#include <iostream>
#include <queue>
#include <vector>
using namespace std;
using ll = long long;
template <typename T>
using reverse_priority_queue = priority_queue<T, vector<T>, greater<T>>;
const int N = 100001;
const int K = 10;
vector<pair<int, int>> g[N];
int visited[N];
ll dist[K];

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 1; i <= m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].emplace_back(b, c);
    }

    reverse_priority_queue<pair<ll, int>> q;
    q.emplace(0, 1);

    while (!q.empty()) {
        auto [d, x] = q.top();
        q.pop();
        if (visited[x] >= k) {
            continue;
        }
        if (x == n) {
            dist[visited[x]] = d;
        }
        ++visited[x];
        for (auto [y, len] : g[x]) {
            q.emplace(d + len, y);
        }
    }

    for (int i = 0; i < k; ++i) {
        cout << dist[i] << ' ';
    }
    cout << '\n';
}
