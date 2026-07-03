#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

static long long distinct_subseq_count(const string& s) {
    int len = (int)s.size();
    vector<long long> dp(len + 1, 0);
    dp[0] = 1;
    int last[2] = {-1, -1};

    for (int i = 0; i < len; i++) {
        int c = s[i] - '0';
        dp[i + 1] = 2 * dp[i];
        if (last[c] != -1)
            dp[i + 1] -= dp[last[c]];
        last[c] = i;
    }

    return dp[len] - 1;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    long long n = inf.readLong();

    string ref = ans.readToken();
    string out = ouf.readToken();

    int optimal_len = (int)ref.size();

    for (char c : out) {
        if (c != '0' && c != '1')
            quitf(_wa, "Output must be a bit string, got character '%c'", c);
    }

    if ((int)out.size() != optimal_len)
        quitf(_wa, "Minimum length is %d, got %d", optimal_len, (int)out.size());

    long long count = distinct_subseq_count(out);
    if (count != n)
        quitf(_wa, "String has %lld distinct subsequences, expected %lld", count, n);

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid minimum-length bit string of length %d", optimal_len);
}
