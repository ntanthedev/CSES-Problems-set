/*

* Problem:      1679 Course Schedule
* Input read:   n, m; m requirements (a, b): course a before course b
* Validity:     IMPOSSIBLE iff jury says no topological order; otherwise a permutation
* ```
            of 1..n satisfying all precedence requirements
* Optimality:   Feasibility is taken from ans; any valid topological order is accepted
* Complexity:   O(n + m) time, O(n + m) memory
  */
  #include "testlib.h"
  #include <bits/stdc++.h>
  using namespace std;

static int parse_bounded_int_token(const string& tok, int lo, int hi, const char* name) {
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

vector<pair<int, int>> requirements;
requirements.reserve(m);

for (int i = 0; i < m; i++) {
    int a = inf.readInt();
    int b = inf.readInt();
    requirements.push_back({a, b});
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

string firstTok = ouf.readToken();
if (firstTok == "IMPOSSIBLE") {
    quitf(_wa, "a valid course order exists, but contestant printed IMPOSSIBLE");
}

vector<int> order(n);
order[0] = parse_bounded_int_token(firstTok, 1, n, "course[1]");

for (int i = 1; i < n; i++) {
    order[i] = ouf.readInt(1, n, format("course[%d]", i + 1).c_str());
}

vector<char> seen(n + 1, 0);
for (int i = 0; i < n; i++) {
    int course = order[i];

    if (seen[course]) {
        quitf(_wa, "course %d appears more than once in the order", course);
    }

    seen[course] = 1;
}

for (int course = 1; course <= n; course++) {
    if (!seen[course]) {
        quitf(_wa, "course %d is missing from the order", course);
    }
}

vector<int> pos(n + 1);
for (int i = 0; i < n; i++) {
    pos[order[i]] = i;
}

for (auto [a, b] : requirements) {
    if (pos[a] >= pos[b]) {
        quitf(_wa, "requirement violated: course %d must come before course %d", a, b);
    }
}

if (!ouf.seekEof())
    quitf(_wa, "extra information in the output file");

quitf(_ok, "valid topological order of %d courses", n);

}
