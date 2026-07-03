#include "testlib.h"
#include <set>
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = inf.readInt();
    vector<pair<int, int>> edges;
    for (int i = 0; i < m; i++) {
        int a = inf.readInt();
        int b = inf.readInt();
        edges.push_back({a, b});
    }

    string ansFirst = ans.readToken();
    string outFirst = ouf.readToken();

    if (outFirst == "IMPOSSIBLE") {
        if (ansFirst != "IMPOSSIBLE")
            quitf(_wa, "Output is IMPOSSIBLE but an Eulerian path exists");
        if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
        quitf(_ok, "Correct: no Eulerian path");
    }

    if (ansFirst == "IMPOSSIBLE")
        quitf(_wa, "An Eulerian path exists but output is IMPOSSIBLE");

    int start = stoi(outFirst);
    if (start < 1 || start > n)
        quitf(_wa, "Start level %d out of range", start);

    vector<int> route;
    route.push_back(start);
    for (int i = 1; i <= m; i++)
        route.push_back(ouf.readInt(1, n));

    if ((int)route.size() != m + 1)
        quitf(_wa, "Route has %d levels, expected %d", (int)route.size(), m + 1);

    if (route[0] != 1)
        quitf(_wa, "Route must start at level 1, got %d", route[0]);
    if (route[m] != n)
        quitf(_wa, "Route must end at level %d, got %d", n, route[m]);

    multiset<pair<int, int>> remaining(edges.begin(), edges.end());
    for (int i = 0; i < m; i++) {
        int u = route[i], v = route[i + 1];
        auto it = remaining.find({u, v});
        if (it == remaining.end())
            quitf(_wa, "No teleporter from %d to %d (or already used)", u, v);
        remaining.erase(it);
    }

    if (!remaining.empty())
        quitf(_wa, "Not all teleporters were used");

    for (int i = 0; i < m; i++)
        ans.readInt();

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid Eulerian path using %d teleporters", m);
}
