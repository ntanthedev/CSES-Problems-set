#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    vector<int> perm(n + 1);
    for (int i = 1; i <= n; i++)
        perm[i] = inf.readInt();

    int k = ouf.readInt();
    if (k < 0 || k > n)
        quitf(_wa, "Number of reversals must be between 0 and %d, got %d", n, k);

    vector<int> cur = perm;
    for (int r = 0; r < k; r++) {
        int a = ouf.readInt();
        int b = ouf.readInt();
        if (a < 1 || b < a || b > n)
            quitf(_wa, "Reversal %d: invalid range [%d, %d]", r + 1, a, b);
        reverse(cur.begin() + a, cur.begin() + b + 1);
    }

    for (int i = 1; i <= n; i++) {
        if (cur[i] != i)
            quitf(_wa, "After all reversals, position %d has value %d, expected %d", i, cur[i], i);
    }

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid sorting with %d reversals", k);
}
