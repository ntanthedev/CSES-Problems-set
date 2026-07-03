#include "testlib.h"
#include <vector>
#include <string>
#include <tuple>
using namespace std;
using ll = long long;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = inf.readInt();
    vector<tuple<int, int, ll>> edges;
    for (int i = 0; i < m; i++) {
        int a = inf.readInt();
        int b = inf.readInt();
        ll c = inf.readLong();
        edges.push_back({a, b, c});
    }

    string ans_token = ans.readToken();
    bool ans_yes = (ans_token == "YES");

    string out_token = ouf.readToken();
    if (out_token == "NO") {
        if (ans_yes)
            quitf(_wa, "Negative cycle exists but contestant printed NO");
        if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
        quitf(_ok, "Correct: no negative cycle");
    }

    if (out_token != "YES")
        quitf(_wa, "Expected YES or NO, got '%s'", out_token.c_str());
    if (!ans_yes)
        quitf(_wa, "No negative cycle exists but contestant printed YES");

    vector<int> cycle;
    while (!ouf.readEof()) {
        int x = ouf.readInt();
        if (x < 1 || x > n)
            quitf(_wa, "Vertex %d out of range", x);
        cycle.push_back(x);
    }

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
        quitf(_wa, "Cycle must repeat a vertex (no vertex appears twice)");
    if (cycle[cycleStart] != cycle.back())
        quitf(_wa, "First and last vertices of cycle must match");

    vector<int> actualCycle;
    for (int i = cycleStart; i < (int)cycle.size(); i++)
        actualCycle.push_back(cycle[i]);

    ll totalWeight = 0;
    for (int i = 0; i + 1 < (int)actualCycle.size(); i++) {
        int u = actualCycle[i], v = actualCycle[i + 1];
        bool found = false;
        ll w = 0;
        for (auto [a, b, c] : edges) {
            if (a == u && b == v) {
                found = true;
                w = c;
                break;
            }
        }
        if (!found)
            quitf(_wa, "No edge from %d to %d in the cycle", u, v);
        totalWeight += w;
    }

    if (totalWeight >= 0)
        quitf(_wa, "Sum of edge weights in cycle is %lld, not negative", totalWeight);

    quitf(_ok, "Valid negative cycle with total weight %lld", totalWeight);
}
