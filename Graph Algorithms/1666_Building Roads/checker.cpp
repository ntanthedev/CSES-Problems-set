#include "testlib.h"
#include <vector>
#include <queue>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = inf.readInt();
    vector<vector<int>> g(n + 1);
    for (int i = 0; i < m; i++) {
        int a = inf.readInt();
        int b = inf.readInt();
        g[a].push_back(b);
        g[b].push_back(a);
    }

    int k_ans = ans.readInt();
    int k = ouf.readInt();
    if (k != k_ans)
        quitf(_wa, "Claimed %d roads but optimal is %d", k, k_ans);
    if (k < 0)
        quitf(_wa, "Number of roads must be non-negative, got %d", k);

    for (int i = 0; i < k; i++) {
        int a = ouf.readInt();
        int b = ouf.readInt();
        if (a < 1 || a > n || b < 1 || b > n)
            quitf(_wa, "Road %d: cities %d %d out of range [1,%d]", i + 1, a, b, n);
        if (a == b)
            quitf(_wa, "Road %d: self-loop %d-%d", i + 1, a, b);
        g[a].push_back(b);
        g[b].push_back(a);
    }

    for (int i = 0; i < k_ans; i++)
        ans.readInt(), ans.readInt();

    vector<char> vis(n + 1, 0);
    queue<int> q;
    q.push(1);
    vis[1] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : g[u]) {
            if (!vis[v]) {
                vis[v] = 1;
                q.push(v);
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        if (!vis[i])
            quitf(_wa, "City %d is still disconnected after adding roads", i);
    }

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid: %d roads make the graph connected", k);
}
