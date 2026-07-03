/*
 * HEADER CONTRACT
 * Problem:      1679 Course Schedule
 * Input read:   n, m; m requirements (a, b): course a before course b
 * Validity:     IMPOSSIBLE if no topological order; else permutation of 1..n
 *               with pos[a] < pos[b] for every requirement
 * Optimality:   any valid topological order (no scalar from ans)
 * Complexity:   O(n + m) time, O(n + m) memory
 */
#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = inf.readInt();
    vector<pair<int, int>> requirements;
    for (int i = 0; i < m; i++) {
        int a = inf.readInt();
        int b = inf.readInt();
        requirements.push_back({a, b});
    }

    string ansTok = ans.readToken();
    if (ansTok == "IMPOSSIBLE") {
        string oufTok = ouf.readToken();
        if (oufTok != "IMPOSSIBLE")
            quitf(_wa, "jury answer is IMPOSSIBLE but contestant printed \"%s\" "
                       "(claims a valid course order exists)",
                  compress(oufTok).c_str());
        if (!ouf.seekEof())
            quitf(_wa, "extra information in the output file");
        quitf(_ok, "correctly reported IMPOSSIBLE");
    }

    vector<int> order(n);
    order[0] = ouf.readInt(1, n, "course[1]");
    for (int i = 1; i < n; i++)
        order[i] = ouf.readInt(1, n, format("course[%d]", i + 1).c_str());

    vector<bool> seen(n + 1, false);
    for (int i = 0; i < n; i++) {
        if (seen[order[i]])
            quitf(_wa, "course %d appears more than once in the order", order[i]);
        seen[order[i]] = true;
    }
    for (int i = 1; i <= n; i++) {
        if (!seen[i])
            quitf(_wa, "course %d is missing from the order", i);
    }

    vector<int> pos(n + 1);
    for (int i = 0; i < n; i++)
        pos[order[i]] = i;

    for (auto [a, b] : requirements) {
        if (pos[a] >= pos[b])
            quitf(_wa, "requirement violated: course %d must come before course %d", a, b);
    }

    if (!ouf.seekEof())
        quitf(_wa, "extra information in the output file");
    quitf(_ok, "valid topological order of %d courses", n);
}
