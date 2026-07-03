#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

static const int MOD = 1000000007;

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

    string ans_first = ans.readToken();
    bool solvable = (ans_first != "-1");

    string first = ouf.readToken();
    if (first == "-1") {
        if (solvable)
            quitf(_wa, "Output is -1 but a solution exists");
        if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
        quitf(_ok, "Correctly reported no solution");
    }

    if (!solvable)
        quitf(_wa, "No solution exists but output is not -1");

    vector<long long> x(m);
    x[0] = stoll(first);
    if (x[0] < 0 || x[0] >= MOD)
        quitf(_wa, "x[1] = %lld out of bounds [0, %d)", x[0], MOD);
    for (int i = 1; i < m; i++) {
        x[i] = ouf.readLong();
        if (x[i] < 0 || x[i] >= MOD)
            quitf(_wa, "x[%d] = %lld out of bounds [0, %d)", i + 1, x[i], MOD);
    }

    for (int i = 0; i < n; i++) {
        long long sum = 0;
        for (int j = 0; j < m; j++)
            sum = mod_norm(sum + mat[i][j] * x[j]);
        if (sum != mat[i][m])
            quitf(_wa, "Equation %d not satisfied: lhs=%lld, rhs=%lld", i + 1, sum, mat[i][m]);
    }

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid solution");
}
