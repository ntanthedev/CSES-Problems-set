#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

struct BridgeChecker {
    vector<vector<int>> g;
    vector<pair<int, int>> edges;
    vector<int> tin, low;
    int timer = 0;
    bool has_bridge = false;

    void add_edge(int a, int b) {
        int id = (int)edges.size();
        edges.push_back({a, b});
        g[a].push_back(id);
        g[b].push_back(id);
    }

    int other(int u, int ei) const {
        return edges[ei].first ^ edges[ei].second ^ u;
    }

    void dfs(int u, int pe) {
        tin[u] = low[u] = ++timer;
        for (int ei : g[u]) {
            if (ei == pe)
                continue;
            int v = other(u, ei);
            if (tin[v]) {
                low[u] = min(low[u], tin[v]);
            } else {
                dfs(v, ei);
                low[u] = min(low[u], low[v]);
                if (low[v] > tin[u])
                    has_bridge = true;
            }
        }
    }

    void run(int n) {
        tin.assign(n + 1, 0);
        low.assign(n + 1, 0);
        timer = 0;
        has_bridge = false;
        dfs(1, -1);
    }
};

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    BridgeChecker bc;
    bc.g.assign(n + 1, {});
    for (int i = 0; i < n - 1; i++) {
        int a = inf.readInt();
        int b = inf.readInt();
        bc.add_edge(a, b);
    }

    int k_ans = ans.readInt();
    int k = ouf.readInt();
    if (k != k_ans)
        quitf(_wa, "Claimed %d new connections but optimal is %d", k, k_ans);
    if (k < 0)
        quitf(_wa, "k=%d is negative", k);

    for (int i = 0; i < k; i++) {
        int a = ouf.readInt();
        int b = ouf.readInt();
        if (a < 1 || a > n)
            quitf(_wa, "Computer %d out of range", a);
        if (b < 1 || b > n)
            quitf(_wa, "Computer %d out of range", b);
        if (a == b)
            quitf(_wa, "Cannot connect a computer to itself");
        bc.add_edge(a, b);
    }

    bc.run(n);
    if (bc.has_bridge)
        quitf(_wa, "Graph still has bridges after adding new connections");

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid minimum solution with %d new connections", k);
}
