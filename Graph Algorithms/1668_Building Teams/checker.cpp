/*

* Problem:      1668 Building Teams
* Input read:   n, m; m undirected friendships
* Validity:     IMPOSSIBLE iff jury says not bipartite; otherwise n team labels in {1,2},
* ```
            and every friendship connects pupils in different teams
* Optimality:   Feasibility is taken from ans; any valid 2-coloring is accepted
* Complexity:   O(n + m) time, O(n + m) memory
  */
  #include "testlib.h"
  #include <bits/stdc++.h>
  using namespace std;

static int parse_team_token(const string& tok, const char* name) {
if (tok == "1") return 1;
if (tok == "2") return 2;

quitf(_wa, "expected team label 1 or 2 for %s, got '%s'",
      name, compress(tok).c_str());

}

int main(int argc, char* argv[]) {
registerTestlibCmd(argc, argv);

int n = inf.readInt();
int m = inf.readInt();

vector<pair<int, int>> friendships;
friendships.reserve(m);

for (int i = 0; i < m; i++) {
    int a = inf.readInt();
    int b = inf.readInt();
    friendships.push_back({a, b});
}

string ansTok = ans.readToken();

if (ansTok == "IMPOSSIBLE") {
    string outTok = ouf.readToken();

    if (outTok != "IMPOSSIBLE") {
        quitf(_wa, "jury answer is IMPOSSIBLE but contestant printed '%s'",
              compress(outTok).c_str());
    }

    if (!ouf.seekEof())
        quitf(_wa, "extra information in the output file");

    quitf(_ok, "correctly reported IMPOSSIBLE");
}

vector<int> team(n + 1);

string firstOut = ouf.readToken();
if (firstOut == "IMPOSSIBLE") {
    quitf(_wa, "a valid team assignment exists, but contestant printed IMPOSSIBLE");
}

team[1] = parse_team_token(firstOut, "team[1]");

for (int i = 2; i <= n; i++) {
    team[i] = ouf.readInt(1, 2, format("team[%d]", i).c_str());
}

for (auto [a, b] : friendships) {
    if (team[a] == team[b]) {
        quitf(_wa, "friendship %d-%d connects pupils in the same team %d",
              a, b, team[a]);
    }
}

if (!ouf.seekEof())
    quitf(_wa, "extra information in the output file");

quitf(_ok, "valid 2-coloring for %d pupils", n);

}
