/*
 * HEADER CONTRACT
 * Problem:      1669 Round Trip
 * Input read:   n, m; m undirected roads (a, b)
 * Validity:     IMPOSSIBLE if no cycle; else k then k cities in [1,n],
 *               first equals last, intermediate cities distinct,
 *               consecutive cities connected by a road
 * Optimality:   any valid cycle (no scalar from ans)
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
                       "(claims a cycle exists)",
                  compress(oufTok).c_str());
        if (!ouf.seekEof())
            quitf(_wa, "extra information in the output file");
        quitf(_ok, "correctly reported IMPOSSIBLE");
    }

    int k = ouf.readInt(3, n + 1, "k");
    vector<int> cycle(k);
    for (int i = 0; i < k; i++)
        cycle[i] = ouf.readInt(1, n, format("city[%d]", i + 1).c_str());

    if (cycle[0] != cycle[k - 1])
        quitf(_wa, "cycle must start and end at the same city (got %d and %d)",
              cycle[0], cycle[k - 1]);

    for (int i = 0; i + 1 < k; i++) {
        int u = cycle[i], v = cycle[i + 1];
        int a = min(u, v), b = max(u, v);
        if (!edges.count({a, b}))
            quitf(_wa, "no road between %d and %d on cycle step %d", u, v, i + 1);
    }

    vector<bool> seen(n + 1, false);
    for (int i = 0; i < k - 1; i++) {
        if (seen[cycle[i]])
            quitf(_wa, "city %d appears more than once among intermediate cities", cycle[i]);
        seen[cycle[i]] = true;
    }

    if (!ouf.seekEof())
        quitf(_wa, "extra information in the output file");
    quitf(_ok, "valid cycle of length %d", k);
}
