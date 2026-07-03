/*
 * Problem:      1197 Cycle Finding
 * Input read:   n, m; m directed edges (a, b, c)
 * Validity:     YES/NO matches existence; if YES: vertex sequence forms a directed
 *               cycle (repeated vertex, first equals last), each arc exists in the
 *               multigraph, total edge weight along cycle is negative
 * Optimality:   any valid negative cycle (no scalar from ans)
 * Complexity:   O(m + cycle length)
 */
#include "testlib.h"
#include <vector>
#include <string>
#include <map>
#include <utility>
using namespace std;
using ll = long long;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = inf.readInt();
    map<pair<int, int>, vector<ll>> edges;
    for (int i = 0; i < m; i++) {
        int a = inf.readInt();
        int b = inf.readInt();
        ll c = inf.readLong();
        edges[{a, b}].push_back(c);
    }

    string ansToken = ans.readToken();
    if (ansToken != "YES" && ansToken != "NO")
        quitf(_fail, "Invalid judge answer token '%s'", ansToken.c_str());

    string outToken = ouf.readToken();
    if (outToken == "NO") {
        if (ansToken != "NO")
            quitf(_wa, "Contestant printed NO but a negative cycle exists");
        if (!ouf.seekEof())
            quitf(_wa, "extra information in the output file");
        quitf(_ok, "correctly reported no negative cycle");
    }

    if (outToken != "YES")
        quitf(_wa, "Expected YES or NO, got '%s'", outToken.c_str());
    if (ansToken == "NO")
        quitf(_wa, "Contestant printed YES but no negative cycle exists");

    vector<int> cycle;
    while (!ouf.seekEof())
        cycle.push_back(ouf.readInt(1, n, "vertex"));

    if ((int)cycle.size() < 2)
        quitf(_wa, "Cycle must have at least 2 vertices");

    int cycleStart = -1;
    vector<int> firstOccurrence(n + 1, -1);
    for (int i = 0; i < (int)cycle.size(); i++) {
        int v = cycle[i];
        if (firstOccurrence[v] != -1) {
            cycleStart = firstOccurrence[v];
            break;
        }
        firstOccurrence[v] = i;
    }
    if (cycleStart == -1)
        quitf(_wa, "Cycle must repeat a vertex");
    if (cycle[cycleStart] != cycle.back())
        quitf(_wa, "First and last vertices of cycle must match");

    vector<int> actualCycle;
    for (int i = cycleStart; i < (int)cycle.size(); i++)
        actualCycle.push_back(cycle[i]);

    ll totalWeight = 0;
    for (int i = 0; i + 1 < (int)actualCycle.size(); i++) {
        int u = actualCycle[i], v = actualCycle[i + 1];
        auto it = edges.find({u, v});
        if (it == edges.end())
            quitf(_wa, "No edge from %d to %d in the cycle", u, v);
        ll best = it->second[0];
        for (ll w : it->second)
            best = min(best, w);
        totalWeight += best;
    }

    if (totalWeight >= 0)
        quitf(_wa, "Sum of edge weights in cycle is %lld, not negative", totalWeight);

    quitf(_ok, "valid negative cycle with total weight %lld", totalWeight);
}
