#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = inf.readInt();
    vector<vector<int>> g(n + 1);
    for (int i = 0; i < m; i++) {
        int a = inf.readInt();
        int b = inf.readInt();
        g[a].push_back(b);
        g[b].push_back(a);
    }

    string ansFirst = ans.readToken();
    string outFirst = ouf.readToken();

    if (outFirst == "IMPOSSIBLE") {
        if (ansFirst != "IMPOSSIBLE")
            quitf(_wa, "Output is IMPOSSIBLE but a cycle exists");
        if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
        quitf(_ok, "Correct: no cycle");
    }

    if (ansFirst == "IMPOSSIBLE")
        quitf(_wa, "A cycle exists but output is IMPOSSIBLE");

    int k = stoi(outFirst);
    if (k < 3)
        quitf(_wa, "Cycle must have at least 3 cities, got %d", k);

    vector<int> cycle(k);
    for (int i = 0; i < k; i++) {
        cycle[i] = ouf.readInt();
        if (cycle[i] < 1 || cycle[i] > n)
            quitf(_wa, "City %d out of range", cycle[i]);
    }

    if (cycle[0] != cycle[k - 1])
        quitf(_wa, "Cycle must start and end at the same city");

    for (int i = 0; i + 1 < k; i++) {
        int u = cycle[i], v = cycle[i + 1];
        bool found = false;
        for (int w : g[u])
            if (w == v) {
                found = true;
                break;
            }
        if (!found)
            quitf(_wa, "No road between %d and %d in cycle", u, v);
    }

    vector<bool> seen(n + 1, false);
    for (int i = 0; i < k - 1; i++) {
        if (seen[cycle[i]])
            quitf(_wa, "City %d appears more than once in the cycle", cycle[i]);
        seen[cycle[i]] = true;
    }

    int ansK = stoi(ansFirst);
    for (int i = 0; i < ansK; i++)
        ans.readInt();

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid cycle of length %d", k);
}
