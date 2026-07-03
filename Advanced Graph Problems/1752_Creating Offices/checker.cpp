#include "testlib.h"
#include <vector>
#include <array>
using namespace std;

static const int LOGN = 19;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int d = inf.readInt();
    vector<vector<int>> g(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int a = inf.readInt();
        int b = inf.readInt();
        g[a].push_back(b);
        g[b].push_back(a);
    }

    int k_ans = ans.readInt();
    int k = ouf.readInt();
    if (k != k_ans)
        quitf(_wa, "Claimed %d offices but optimal is %d", k, k_ans);
    if (k < 0 || k > n)
        quitf(_wa, "k=%d out of range [0,%d]", k, n);

    vector<int> offices(k);
    vector<bool> is_office(n + 1, false);
    for (int i = 0; i < k; i++) {
        offices[i] = ouf.readInt();
        if (offices[i] < 1 || offices[i] > n)
            quitf(_wa, "City %d out of range", offices[i]);
        if (is_office[offices[i]])
            quitf(_wa, "City %d selected more than once", offices[i]);
        is_office[offices[i]] = true;
    }

    vector<array<int, LOGN>> up(n + 1);
    vector<int> depth(n + 1), tin(n + 1), tout(n + 1);
    int timer = 0;

    auto is_ancestor = [&](int u, int v) {
        return tin[u] <= tin[v] && tout[u] >= tout[v];
    };

    function<int(int, int)> lca = [&](int u, int v) {
        if (is_ancestor(u, v))
            return u;
        if (is_ancestor(v, u))
            return v;
        int x = u;
        for (int i = LOGN - 1; i >= 0; i--)
            if (!is_ancestor(up[x][i], v))
                x = up[x][i];
        return up[x][0];
    };

    auto dist = [&](int u, int v) {
        return depth[u] + depth[v] - 2 * depth[lca(u, v)];
    };

    function<void(int, int)> dfs = [&](int u, int par) {
        tin[u] = ++timer;
        depth[u] = depth[par] + 1;
        up[u][0] = par;
        for (int i = 1; i < LOGN; i++)
            up[u][i] = up[up[u][i - 1]][i - 1];
        for (int v : g[u])
            if (v != par)
                dfs(v, u);
        tout[u] = ++timer;
    };
    dfs(1, 1);

    for (int i = 0; i < k; i++) {
        for (int j = i + 1; j < k; j++) {
            int dd = dist(offices[i], offices[j]);
            if (dd < d)
                quitf(_wa, "Distance between offices %d and %d is %d, need at least %d",
                      offices[i], offices[j], dd, d);
        }
    }

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid maximum office placement with %d offices", k);
}
