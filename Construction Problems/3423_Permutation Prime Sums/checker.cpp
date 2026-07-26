/*

* Problem:      3423 Permutation Prime Sums
* Input read:   n
* Validity:     IMPOSSIBLE iff jury says impossible; otherwise two permutations a,b
* ```
            of 1..n such that a[i] + b[i] is prime for every position
* Optimality:   Feasibility is taken from ans; any valid pair is accepted
* Complexity:   O(n log log n) time, O(n) memory
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

static vector<char> build_prime_table(int maxValue) {
vector<char> prime(maxValue + 1, 1);

if (maxValue >= 0) prime[0] = 0;
if (maxValue >= 1) prime[1] = 0;

for (int p = 2; 1LL * p * p <= maxValue; p++) {
    if (!prime[p]) continue;

    for (long long x = 1LL * p * p; x <= maxValue; x += p) {
        prime[(int)x] = 0;
    }
}

return prime;

}

int main(int argc, char* argv[]) {
registerTestlibCmd(argc, argv);

int n = inf.readInt();

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
    quitf(_wa, "valid prime-sum permutations exist, but contestant printed IMPOSSIBLE");
}

vector<int> a(n), b(n);
vector<char> seenA(n + 1, 0), seenB(n + 1, 0);

a[0] = parse_bounded_int_token(firstOut, 1, n, "a[1]");
seenA[a[0]] = 1;

for (int i = 1; i < n; i++) {
    a[i] = ouf.readInt(1, n, format("a[%d]", i + 1).c_str());

    if (seenA[a[i]]) {
        quitf(_wa, "value %d appears more than once in the first permutation", a[i]);
    }

    seenA[a[i]] = 1;
}

for (int i = 0; i < n; i++) {
    b[i] = ouf.readInt(1, n, format("b[%d]", i + 1).c_str());

    if (seenB[b[i]]) {
        quitf(_wa, "value %d appears more than once in the second permutation", b[i]);
    }

    seenB[b[i]] = 1;
}

vector<char> prime = build_prime_table(2 * n);

for (int i = 0; i < n; i++) {
    int sum = a[i] + b[i];

    if (!prime[sum]) {
        quitf(_wa, "a[%d] + b[%d] = %d + %d = %d is not prime",
              i + 1, i + 1, a[i], b[i], sum);
    }
}

if (!ouf.seekEof())
    quitf(_wa, "extra information in the output file");

quitf(_ok, "valid prime-sum permutations");

}
