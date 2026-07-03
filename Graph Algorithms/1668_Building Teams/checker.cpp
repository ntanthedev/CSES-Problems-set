#include "testlib.h"
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

    string ansTok = ans.readToken();
    if (ansTok != "IMPOSSIBLE" && (ansTok != "1" && ansTok != "2"))
        quitf(_fail, "Invalid judge answer token '%s'", ansTok.c_str());

    string outTok = ouf.readToken();
    if (outTok == "IMPOSSIBLE") {
        if (ansTok != "IMPOSSIBLE")
            quitf(_wa, "Output is IMPOSSIBLE but a valid team assignment exists");
        if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
        quitf(_ok, "Correct: no valid team assignment");
    }

    if (ansTok == "IMPOSSIBLE")
        quitf(_wa, "A valid team assignment exists but output is IMPOSSIBLE");

    vector<int> team(n + 1);
    team[1] = stoi(outTok);
    if (team[1] != 1 && team[1] != 2)
        quitf(_wa, "Team must be 1 or 2, got %d for pupil 1", team[1]);

    for (int i = 2; i <= n; i++) {
        team[i] = ouf.readInt();
        if (team[i] != 1 && team[i] != 2)
            quitf(_wa, "Team must be 1 or 2, got %d for pupil %d", team[i], i);
    }

    for (int i = 2; i <= n; i++)
        ans.readInt();

    for (auto [a, b] : edges) {
        if (team[a] == team[b])
            quitf(_wa, "Edge %d-%d connects pupils in same team %d", a, b, team[a]);
    }

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid 2-coloring");
}
