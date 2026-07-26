/*

* Problem:      3424 Distinct Sums Grid
* Input read:   n
* Validity:     IMPOSSIBLE iff jury says impossible; otherwise n x n grid with each value
* ```
            1..n appearing exactly n times and exactly 2n distinct row and column sums
* Optimality:   Feasibility is taken from ans; any valid grid is accepted
* Complexity:   O(n^2) time, O(n) memory
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
    quitf(_wa, "a valid grid exists, but contestant printed IMPOSSIBLE");
}

vector<int> freq(n + 1, 0);
vector<int> colSum(n, 0);
set<int> sums;

int firstValue = parse_bounded_int_token(firstOut, 1, n, "grid[1][1]");
freq[firstValue]++;
colSum[0] += firstValue;

int rowSum = firstValue;

for (int j = 1; j < n; j++) {
    int x = ouf.readInt(1, n, format("grid[1][%d]", j + 1).c_str());

    freq[x]++;
    rowSum += x;
    colSum[j] += x;
}

sums.insert(rowSum);

for (int i = 1; i < n; i++) {
    rowSum = 0;

    for (int j = 0; j < n; j++) {
        int x = ouf.readInt(1, n, format("grid[%d][%d]", i + 1, j + 1).c_str());

        freq[x]++;
        rowSum += x;
        colSum[j] += x;
    }

    sums.insert(rowSum);
}

for (int value = 1; value <= n; value++) {
    if (freq[value] != n) {
        quitf(_wa, "value %d appears %d times, expected exactly %d",
              value, freq[value], n);
    }
}

for (int j = 0; j < n; j++) {
    sums.insert(colSum[j]);
}

if ((int)sums.size() != 2 * n) {
    quitf(_wa, "got %d distinct row and column sums, expected %d",
          (int)sums.size(), 2 * n);
}

if (!ouf.seekEof())
    quitf(_wa, "extra information in the output file");

quitf(_ok, "valid grid with %d distinct sums", (int)sums.size());

}
