#include "testlib.h"
#include <vector>
#include <string>
using namespace std;
using ll = long long;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = inf.readInt();

    vector<int> L(m), R(m);
    vector<ll> S(m);
    for (int i = 0; i < m; i++) {
        L[i] = inf.readInt();
        R[i] = inf.readInt();
        S[i] = inf.readLong();
    }

    string ans_token = ans.readToken();
    bool ans_yes = (ans_token == "YES");

    string out_token = ouf.readToken();
    if (out_token == "NO") {
        if (ans_yes)
            quitf(_wa, "Output is NO but a solution exists");
        if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
        quitf(_ok, "Correctly reported no solution");
    }

    if (out_token != "YES")
        quitf(_wa, "Expected YES or NO, got '%s'", out_token.c_str());
    if (!ans_yes)
        quitf(_wa, "No solution exists but output is YES");

    vector<ll> x(n + 1);
    for (int i = 1; i <= n; i++) {
        x[i] = ouf.readLong();
        if (x[i] < -1000000000000000LL || x[i] > 1000000000000000LL)
            quitf(_wa, "x[%d] = %lld out of bounds [-10^15, 10^15]", i, x[i]);
    }

    vector<ll> pref(n + 1, 0);
    for (int i = 1; i <= n; i++)
        pref[i] = pref[i - 1] + x[i];

    for (int i = 0; i < m; i++) {
        ll sum = pref[R[i]] - pref[L[i] - 1];
        if (sum != S[i])
            quitf(_wa, "Constraint %d: sum[%d..%d] = %lld, expected %lld",
                  i + 1, L[i], R[i], sum, S[i]);
    }

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid solution");
}
