#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

static int lis_len(const vector<int>& a) {
    vector<int> dp;
    for (int x : a) {
        auto it = lower_bound(dp.begin(), dp.end(), x);
        if (it == dp.end())
            dp.push_back(x);
        else
            *it = x;
    }
    return (int)dp.size();
}

static int lds_len(const vector<int>& a) {
    vector<int> dp;
    for (int x : a) {
        x = -x;
        auto it = lower_bound(dp.begin(), dp.end(), x);
        if (it == dp.end())
            dp.push_back(x);
        else
            *it = x;
    }
    return (int)dp.size();
}

static void consume_permutation(int n, InStream& stream) {
    for (int i = 1; i < n; i++)
        stream.readInt();
}

static vector<int> read_permutation(int n, const string& first) {
    vector<int> p(n);
    vector<bool> seen(n + 1, false);
    p[0] = stoi(first);
    if (p[0] < 1 || p[0] > n)
        quitf(_wa, "Value %d out of range [1,%d]", p[0], n);
    seen[p[0]] = true;

    for (int i = 1; i < n; i++) {
        p[i] = ouf.readInt();
        if (p[i] < 1 || p[i] > n)
            quitf(_wa, "Value %d out of range [1,%d]", p[i], n);
        if (seen[p[i]])
            quitf(_wa, "Value %d appears more than once", p[i]);
        seen[p[i]] = true;
    }
    return p;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int t = inf.readInt();
    for (int test = 0; test < t; test++) {
        int n = inf.readInt();
        int k = inf.readInt();
        string ans_first = ans.readToken();
        string ouf_first = ouf.readToken();

        if (ans_first == "IMPOSSIBLE") {
            if (ouf_first != "IMPOSSIBLE")
                quitf(_wa, "Test %d: a valid permutation exists but contestant printed IMPOSSIBLE", test + 1);
            continue;
        }

        if (ouf_first == "IMPOSSIBLE")
            quitf(_wa, "Test %d: no valid permutation exists but contestant printed a solution", test + 1);

        consume_permutation(n, ans);
        vector<int> p = read_permutation(n, ouf_first);

        int longest = max(lis_len(p), lds_len(p));
        if (longest != k)
            quitf(_wa,
                  "Test %d: longest monotone subsequence is %d, expected %d (LIS=%d, LDS=%d)",
                  test + 1, longest, k, lis_len(p), lds_len(p));
    }

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "All %d tests passed", t);
}
