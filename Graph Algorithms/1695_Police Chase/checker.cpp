#include "testlib.h"
#include <vector>
#include <queue>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = inf.readInt();
    vector<vector<int>> adj(n + 1);
    vector<pair<int, int>> edges;
    for (int i = 0; i < m; i++) {
        int a = inf.readInt();
        int b = inf.readInt();
        edges.push_back({a, b});
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    int k_ans = ans.readInt();
    int k = ouf.readInt();
    if (k != k_ans)
        quitf(_wa, "Claimed %d streets but optimal is %d", k, k_ans);
    if (k < 0 || k > m)
        quitf(_wa, "k=%d out of range [0,%d]", k, m);

    set<pair<int, int>> closedEdges;
    for (int i = 0; i < k; i++) {
        int a = ouf.readInt();
        int b = ouf.readInt();
        if (a < 1 || a > n || b < 1 || b > n)
            quitf(_wa, "Edge %d-%d out of range", a, b);
        int mn = min(a, b), mx = max(a, b);
        bool found = false;
        for (auto [u, v] : edges) {
            if ((u == a && v == b) || (u == b && v == a)) {
                found = true;
                break;
            }
        }
        if (!found)
            quitf(_wa, "Street %d-%d does not exist in the city", a, b);
        if (closedEdges.count({mn, mx}))
            quitf(_wa, "Street %d-%d listed twice", mn, mx);
        closedEdges.insert({mn, mx});
    }

    vector<bool> vis(n + 1, false);
    queue<int> q;
    q.push(1);
    vis[1] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (u == n)
            break;
        for (int v : adj[u]) {
            int mn = min(u, v), mx = max(u, v);
            if (!vis[v] && !closedEdges.count({mn, mx})) {
                vis[v] = true;
                q.push(v);
            }
        }
    }
    if (vis[n])
        quitf(_wa, "Route from 1 to %d still exists after closing %d streets", n, k);

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid minimum cut of size %d", k);
}
