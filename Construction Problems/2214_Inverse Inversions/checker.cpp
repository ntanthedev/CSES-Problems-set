#include "testlib.h"
#include <vector>
using namespace std;
using ll = long long;

static ll count_inversions(const vector<int>& p) {
    int n = (int)p.size();
    vector<int> bit(n + 1, 0);
    auto add = [&](int i) {
        for (; i <= n; i += i & -i)
            bit[i]++;
    };
    auto sum = [&](int i) {
        int s = 0;
        for (; i > 0; i -= i & -i)
            s += bit[i];
        return s;
    };

    ll inv = 0;
    for (int x : p) {
        inv += sum(n) - sum(x);
        add(x);
    }
    return inv;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    ll k = inf.readLong();
    vector<int> p(n);
    vector<bool> seen(n + 1, false);
    for (int i = 0; i < n; i++) {
        p[i] = ouf.readInt();
        if (p[i] < 1 || p[i] > n)
            quitf(_wa, "Value %d out of range [1,%d]", p[i], n);
        if (seen[p[i]])
            quitf(_wa, "Value %d appears more than once", p[i]);
        seen[p[i]] = true;
    }
    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");

    ll inv = count_inversions(p);
    if (inv != k)
        quitf(_wa, "Permutation has %lld inversions, expected %lld", inv, k);

    quitf(_ok, "Valid permutation with %lld inversions", k);
}
