/*
 * HEADER CONTRACT
 * Problem:      1667 Message Route
 * Input read:   n, m; m undirected edges (a, b)
 * Validity:     IMPOSSIBLE if no 1->n path; else k then route of k vertices in [1,n],
 *               route[0]=1, route[k-1]=n, consecutive vertices adjacent in input graph
 * Optimality:   k equals jury optimum (first token of ans)
 * Complexity:   O(n + m) time, O(n + m) memory
 */
#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = inf.readInt();
    set<pair<int, int>> edges;
    for (int i = 0; i < m; i++) {
        int a = inf.readInt();
        int b = inf.readInt();
        int u = min(a, b), v = max(a, b);
        edges.insert({u, v});
    }

    string ansTok = ans.readToken();
    if (ansTok == "IMPOSSIBLE") {
        string oufTok = ouf.readToken();
        if (oufTok != "IMPOSSIBLE")
            quitf(_wa, "jury answer is IMPOSSIBLE but contestant printed \"%s\" "
                       "(claims a route exists)",
                  compress(oufTok).c_str());
        if (!ouf.seekEof())
            quitf(_wa, "extra information in the output file");
        quitf(_ok, "correctly reported IMPOSSIBLE");
    }

    int kAns = stoi(ansTok);
    int k = ouf.readInt(2, n, "k");
    vector<int> route(k);
    for (int i = 0; i < k; i++)
        route[i] = ouf.readInt(1, n, format("route[%d]", i + 1).c_str());

    if (k != kAns)
        quitf(_wa, "not optimal: contestant k = %d, jury k = %d", k, kAns);

    if (route[0] != 1)
        quitf(_wa, "route must start at computer 1, contestant starts at %d", route[0]);
    if (route[k - 1] != n)
        quitf(_wa, "route must end at computer %d, contestant ends at %d", n, route[k - 1]);

    for (int i = 0; i + 1 < k; i++) {
        int u = route[i], v = route[i + 1];
        int a = min(u, v), b = max(u, v);
        if (!edges.count({a, b}))
            quitf(_wa, "no connection between %d and %d on route step %d", u, v, i + 1);
    }

    if (!ouf.seekEof())
        quitf(_wa, "extra information in the output file");
    quitf(_ok, "valid shortest route of length %d", k);
}
