/*

* Problem:      1640 Sum of Two Values
* Input read:   n, x; array a[1..n]
* Validity:     IMPOSSIBLE iff jury says no pair; otherwise two distinct positions in [1,n]
* ```
            whose values sum to x
* Optimality:   Feasibility is taken from ans; any valid pair is accepted
* Complexity:   O(n) time, O(n) memory
  */
  #include "testlib.h"
  #include <bits/stdc++.h>
  using namespace std;

int main(int argc, char* argv[]) {
registerTestlibCmd(argc, argv);

int n = inf.readInt();
long long x = inf.readLong();

vector<long long> a(n + 1);
for (int i = 1; i <= n; i++) {
    a[i] = inf.readLong();
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

int i = ouf.readInt(1, n, "first position");
int j = ouf.readInt(1, n, "second position");

if (i == j) {
    quitf(_wa, "positions must be distinct, both are %d", i);
}

long long sum = a[i] + a[j];
if (sum != x) {
    quitf(_wa, "values at positions %d and %d sum to %lld, expected %lld",
          i, j, sum, x);
}

if (!ouf.seekEof())
    quitf(_wa, "extra information in the output file");

quitf(_ok, "valid pair (%d, %d)", i, j);

}
