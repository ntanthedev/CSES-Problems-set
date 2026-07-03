/*
 * Problem:      3423 Permutation Prime Sums
 * Input read:   n
 * Validity:     IMPOSSIBLE iff no pair exists; else two permutations of 1..n with
 *               a_i + b_i prime for every position i
 * Optimality:   any valid pair (no scalar from ans)
 * Complexity:   O(n sqrt n)
 */
#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

static bool is_prime(int x) {
    if (x < 2) return false;
    if (x == 2) return true;
    if (x % 2 == 0) return false;
    for (int d = 3; d * d <= x; d += 2) {
        if (x % d == 0) return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();

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

    vector<int> a(n), b(n);
    vector<bool> seen_a(n + 1, false), seen_b(n + 1, false);

    for (int i = 0; i < n; i++) {
        a[i] = ouf.readInt(1, n, format("a[%d]", i + 1).c_str());
        if (seen_a[a[i]])
            quitf(_wa, "Value %d appears more than once in first permutation", a[i]);
        seen_a[a[i]] = true;
    }

    for (int i = 0; i < n; i++) {
        b[i] = ouf.readInt(1, n, format("b[%d]", i + 1).c_str());
        if (seen_b[b[i]])
            quitf(_wa, "Value %d appears more than once in second permutation", b[i]);
        seen_b[b[i]] = true;
    }

    for (int i = 0; i < n; i++) {
        int sum = a[i] + b[i];
        if (!is_prime(sum))
            quitf(_wa, "a[%d]+b[%d] = %d+%d = %d is not prime",
                  i + 1, i + 1, a[i], b[i], sum);
    }

    if (!ouf.seekEof())
        quitf(_wa, "extra information in the output file");
    quitf(_ok, "valid prime-sum permutations");
}
