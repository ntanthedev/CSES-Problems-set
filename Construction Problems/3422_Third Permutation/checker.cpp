/*

* Problem:      3422 Third Permutation
* Input read:   n; permutations a[1..n], b[1..n]
* Validity:     IMPOSSIBLE iff jury says impossible; otherwise c is a permutation of
* ```
            1..n with c[i] != a[i] and c[i] != b[i] for every position
* Optimality:   Feasibility is taken from ans; any valid third permutation is accepted
* Complexity:   O(n) time, O(n) memory
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

vector<int> a(n), b(n);
for (int i = 0; i < n; i++) {
    a[i] = inf.readInt();
}
for (int i = 0; i < n; i++) {
    b[i] = inf.readInt();
}

string ansFirst = ans.readToken();

if (ansFirst == "IMPOSSIBLE") {
    string outFirst = ouf.readToken();

    if (outFirst != "IMPOSSIBLE") {
        quitf(_wa, "jury answer is IMPOSSIBLE but contestant printed '%s'",
              compress(outFirst).c_str());
    }

    if (!ouf.seekEof())
        quitf(_wa, "extra information in the output file");

    quitf(_ok, "correctly reported IMPOSSIBLE");
}

string firstOut = ouf.readToken();
if (firstOut == "IMPOSSIBLE") {
    quitf(_wa, "a valid third permutation exists, but contestant printed IMPOSSIBLE");
}

vector<int> c(n);
vector<char> seen(n + 1, 0);

c[0] = parse_bounded_int_token(firstOut, 1, n, "c[1]");
seen[c[0]] = 1;

for (int i = 1; i < n; i++) {
    c[i] = ouf.readInt(1, n, format("c[%d]", i + 1).c_str());

    if (seen[c[i]]) {
        quitf(_wa, "value %d appears more than once", c[i]);
    }

    seen[c[i]] = 1;
}

for (int i = 0; i < n; i++) {
    if (c[i] == a[i]) {
        quitf(_wa, "position %d: c[%d] = %d equals a[%d]",
              i + 1, i + 1, c[i], i + 1);
    }

    if (c[i] == b[i]) {
        quitf(_wa, "position %d: c[%d] = %d equals b[%d]",
              i + 1, i + 1, c[i], i + 1);
    }
}

if (!ouf.seekEof())
    quitf(_wa, "extra information in the output file");

quitf(_ok, "valid third permutation");

}
