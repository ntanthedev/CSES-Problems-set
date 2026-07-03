/*

* Problem:      1667 Message Route
* Input read:   n, m; m undirected connections
* Validity:     IMPOSSIBLE iff jury says no route; otherwise k vertices, starting at 1,
* ```
            ending at n, and every consecutive pair is an input connection
* Optimality:   k must equal the shortest route length from ans
* Complexity:   O(n + m) expected time, O(n + m) memory
  */
  #include "testlib.h"
  #include <bits/stdc++.h>
  using namespace std;

static long long edge_key(int u, int v, int n) {
if (u > v) swap(u, v);
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

static int parse_jury_positive_int_token(const string& tok, int lo, int hi, const char* name) {
if (tok.empty()) {
quitf(_fail, "jury %s is empty", name);
}

long long val = 0;
for (char ch : tok) {
    if (ch < '0' || ch > '9') {
        quitf(_fail, "jury %s is malformed: '%s'", name, compress(tok).c_str());
    }

    val = val * 10 + (ch - '0');
    if (val > hi) {
        quitf(_fail, "jury %s is %lld, out of range [%d,%d]", name, val, lo, hi);
    }
}

if (val < lo) {
    quitf(_fail, "jury %s is %lld, out of range [%d,%d]", name, val, lo, hi);
}

return (int)val;

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

int optimal = parse_jury_positive_int_token(ansTok, 2, n, "route length");

string firstOut = ouf.readToken();
if (firstOut == "IMPOSSIBLE") {
    quitf(_wa, "a route exists, but contestant printed IMPOSSIBLE");
}

int k = parse_positive_int_token(firstOut, 2, n, "route length");

if (k != optimal) {
    quitf(_wa, "route length is %d, but shortest route length is %d", k, optimal);
}

vector<int> route(k);
for (int i = 0; i < k; i++) {
    route[i] = ouf.readInt(1, n, format("route[%d]", i + 1).c_str());
}

if (route.front() != 1) {
    quitf(_wa, "route must start at computer 1, but starts at computer %d", route.front());
}

if (route.back() != n) {
    quitf(_wa, "route must end at computer %d, but ends at computer %d", n, route.back());
}

for (int i = 0; i + 1 < k; i++) {
    int u = route[i];
    int v = route[i + 1];

    if (!edges.count(edge_key(u, v, n))) {
        quitf(_wa, "no connection between %d and %d at route step %d", u, v, i + 1);
    }
}

if (!ouf.seekEof())
    quitf(_wa, "extra information in the output file");

quitf(_ok, "valid shortest route of length %d", k);

}
