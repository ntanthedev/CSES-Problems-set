#include <iostream>
using namespace std;
using ll = long long;
const int N = 501;
const ll INF = 1e18;
ll dist[N][N];

int main() {
    int n, m, q;
    cin >> n >> m >> q;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            dist[i][j] = i == j ? 0 : INF;
        }
    }
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        dist[a][b] = min(dist[a][b], (ll)c);
        dist[b][a] = min(dist[b][a], (ll)c);
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            for (int k = 1; k <= n; ++k) {
                dist[j][k] = min(dist[j][k], dist[j][i] + dist[i][k]);
            }
        }
    }

    for (int i = 0; i < q; ++i) {
        int a, b;
        cin >> a >> b;
        if (dist[a][b] == INF) {
            cout << -1 << '\n';
        } else {
            cout << dist[a][b] << '\n';
        }
    }
}
