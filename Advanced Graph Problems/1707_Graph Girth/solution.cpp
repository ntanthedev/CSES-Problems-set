#include <iostream>
#include <vector>
using namespace std;

const int INF = 1e9;
const int N = 2501;
vector<int> g[N];

int dist[N], tree[N];

int main() {
    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    int ans = INF;
    for (int i = 1; i <= n; i++) {
        fill(dist, dist + N, -1);
        dist[i] = 0;
        vector<int> q;
        for (int j = 0; j < g[i].size(); ++j) {
            q.push_back(g[i][j]);
            tree[g[i][j]] = j;
            dist[g[i][j]] = 1;
        }
        for (int qi = 0; qi < q.size(); qi++) {
            int s = q[qi];
            for (int nxt : g[s]) {
                if (dist[nxt] == -1) {
                    dist[nxt] = dist[s] + 1;
                    tree[nxt] = tree[s];
                    q.push_back(nxt);
                } else if (tree[nxt] != tree[s] && nxt != i) {
                    ans = min(ans, dist[nxt] + dist[s] + 1);
                }
            }
        }
    }
    if (ans == INF) ans = -1;
    cout << ans << '\n';
}
