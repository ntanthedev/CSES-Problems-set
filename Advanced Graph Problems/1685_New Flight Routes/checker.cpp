#include "testlib.h"
#include <vector>
using namespace std;

void dfs1(int u, const vector<vector<int>>& g, vector<bool>& vis, vector<int>& order) {
    vis[u] = true;
    for (int v : g[u])
        if (!vis[v])
            dfs1(v, g, vis, order);
    order.push_back(u);
}

void dfs2(int u, const vector<vector<int>>& rg, vector<bool>& vis, int& cnt) {
    vis[u] = true;
    ++cnt;
    for (int v : rg[u])
        if (!vis[v])
            dfs2(v, rg, vis, cnt);
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = inf.readInt();
    vector<vector<int>> g(n + 1), rg(n + 1);
    for (int i = 0; i < m; i++) {
        int a = inf.readInt();
        int b = inf.readInt();
        g[a].push_back(b);
        rg[b].push_back(a);
    }

    int k_ans = ans.readInt();
    int k = ouf.readInt();
    if (k != k_ans)
        quitf(_wa, "Claimed %d new flights but optimal is %d", k, k_ans);
    if (k < 0)
        quitf(_wa, "k=%d is negative", k);

    for (int i = 0; i < k; i++) {
        int a = ouf.readInt();
        int b = ouf.readInt();
        if (a < 1 || a > n)
            quitf(_wa, "City %d out of range", a);
        if (b < 1 || b > n)
            quitf(_wa, "City %d out of range", b);
        g[a].push_back(b);
        rg[b].push_back(a);
    }

    vector<bool> vis(n + 1, false);
    vector<int> order;
    for (int i = 1; i <= n; i++)
        if (!vis[i])
            dfs1(i, g, vis, order);

    fill(vis.begin(), vis.end(), false);
    int scc = 0;
    for (int i = (int)order.size() - 1; i >= 0; i--) {
        int v = order[i];
        if (!vis[v]) {
            int cnt = 0;
            dfs2(v, rg, vis, cnt);
            if (cnt > 0)
                ++scc;
        }
    }
    if (scc != 1)
        quitf(_wa, "Resulting graph has %d SCCs (not strongly connected)", scc);

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid minimum solution with %d new flights", k);
}
