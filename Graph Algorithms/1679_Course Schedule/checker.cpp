#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
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
    if (ansTok != "IMPOSSIBLE") {
        int v = stoi(ansTok);
        if (v < 1 || v > n)
            quitf(_fail, "Invalid judge answer token '%s'", ansTok.c_str());
    }

    string outTok = ouf.readToken();
    if (outTok == "IMPOSSIBLE") {
        if (ansTok != "IMPOSSIBLE")
            quitf(_wa, "Output is IMPOSSIBLE but a valid course order exists");
        if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
        quitf(_ok, "Correct: no valid course order");
    }

    if (ansTok == "IMPOSSIBLE")
        quitf(_wa, "A valid course order exists but output is IMPOSSIBLE");

    vector<int> order(n);
    order[0] = stoi(outTok);
    if (order[0] < 1 || order[0] > n)
        quitf(_wa, "Course %d out of range [1,%d]", order[0], n);

    for (int i = 1; i < n; i++) {
        order[i] = ouf.readInt();
        if (order[i] < 1 || order[i] > n)
            quitf(_wa, "Course %d out of range [1,%d]", order[i], n);
    }

    for (int i = 1; i < n; i++)
        ans.readInt();

    vector<bool> seen(n + 1, false);
    for (int x : order) {
        if (seen[x])
            quitf(_wa, "Course %d appears more than once", x);
        seen[x] = true;
    }
    for (int i = 1; i <= n; i++) {
        if (!seen[i])
            quitf(_wa, "Course %d is missing from the order", i);
    }

    vector<int> pos(n + 1);
    for (int i = 0; i < n; i++)
        pos[order[i]] = i;

    for (auto [a, b] : requirements) {
        if (pos[a] >= pos[b])
            quitf(_wa, "Requirement %d before %d violated", a, b);
    }

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid topological order of %d courses", n);
}
