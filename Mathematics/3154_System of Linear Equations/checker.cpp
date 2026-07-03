/*
 * Problem:      3154 System of Linear Equations
 * Input read:   n, m; n rows of m+1 coefficients (mod 10^9+7)
 * Validity:     -1 iff no solution; else m values x_i in [0, MOD) satisfying
 *               all n equations modulo MOD
 * Optimality:   any valid solution (no scalar from ans)
 * Complexity:   O(n*m)
 */
#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

static const int MOD = 1000000007;
static const long long MAXV = MOD - 1;

static long long mod_norm(long long x) {
    x %= MOD;
    if (x < 0) x += MOD;
    return x;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = inf.readInt();
    vector<vector<long long>> mat(n, vector<long long>(m + 1));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            mat[i][j] = inf.readInt();
        mat[i][m] = inf.readInt();
    }

    string ansFirst = ans.readToken();
    if (ansFirst == "-1") {
        string tok = ouf.readToken();
        if (tok != "-1")
            quitf(_wa, "Jury answer is -1 but contestant printed \"%s\"",
                  compress(tok).c_str());
        if (!ouf.seekEof())
            quitf(_wa, "extra information in the output file");
        quitf(_ok, "correctly reported no solution");
    }

    vector<long long> x(m);
    x[0] = ouf.readLong(0LL, MAXV, "x[1]");
    for (int i = 1; i < m; i++)
        x[i] = ouf.readLong(0LL, MAXV, format("x[%d]", i + 1).c_str());

    for (int i = 0; i < n; i++) {
        long long sum = 0;
        for (int j = 0; j < m; j++)
            sum = mod_norm(sum + mat[i][j] * x[j]);
        if (sum != mat[i][m])
            quitf(_wa, "Equation %d not satisfied: lhs=%lld, rhs=%lld",
                  i + 1, sum, mat[i][m]);
    }

    if (!ouf.seekEof())
        quitf(_wa, "extra information in the output file");
    quitf(_ok, "valid solution");
}
