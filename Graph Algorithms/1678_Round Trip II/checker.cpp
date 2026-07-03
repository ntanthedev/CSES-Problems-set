/*
 * HEADER CONTRACT
 * Problem:      1678 Round Trip II
 * Input read:   n, m; m directed flights (a, b)
 * Validity:     IMPOSSIBLE if no directed cycle; else k then k cities in [1,n],
 *               first equals last, intermediate cities distinct,
 *               each consecutive pair is a directed flight in the input
 * Optimality:   any valid directed cycle (no scalar from ans)
 * Complexity:   O(n + m) time, O(n + m) memory
 */
#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = inf.readInt();
    multiset<pair<int, int>> flights;
    for (int i = 0; i < m; i++) {
        int a = inf.readInt();
        int b = inf.readInt();
        flights.insert({a, b});
    }

    string ansTok = ans.readToken();
    if (ansTok == "IMPOSSIBLE") {
        string oufTok = ouf.readToken();
        if (oufTok != "IMPOSSIBLE")
            quitf(_wa, "jury answer is IMPOSSIBLE but contestant printed \"%s\" "
                       "(claims a directed cycle exists)",
                  compress(oufTok).c_str());
        if (!ouf.seekEof())
            quitf(_wa, "extra information in the output file");
        quitf(_ok, "correctly reported IMPOSSIBLE");
    }

    int k = ouf.readInt(2, n + 1, "k");
    vector<int> cycle(k);
    for (int i = 0; i < k; i++)
        cycle[i] = ouf.readInt(1, n, format("city[%d]", i + 1).c_str());

    if (cycle[0] != cycle[k - 1])
        quitf(_wa, "cycle must start and end at the same city (got %d and %d)",
              cycle[0], cycle[k - 1]);

    multiset<pair<int, int>> remaining = flights;
    for (int i = 0; i + 1 < k; i++) {
        int u = cycle[i], v = cycle[i + 1];
        auto it = remaining.find({u, v});
        if (it == remaining.end())
            quitf(_wa, "no directed flight from %d to %d on cycle step %d", u, v, i + 1);
        remaining.erase(it);
    }

    vector<bool> seen(n + 1, false);
    for (int i = 0; i < k - 1; i++) {
        if (seen[cycle[i]])
            quitf(_wa, "city %d appears more than once among intermediate cities", cycle[i]);
        seen[cycle[i]] = true;
    }

    if (!ouf.seekEof())
        quitf(_wa, "extra information in the output file");
    quitf(_ok, "valid directed cycle of length %d", k);
}
