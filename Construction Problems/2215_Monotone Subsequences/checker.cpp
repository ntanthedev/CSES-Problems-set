/*
 * HEADER CONTRACT
 * Problem:      2215 Monotone Subsequences
 * Input read:   t test cases; each has n, k
 * Validity:     per test: IMPOSSIBLE iff no permutation exists; else print a permutation
 *               of 1..n whose longest monotone subsequence (increasing or decreasing)
 *               has length exactly k.
 * Optimality:   none (any valid permutation accepted)
 * Complexity:   O(t * n log n) time, O(n) memory — n <= 100 per test
 */
#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

static int parseBoundedToken(const string &s, int lo, int hi, const char *name) {
    if (s.empty())
        quitf(_pe, "expected %s, got empty token", name);
    long long v = 0;
    for (char c : s) {
        if (!isdigit((unsigned char)c))
            quitf(_pe, "expected integer %s, got \"%s\"", name, compress(s).c_str());
        v = v * 10 + (c - '0');
        if (v > hi)
            quitf(_wa, "%s = %s out of range [%d,%d]", name, s.c_str(), lo, hi);
    }
    if (v < lo)
        quitf(_wa, "%s = %s out of range [%d,%d]", name, s.c_str(), lo, hi);
    return (int)v;
}

static int lisLen(const vector<int> &a) {
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

static int ldsLen(const vector<int> &a) {
    vector<int> dp;
    for (int x : a) {
        int y = -x;
        auto it = lower_bound(dp.begin(), dp.end(), y);
        if (it == dp.end())
            dp.push_back(y);
        else
            *it = y;
    }
    return (int)dp.size();
}

static void consumePermutation(int n, InStream &stream) {
    for (int i = 1; i < n; i++)
        stream.readInt();
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    int t = inf.readInt();
    for (int tc = 1; tc <= t; tc++) {
        int n = inf.readInt();
        int k = inf.readInt();

        string ansTok = ans.readToken();
        if (ansTok == "IMPOSSIBLE") {
            string oufTok = ouf.readToken();
            if (oufTok != "IMPOSSIBLE")
                quitf(_wa, "test %d: jury answer is IMPOSSIBLE but contestant printed \"%s\"",
                      tc, compress(oufTok).c_str());
            continue;
        }

        string oufTok = ouf.readToken();
        if (oufTok == "IMPOSSIBLE")
            quitf(_wa, "test %d: a valid permutation exists but contestant printed IMPOSSIBLE", tc);

        consumePermutation(n, ans);

        vector<int> p(n);
        vector<char> seen(n + 1, 0);
        p[0] = parseBoundedToken(oufTok, 1, n, format("test %d p[1]", tc).c_str());
        seen[p[0]] = 1;
        for (int i = 1; i < n; i++) {
            p[i] = ouf.readInt(1, n, format("test %d p[%d]", tc, i + 1).c_str());
            if (seen[p[i]])
                quitf(_wa, "test %d: value %d appears more than once", tc, p[i]);
            seen[p[i]] = 1;
        }

        int lis = lisLen(p);
        int lds = ldsLen(p);
        int longest = max(lis, lds);
        if (longest != k)
            quitf(_wa,
                  "test %d: longest monotone subsequence is %d, expected %d (LIS=%d, LDS=%d)",
                  tc, longest, k, lis, lds);
    }

    if (!ouf.seekEof())
        quitf(_wa, "extra information in the output file");
    quitf(_ok, "all %d tests passed", t);
}
