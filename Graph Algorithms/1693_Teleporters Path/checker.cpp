/*
 * HEADER CONTRACT
 * Problem:      1693 Teleporters Path
 * Input read:   n, m; m directed teleporters (a, b), distinct pairs
 * Validity:     IMPOSSIBLE if no Eulerian trail 1->n using all teleporters;
 *               else m+1 levels in [1,n], route[0]=1, route[m]=n,
 *               each input teleporter used exactly once in order
 * Optimality:   any valid Eulerian path (no scalar from ans)
 * Complexity:   O(n + m log m) time, O(n + m) memory
 */
#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = inf.readInt();
    multiset<pair<int, int>> teleporters;
    for (int i = 0; i < m; i++) {
        int a = inf.readInt();
        int b = inf.readInt();
        teleporters.insert({a, b});
    }

    string ansTok = ans.readToken();
    if (ansTok == "IMPOSSIBLE") {
        string oufTok = ouf.readToken();
        if (oufTok != "IMPOSSIBLE")
            quitf(_wa, "jury answer is IMPOSSIBLE but contestant printed \"%s\" "
                       "(claims a winning teleporter path exists)",
                  compress(oufTok).c_str());
        if (!ouf.seekEof())
            quitf(_wa, "extra information in the output file");
        quitf(_ok, "correctly reported IMPOSSIBLE");
    }

    string oufFirst = ouf.readToken();
    if (oufFirst == "IMPOSSIBLE")
        quitf(_wa, "jury has a valid teleporter path but contestant printed IMPOSSIBLE");

    auto readLevel = [&](const string &t, const char *name) -> int {
        if (t.empty())
            quitf(_wa, "%s is empty", name);
        long long v = 0;
        for (char c : t) {
            if (c < '0' || c > '9')
                quitf(_wa, "%s must be an integer in [1,%d], got \"%s\"", name, n, compress(t).c_str());
            v = v * 10 + (c - '0');
            if (v > n)
                quitf(_wa, "%s = %lld is out of range [1,%d]", name, v, n);
        }
        if (v < 1)
            quitf(_wa, "%s = %lld is out of range [1,%d]", name, v, n);
        return (int)v;
    };

    int routeLen = m + 1;
    vector<int> route(routeLen);
    route[0] = readLevel(oufFirst, "level[1]");
    for (int i = 1; i < routeLen; i++)
        route[i] = ouf.readInt(1, n, format("level[%d]", i + 1).c_str());

    if (route[0] != 1)
        quitf(_wa, "path must start at level 1, contestant starts at %d", route[0]);
    if (route[m] != n)
        quitf(_wa, "path must end at level %d, contestant ends at %d", n, route[m]);

    multiset<pair<int, int>> remaining = teleporters;
    for (int i = 0; i < m; i++) {
        int u = route[i], v = route[i + 1];
        auto it = remaining.find({u, v});
        if (it == remaining.end())
            quitf(_wa, "teleporter %d->%d on step %d does not exist or was already used", u, v, i + 1);
        remaining.erase(it);
    }

    if (!remaining.empty())
        quitf(_wa, "contestant path does not use all %d teleporters", m);

    if (!ouf.seekEof())
        quitf(_wa, "extra information in the output file");
    quitf(_ok, "valid teleporter path using all %d teleporters", m);
}
