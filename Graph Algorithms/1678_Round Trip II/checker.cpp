/*

* Problem:      1678 Round Trip II
* Input read:   n, m; m directed flights
* Validity:     IMPOSSIBLE iff jury says no directed cycle; otherwise k >= 3 cities,
* ```
            first equals last, the k-1 listed cities are distinct, and every
* ```
            consecutive pair is an input directed flight
* Optimality:   Feasibility is taken from ans; any valid directed cycle is accepted
* Complexity:   O(n + m) expected time, O(n + m) memory
  */
  #include "testlib.h"
  #include <bits/stdc++.h>
  using namespace std;

static long long edge_key(int u, int v, int n) {
return 1LL * u * (n + 1LL) + v;
}

static int parse_positive_int_token(const string& tok, int lo, int hi, const char* name) {
if (tok.empty()) {
quitf(_wa, "%s is empty", name);
}

long long val = 0;
for (char ch : tok) {
    if (ch < '0' || ch > '9') {
        quitf(_wa, "expected integer %s, got '%s'", name, compress(tok).c_str());
    }

    val = val * 10 + (ch - '0');
    if (val > hi) {
        quitf(_wa, "%s is %lld, out of range [%d,%d]", name, val, lo, hi);
    }
}

if (val < lo) {
    quitf(_wa, "%s is %lld, out of range [%d,%d]", name, val, lo, hi);
}

return (int)val;

}

int main(int argc, char* argv[]) {
registerTestlibCmd(argc, argv);

int n = inf.readInt();
int m = inf.readInt();

unordered_set<long long> flights;
flights.reserve((size_t)m * 2 + 10);

for (int i = 0; i < m; i++) {
    int a = inf.readInt();
    int b = inf.readInt();
    flights.insert(edge_key(a, b, n));
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

string firstOut = ouf.readToken();
if (firstOut == "IMPOSSIBLE") {
    quitf(_wa, "a directed cycle exists, but contestant printed IMPOSSIBLE");
}

int k = parse_positive_int_token(firstOut, 3, n + 1, "k");

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

    if (!flights.count(edge_key(u, v, n))) {
        quitf(_wa, "no directed flight from %d to %d at cycle step %d",
              u, v, i + 1);
    }
}

if (!ouf.seekEof())
    quitf(_wa, "extra information in the output file");

quitf(_ok, "valid directed cycle with %d listed cities", k);

}
