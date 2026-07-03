#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> g, rg;
vector<int> order, comp;
vector<char> seen;
int n;

void dfs1(int u) {
    seen[u] = 1;
    for (int v : g[u]) {
        if (!seen[v])
            dfs1(v);
    }
    order.push_back(u);
}

void dfs2(int u, int id) {
    comp[u] = id;
    for (int v : rg[u]) {
        if (!comp[v])
            dfs2(v, id);
    }
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    int m = inf.readInt();
    g.assign(n + 1, {});
    rg.assign(n + 1, {});
    for (int i = 0; i < m; i++) {
        int a = inf.readInt();
        int b = inf.readInt();
        g[a].push_back(b);
        rg[b].push_back(a);
    }

    int k_ans = ans.readInt();
    int k = ouf.readInt();
    if (k != k_ans)
        quitf(_wa, "Claimed %d kingdoms but optimal is %d", k, k_ans);
    if (k < 1 || k > n)
        quitf(_wa, "Number of kingdoms %d out of range [1,%d]", k, n);

    vector<int> label(n + 1);
    vector<bool> used(k + 1, false);
    for (int i = 1; i <= n; i++) {
        label[i] = ouf.readInt();
        if (label[i] < 1 || label[i] > k)
            quitf(_wa, "Kingdom label for planet %d is %d, must be in [1,%d]", i, label[i], k);
        used[label[i]] = true;
    }

    for (int j = 1; j <= k; j++) {
        if (!used[j])
            quitf(_wa, "Kingdom %d is not assigned to any planet", j);
    }

    for (int i = 1; i <= n; i++)
        ans.readInt();

    order.clear();
    seen.assign(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        if (!seen[i])
            dfs1(i);
    }
    reverse(order.begin(), order.end());

    comp.assign(n + 1, 0);
    int compCnt = 0;
    for (int u : order) {
        if (!comp[u])
            dfs2(u, ++compCnt);
    }

    vector<int> compLabel(compCnt + 1, -1);
    vector<int> labelComp(k + 1, -1);
    for (int i = 1; i <= n; i++) {
        int c = comp[i];
        int l = label[i];
        if (compLabel[c] == -1)
            compLabel[c] = l;
        else if (compLabel[c] != l)
            quitf(_wa, "Planets in the same kingdom (SCC) have different labels");
        if (labelComp[l] == -1)
            labelComp[l] = c;
        else if (labelComp[l] != c)
            quitf(_wa, "Planets in the same labeled kingdom belong to different SCCs");
    }

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid kingdom assignment: %d kingdoms", k);
}
