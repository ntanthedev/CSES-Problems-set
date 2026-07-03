/*
 * HEADER CONTRACT
 * Problem:      1691 Mail Delivery
 * Input read:   n, m; m undirected streets (a, b), post office at crossing 1
 * Validity:     IMPOSSIBLE if no Eulerian circuit at 1; else m+1 crossings in [1,n],
 *               route[0]=route[m]=1, each input street used exactly once
 * Optimality:   any valid Eulerian circuit (no scalar from ans)
 * Complexity:   O(n + m log m) time, O(n + m) memory
 */
#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = inf.readInt();
    multiset<pair<int, int>> streets;
    for (int i = 0; i < m; i++) {
        int a = inf.readInt();
        int b = inf.readInt();
        int u = min(a, b), v = max(a, b);
        streets.insert({u, v});
    }

    string ansTok = ans.readToken();
    if (ansTok == "IMPOSSIBLE") {
        string oufTok = ouf.readToken();
        if (oufTok != "IMPOSSIBLE")
            quitf(_wa, "jury answer is IMPOSSIBLE but contestant printed \"%s\" "
                       "(claims an Eulerian circuit exists)",
                  compress(oufTok).c_str());
        if (!ouf.seekEof())
            quitf(_wa, "extra information in the output file");
        quitf(_ok, "correctly reported IMPOSSIBLE");
    }

    string oufFirst = ouf.readToken();
    if (oufFirst == "IMPOSSIBLE")
        quitf(_wa, "jury has a valid Eulerian circuit but contestant printed IMPOSSIBLE");

    auto readVertex = [&](const string &t, const char *name) -> int {
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
    route[0] = readVertex(oufFirst, "route[1]");
    for (int i = 1; i < routeLen; i++)
        route[i] = ouf.readInt(1, n, format("route[%d]", i + 1).c_str());

    if (route[0] != 1)
        quitf(_wa, "route must start at crossing 1, contestant starts at %d", route[0]);
    if (route[m] != 1)
        quitf(_wa, "route must end at crossing 1, contestant ends at %d", route[m]);

    multiset<pair<int, int>> remaining = streets;
    for (int i = 0; i < m; i++) {
        int u = route[i], v = route[i + 1];
        int a = min(u, v), b = max(u, v);
        auto it = remaining.find({a, b});
        if (it == remaining.end())
            quitf(_wa, "street %d-%d on step %d does not exist or was already used", u, v, i + 1);
        remaining.erase(it);
    }

    if (!remaining.empty())
        quitf(_wa, "contestant route does not use all %d streets", m);

    if (!ouf.seekEof())
        quitf(_wa, "extra information in the output file");
    quitf(_ok, "valid Eulerian circuit with %d streets", m);
}
