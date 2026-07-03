/*

* Problem:      2414 List of Sums
* Input read:   n; n*(n-1)/2 pair sums
* Validity:     Output exactly n integers A[i] in [1, 1e9] whose pair sums match input
* Optimality:   Any valid reconstruction is accepted
* Complexity:   O(n^2 log n) time, O(n^2) memory
  */
  #include "testlib.h"
  #include <bits/stdc++.h>
  using namespace std;

using ll = long long;

int main(int argc, char* argv[]) {
registerTestlibCmd(argc, argv);

int n = inf.readInt();
int m = n * (n - 1) / 2;

vector<ll> inputSums(m);
for (int i = 0; i < m; i++) {
    inputSums[i] = inf.readLong();
}
sort(inputSums.begin(), inputSums.end());

vector<ll> a(n);
for (int i = 0; i < n; i++) {
    a[i] = ouf.readLong(1LL, 1000000000LL, format("A[%d]", i + 1).c_str());
}

vector<ll> outputSums;
outputSums.reserve(m);
for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
        outputSums.push_back(a[i] + a[j]);
    }
}
sort(outputSums.begin(), outputSums.end());

if (inputSums != outputSums) {
    quitf(_wa, "pairwise sums of contestant output do not match the input list");
}

if (!ouf.seekEof())
    quitf(_wa, "extra information in the output file");

quitf(_ok, "valid reconstruction of %d values", n);

}
