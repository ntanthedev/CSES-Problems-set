/*

* Problem:      3403 Longest Common Subsequence
* Input read:   n, m; arrays a[1..n], b[1..m]
* Validity:     Output k followed by k values forming a common subsequence of both arrays
* Optimality:   k must equal the longest common subsequence length from ans
* Complexity:   O(n + m + k) time, O(n + m + k) memory
  */
  #include "testlib.h"
  #include <bits/stdc++.h>
  using namespace std;

using ll = long long;

static bool is_subsequence(const vector<ll>& arr, const vector<ll>& sub) {
int j = 0;

for (int i = 0; i < (int)arr.size() && j < (int)sub.size(); i++) {
    if (arr[i] == sub[j]) {
        j++;
    }
}

return j == (int)sub.size();

}

int main(int argc, char* argv[]) {
registerTestlibCmd(argc, argv);

int n = inf.readInt();
int m = inf.readInt();

vector<ll> a(n), b(m);

for (int i = 0; i < n; i++) {
    a[i] = inf.readLong();
}

for (int i = 0; i < m; i++) {
    b[i] = inf.readLong();
}

int optimal = ans.readInt();

int k = ouf.readInt(0, min(n, m), "LCS length");
if (k != optimal) {
    quitf(_wa, "contestant printed LCS length %d, but optimum is %d", k, optimal);
}

vector<ll> sub(k);
for (int i = 0; i < k; i++) {
    sub[i] = ouf.readLong(1LL, 1000000000LL, format("subsequence[%d]", i + 1).c_str());
}

if (!is_subsequence(a, sub)) {
    quitf(_wa, "output sequence is not a subsequence of the first array");
}

if (!is_subsequence(b, sub)) {
    quitf(_wa, "output sequence is not a subsequence of the second array");
}

if (!ouf.seekEof())
    quitf(_wa, "extra information in the output file");

quitf(_ok, "valid longest common subsequence of length %d", k);

}
