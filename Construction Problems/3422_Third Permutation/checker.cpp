/*
 * Problem:      3422 Third Permutation
 * Input read:   n; permutations a[1..n], b[1..n]
 * Validity:     IMPOSSIBLE iff no permutation c exists; else c is a permutation of
 *               1..n with c_i != a_i and c_i != b_i for all i
 * Optimality:   any valid permutation (no scalar from ans)
 * Complexity:   O(n)
 */
#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++)
        a[i] = inf.readInt();
    for (int i = 0; i < n; i++)
        b[i] = inf.readInt();

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

    vector<int> c(n);
    vector<bool> seen(n + 1, false);
    for (int i = 0; i < n; i++) {
        c[i] = ouf.readInt(1, n, format("c[%d]", i + 1).c_str());
        if (seen[c[i]])
            quitf(_wa, "Value %d appears more than once", c[i]);
        seen[c[i]] = true;
    }

    for (int i = 0; i < n; i++) {
        if (c[i] == a[i])
            quitf(_wa, "Position %d: c=%d equals a=%d", i + 1, c[i], a[i]);
        if (c[i] == b[i])
            quitf(_wa, "Position %d: c=%d equals b=%d", i + 1, c[i], b[i]);
    }

    if (!ouf.seekEof())
        quitf(_wa, "extra information in the output file");
    quitf(_ok, "valid third permutation");
}
