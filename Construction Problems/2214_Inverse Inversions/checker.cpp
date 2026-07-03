/*

* Problem:      2214 Inverse Inversions
* Input read:   n, k
* Validity:     Output a permutation of 1..n
* Optimality:   The permutation must have exactly k inversions
* Complexity:   O(n log n) time, O(n) memory
  */
  #include "testlib.h"
  #include <bits/stdc++.h>
  using namespace std;

using ll = long long;

struct Fenwick {
int n;
vector<int> bit;

explicit Fenwick(int n_) : n(n_), bit(n_ + 1, 0) {}

void add(int idx, int val) {
    for (; idx <= n; idx += idx & -idx) {
        bit[idx] += val;
    }
}

int sum(int idx) const {
    int res = 0;
    for (; idx > 0; idx -= idx & -idx) {
        res += bit[idx];
    }
    return res;
}

};

int main(int argc, char* argv[]) {
registerTestlibCmd(argc, argv);

int n = inf.readInt();
ll expected = inf.readLong();

vector<char> seen(n + 1, 0);
Fenwick fw(n);

ll inv = 0;

for (int i = 1; i <= n; i++) {
    int x = ouf.readInt(1, n, format("p[%d]", i).c_str());

    if (seen[x]) {
        quitf(_wa, "value %d appears more than once", x);
    }

    seen[x] = 1;

    inv += (i - 1) - fw.sum(x);
    fw.add(x, 1);
}

if (inv != expected) {
    quitf(_wa, "permutation has %lld inversions, expected %lld", inv, expected);
}

if (!ouf.seekEof())
    quitf(_wa, "extra information in the output file");

quitf(_ok, "valid permutation with %lld inversions", inv);

}
