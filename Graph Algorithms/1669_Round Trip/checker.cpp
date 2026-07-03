/*

* Problem:      1669 Round Trip
* Input read:   n, m; m undirected roads
* Validity:     IMPOSSIBLE iff jury says no cycle; otherwise k cities with k >= 4,
* ```
            first equals last, k-1 distinct visited cities, and every consecutive
* ```
            pair is an input road
* Optimality:   Feasibility is taken from ans; any valid cycle is accepted
* Complexity:   O(n + m) expected time, O(n + m) memory
  */
  #include "testlib.h"
  #include <bits/stdc++.h>
  using namespace std;

static long long edge_key(int u, int v, int n) {
if (u > v) swap(u, v);
return 1LL * u * (n + 1LL) + v;
}

int main(int argc, char* argv[]) {
registerTestlibCmd(argc, argv);

int n = inf.readInt();
int m = inf.readInt();

unordered_set<long long> edges;
edges.reserve((size_t)m * 2 + 10);

for (int i = 0; i < m; i++) {
    int a = inf.readInt();
    int b = inf.readInt();
    edges.insert(edge_key(a, b, n));
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

int k = ouf.readInt(4, n + 1, "k");

vector<int> cycle(k);
for (int i = 0; i < k; i++) {
    cycle[i] = ouf.readInt(1, n, format("city[%d]", i + 1).c_str());
}

if (cycle.front() != cycle.back()) {
    quitf(_wa, "cycle must start and end at the same city, got %d and %d",
          cycle.front(), cycle.back());
}

vector<char> seen(n + 1, 0);
for (int i = 0; i < k - 1; i++) {
    int v = cycle[i];
    if (seen[v]) {
        quitf(_wa, "city %d appears more than once before the final return", v);
    }
    seen[v] = 1;
}

for (int i = 0; i + 1 < k; i++) {
    int u = cycle[i];
    int v = cycle[i + 1];
    if (!edges.count(edge_key(u, v, n))) {
        quitf(_wa, "no road between city %d and city %d at step %d",
              u, v, i + 1);
    }
}

if (!ouf.seekEof())
    quitf(_wa, "extra information in the output file");

quitf(_ok, "valid cycle with %d listed cities", k);

}
