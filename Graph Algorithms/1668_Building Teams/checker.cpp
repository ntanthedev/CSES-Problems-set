/*
 * HEADER CONTRACT
 * Problem:      1668 Building Teams
 * Input read:   n, m; m undirected friendships (a, b)
 * Validity:     IMPOSSIBLE if not 2-colorable; else n team labels in {1,2},
 *               no friendship connects two pupils in the same team
 * Optimality:   any valid 2-coloring (no scalar from ans)
 * Complexity:   O(n + m) time, O(n + m) memory
 */
#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = inf.readInt();
    vector<pair<int, int>> friendships;
    for (int i = 0; i < m; i++) {
        int a = inf.readInt();
        int b = inf.readInt();
        friendships.push_back({a, b});
    }

    string ansTok = ans.readToken();
    if (ansTok == "IMPOSSIBLE") {
        string oufTok = ouf.readToken();
        if (oufTok != "IMPOSSIBLE")
            quitf(_wa, "jury answer is IMPOSSIBLE but contestant printed \"%s\" "
                       "(claims a valid team assignment exists)",
                  compress(oufTok).c_str());
        if (!ouf.seekEof())
            quitf(_wa, "extra information in the output file");
        quitf(_ok, "correctly reported IMPOSSIBLE");
    }

    vector<int> team(n + 1);
    team[1] = ouf.readInt(1, 2, "team[1]");
    for (int i = 2; i <= n; i++)
        team[i] = ouf.readInt(1, 2, format("team[%d]", i).c_str());

    for (auto [a, b] : friendships) {
        if (team[a] == team[b])
            quitf(_wa, "friendship %d-%d connects pupils in the same team %d", a, b, team[a]);
    }

    if (!ouf.seekEof())
        quitf(_wa, "extra information in the output file");
    quitf(_ok, "valid 2-coloring for %d pupils", n);
}
