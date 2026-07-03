/*
 * Problem:      1642 Sum of Four Values
 * Input read:   n, x; array a[1..n]
 * Validity:     IMPOSSIBLE iff no quadruple exists; else four distinct positions
 *               in [1,n] whose values sum to x
 * Optimality:   any valid quadruple (no scalar from ans)
 * Complexity:   O(n)
 */
#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int x = inf.readInt();
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        a[i] = inf.readInt();

    string ansFirst = ans.readToken();
    if (ansFirst == "IMPOSSIBLE") {
        string tok = ouf.readToken();
        if (tok != "IMPOSSIBLE")
            quitf(_wa, "Jury answer is IMPOSSIBLE but contestant printed \"%s\"",
                  compress(tok).c_str());
        if (!ouf.seekEof())
            quitf(_wa, "extra information in the output file");
        quitf(_ok, "correctly reported IMPOSSIBLE");
    }

    int i = ouf.readInt(1, n, "i");
    int j = ouf.readInt(1, n, "j");
    int k = ouf.readInt(1, n, "k");
    int l = ouf.readInt(1, n, "l");

    if (i == j || i == k || i == l || j == k || j == l || k == l)
        quitf(_wa, "Positions must be distinct, got %d %d %d %d", i, j, k, l);

    long long sum = (long long)a[i - 1] + a[j - 1] + a[k - 1] + a[l - 1];
    if (sum != x)
        quitf(_wa, "Values at positions %d,%d,%d,%d sum to %lld, expected %d",
              i, j, k, l, sum, x);

    if (!ouf.seekEof())
        quitf(_wa, "extra information in the output file");
    quitf(_ok, "valid quadruple (%d, %d, %d, %d)", i, j, k, l);
}
