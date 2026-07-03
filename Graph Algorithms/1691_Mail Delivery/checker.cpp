#include "testlib.h"
#include <vector>
#include <string>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = inf.readInt();
    vector<set<int>> g(n + 1);
    vector<pair<int, int>> edges;
    for (int i = 0; i < m; i++) {
        int a = inf.readInt();
        int b = inf.readInt();
        g[a].insert(b);
        g[b].insert(a);
        edges.push_back({a, b});
    }

    string ansFirst = ans.readToken();
    string outFirst = ouf.readToken();

    if (outFirst == "IMPOSSIBLE") {
        if (ansFirst != "IMPOSSIBLE")
            quitf(_wa, "Output is IMPOSSIBLE but an Eulerian circuit exists");
        if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
        quitf(_ok, "Correct: no Eulerian circuit");
    }

    if (ansFirst == "IMPOSSIBLE")
        quitf(_wa, "An Eulerian circuit exists but output is IMPOSSIBLE");

    int start = stoi(outFirst);
    if (start < 1 || start > n)
        quitf(_wa, "Start crossing %d out of range", start);

    vector<int> route;
    route.push_back(start);
    for (int i = 1; i <= m; i++)
        route.push_back(ouf.readInt(1, n));

    if ((int)route.size() != m + 1)
        quitf(_wa, "Route has %d crossings, expected %d", (int)route.size(), m + 1);

    if (route[0] != 1)
        quitf(_wa, "Route must start at crossing 1, got %d", route[0]);
    if (route[m] != 1)
        quitf(_wa, "Route must end at crossing 1, got %d", route[m]);

    vector<set<int>> used(n + 1);
    for (int i = 0; i < m; i++) {
        int u = route[i], v = route[i + 1];
        if (!g[u].count(v))
            quitf(_wa, "No street between %d and %d in route", u, v);
        int a = min(u, v), b = max(u, v);
        if (used[a].count(b))
            quitf(_wa, "Street %d-%d used more than once", a, b);
        used[a].insert(b);
    }

    for (auto [a, b] : edges) {
        int mn = min(a, b), mx = max(a, b);
        if (!used[mn].count(mx))
            quitf(_wa, "Street %d-%d not visited", a, b);
    }

    for (int i = 0; i < m; i++)
        ans.readInt();

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid Eulerian circuit with %d edges", m);
}
