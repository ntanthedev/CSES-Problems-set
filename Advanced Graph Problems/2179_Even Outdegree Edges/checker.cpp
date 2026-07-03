#include "testlib.h"
#include <vector>
#include <string>
#include <map>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = inf.readInt();
    map<pair<int, int>, int> edgeCnt;
    for (int i = 0; i < m; i++) {
        int a = inf.readInt();
        int b = inf.readInt();
        pair<int, int> key = {min(a, b), max(a, b)};
        edgeCnt[key]++;
    }

    string ansTok = ans.readToken();
    string outTok = ouf.readToken();

    if (outTok == "IMPOSSIBLE") {
        if (ansTok != "IMPOSSIBLE")
            quitf(_wa, "Output is IMPOSSIBLE but a valid orientation exists");
        if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
        quitf(_ok, "Correct: impossible");
    }

    if (ansTok == "IMPOSSIBLE")
        quitf(_wa, "A valid orientation exists but output is IMPOSSIBLE");

    map<pair<int, int>, int> used = edgeCnt;
    vector<int> outdeg(n + 1, 0);

    auto add_edge = [&](int a, int b) {
        if (a < 1 || a > n || b < 1 || b > n)
            quitf(_wa, "Node %d or %d out of range [1,%d]", a, b, n);
        pair<int, int> key = {min(a, b), max(a, b)};
        if (!used.count(key) || used[key] == 0)
            quitf(_wa, "Edge %d %d not in original graph", a, b);
        used[key]--;
        outdeg[a]++;
    };

    int a = stoi(outTok);
    int b = ouf.readInt();
    add_edge(a, b);
    for (int i = 1; i < m; i++) {
        int x = ouf.readInt();
        int y = ouf.readInt();
        add_edge(x, y);
    }

    for (auto [key, cnt] : used) {
        if (cnt != 0)
            quitf(_wa, "Not all original edges are oriented");
    }

    ans.readInt();
    for (int i = 1; i < m; i++)
        ans.readInt(), ans.readInt();

    for (int i = 1; i <= n; i++) {
        if (outdeg[i] % 2 != 0)
            quitf(_wa, "Node %d has odd outdegree %d", i, outdeg[i]);
    }

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid orientation with all even outdegrees");
}
