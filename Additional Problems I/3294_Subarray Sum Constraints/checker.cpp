/*

* Problem:      3294 Subarray Sum Constraints
* Input read:   n, m; m constraints (l, r, s)
* Validity:     NO iff jury says no solution; otherwise YES followed by n integers
* ```
            x[i] in [-1e15,1e15] satisfying every subarray sum constraint
* Optimality:   Feasibility is taken from ans; any valid array is accepted
* Complexity:   O(n + m) time, O(n + m) memory
  */
  #include "testlib.h"
  #include <bits/stdc++.h>
  using namespace std;

using ll = long long;

int main(int argc, char* argv[]) {
registerTestlibCmd(argc, argv);

int n = inf.readInt();
int m = inf.readInt();

vector<int> L(m), R(m);
vector<ll> S(m);

for (int i = 0; i < m; i++) {
    L[i] = inf.readInt();
    R[i] = inf.readInt();
    S[i] = inf.readLong();
}

string ansToken = ans.readToken();
if (ansToken != "YES" && ansToken != "NO") {
    quitf(_fail, "malformed jury answer token '%s'", compress(ansToken).c_str());
}

string outToken = ouf.readToken();
if (outToken != "YES" && outToken != "NO") {
    quitf(_wa, "expected YES or NO, got '%s'", compress(outToken).c_str());
}

if (ansToken == "NO") {
    if (outToken != "NO") {
        quitf(_wa, "jury answer is NO, but contestant printed YES");
    }

    if (!ouf.seekEof())
        quitf(_wa, "extra information in the output file");

    quitf(_ok, "correctly reported NO");
}

if (outToken == "NO") {
    quitf(_wa, "a solution exists, but contestant printed NO");
}

const ll LIM = 1000000000000000LL;

vector<ll> pref(n + 1, 0);

for (int i = 1; i <= n; i++) {
    ll x = ouf.readLong(-LIM, LIM, format("x[%d]", i).c_str());
    pref[i] = pref[i - 1] + x;
}

for (int i = 0; i < m; i++) {
    ll got = pref[R[i]] - pref[L[i] - 1];

    if (got != S[i]) {
        quitf(_wa, "constraint %d violated: sum[%d..%d] is %lld, expected %lld",
              i + 1, L[i], R[i], got, S[i]);
    }
}

if (!ouf.seekEof())
    quitf(_wa, "extra information in the output file");

quitf(_ok, "valid array satisfying all %d constraints", m);

}
