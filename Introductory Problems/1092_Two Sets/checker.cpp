/*

* Problem:      1092 Two Sets
* Input read:   n
* Validity:     NO iff jury says impossible; otherwise YES followed by two sets whose
* ```
            sizes sum to n, whose elements form exactly {1..n}, and whose sums are equal
* Optimality:   Feasibility is taken from ans; any valid partition is accepted
* Complexity:   O(n) time, O(n) memory
  */
  #include "testlib.h"
  #include <bits/stdc++.h>
  using namespace std;

int main(int argc, char* argv[]) {
registerTestlibCmd(argc, argv);

int n = inf.readInt();

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
        quitf(_wa, "no partition exists, but contestant printed YES");
    }

    if (!ouf.seekEof())
        quitf(_wa, "extra information in the output file");

    quitf(_ok, "correctly reported NO");
}

if (outToken == "NO") {
    quitf(_wa, "a partition exists, but contestant printed NO");
}

vector<char> seen(n + 1, 0);

int k1 = ouf.readInt(0, n, "first set size");
long long sum1 = 0;

for (int i = 0; i < k1; i++) {
    int x = ouf.readInt(1, n, format("first_set[%d]", i + 1).c_str());

    if (seen[x]) {
        quitf(_wa, "value %d appears more than once", x);
    }

    seen[x] = 1;
    sum1 += x;
}

int k2 = ouf.readInt(0, n, "second set size");

if (k1 + k2 != n) {
    quitf(_wa, "set sizes are %d and %d, but their sum must be n = %d",
          k1, k2, n);
}

long long sum2 = 0;

for (int i = 0; i < k2; i++) {
    int x = ouf.readInt(1, n, format("second_set[%d]", i + 1).c_str());

    if (seen[x]) {
        quitf(_wa, "value %d appears more than once", x);
    }

    seen[x] = 1;
    sum2 += x;
}

if (sum1 != sum2) {
    quitf(_wa, "set sums differ: first sum is %lld, second sum is %lld",
          sum1, sum2);
}

for (int x = 1; x <= n; x++) {
    if (!seen[x]) {
        quitf(_wa, "value %d is missing from both sets", x);
    }
}

if (!ouf.seekEof())
    quitf(_wa, "extra information in the output file");

quitf(_ok, "valid partition of 1..%d", n);

}
