#include "testlib.h"
#include <vector>
#include <functional>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    vector<vector<int>> g(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int a = inf.readInt();
        int b = inf.readInt();
        g[a].push_back(b);
        g[b].push_back(a);
    }

    int c = ouf.readInt();
    if (c < 1 || c > n)
        quitf(_wa, "Node %d out of range [1,%d]", c, n);

    vector<int> sz(n + 1, 0);
    function<void(int, int)> dfs = [&](int u, int p) {
        sz[u] = 1;
        for (int v : g[u]) {
            if (v == p) continue;
            dfs(v, u);
            sz[u] += sz[v];
        }
    };
    dfs(c, -1);

    for (int v : g[c]) {
        if (sz[v] > n / 2)
            quitf(_wa, "Node %d is not a centroid: subtree through neighbor %d has size %d",
                  c, v, sz[v]);
    }

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid centroid %d", c);
}
