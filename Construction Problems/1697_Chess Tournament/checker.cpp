/*
 * HEADER CONTRACT
 * Problem:      1697 Chess Tournament
 * Input read:   n; x_1..x_n (desired game counts per player)
 * Validity:     IMPOSSIBLE iff no valid schedule; else print k then k pairs (a,b)
 *               with 1<=a,b<=n, a!=b, each unordered pair at most once, and player i
 *               plays exactly x_i games.
 * Optimality:   none (any valid schedule accepted; k not compared to ans)
 * Complexity:   O(n + k) time, O(n + k) memory — edge list, no N^2 adjacency matrix
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

static void consumeGames(int k, InStream &stream) {
    for (int i = 0; i < k; i++) {
        stream.readInt();
        stream.readInt();
    }
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    vector<int> want(n + 1);
    long long sumDeg = 0;
    for (int i = 1; i <= n; i++) {
        want[i] = inf.readInt();
        sumDeg += want[i];
    }
    int maxK = (int)(sumDeg / 2);

    string ansTok = ans.readToken();
    if (ansTok == "IMPOSSIBLE") {
        string oufTok = ouf.readToken();
        if (oufTok != "IMPOSSIBLE")
            quitf(_wa, "jury answer is IMPOSSIBLE but contestant printed \"%s\" "
                       "(claims a solution exists)",
                  compress(oufTok).c_str());
        if (!ouf.seekEof())
            quitf(_wa, "extra information in the output file");
        quitf(_ok, "correctly reported IMPOSSIBLE");
    }

    string oufTok = ouf.readToken();
    if (oufTok == "IMPOSSIBLE")
        quitf(_wa, "a valid tournament exists but contestant printed IMPOSSIBLE");

    int kAns = stoi(ansTok);
    consumeGames(kAns, ans);

    int k = parseBoundedToken(oufTok, 0, maxK, "k");
    vector<int> got(n + 1, 0);
    unordered_set<long long> used;
    used.reserve((size_t)k * 2 + 1);

    for (int i = 0; i < k; i++) {
        int a = ouf.readInt(1, n, format("game %d player a", i + 1).c_str());
        int b = ouf.readInt(1, n, format("game %d player b", i + 1).c_str());
        if (a == b)
            quitf(_wa, "game %d: player %d cannot play against themselves", i + 1, a);
        int u = min(a, b), v = max(a, b);
        long long key = (long long)u * (n + 1LL) + v;
        if (!used.insert(key).second)
            quitf(_wa, "pair %d %d plays more than once", u, v);
        got[a]++;
        got[b]++;
    }

    for (int i = 1; i <= n; i++) {
        if (got[i] != want[i])
            quitf(_wa, "player %d wanted %d games but played %d", i, want[i], got[i]);
    }

    if (!ouf.seekEof())
        quitf(_wa, "extra information in the output file");
    quitf(_ok, "valid tournament with %d games", k);
}
