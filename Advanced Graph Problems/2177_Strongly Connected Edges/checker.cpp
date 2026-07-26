/*
 * HEADER CONTRACT
 * Problem:      2177 Strongly Connected Edges
 * Input read:   n, m; m undirected simple edges (a,b)
 * Validity:     IMPOSSIBLE iff no orientation exists; else orient each input edge exactly
 *               once (a->b) with 1<=a,b<=n, and the directed graph is strongly connected.
 * Optimality:   none (any valid orientation accepted)
 * Complexity:   O(n + m) time and memory — edge multiset + two reachability BFS passes
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

static void consumeAnsEdges(int m, const string &firstA) {
    (void)stoi(firstA);
    ans.readInt();
    for (int i = 1; i < m; i++)
        ans.readInt(), ans.readInt();
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = inf.readInt();
    map<pair<int, int>, int> edgeCnt;
    for (int i = 0; i < m; i++) {
        int a = inf.readInt();
        int b = inf.readInt();
        pair<int, int> key = {min(a, b), max(a, b)};
        edgeCnt[key]++;
    }

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
        quitf(_wa, "a valid orientation exists but contestant printed IMPOSSIBLE");

    map<pair<int, int>, int> used = edgeCnt;
    vector<vector<int>> dg(n + 1), rdg(n + 1);

    auto orient = [&](int a, int b, int idx) {
        pair<int, int> key = {min(a, b), max(a, b)};
        auto it = used.find(key);
        if (it == used.end() || it->second == 0)
            quitf(_wa, "edge %d: (%d,%d) is not an undirected input edge", idx, a, b);
        it->second--;
        dg[a].push_back(b);
        rdg[b].push_back(a);
    };

    int a = parseBoundedToken(oufTok, 1, n, "edge 1 endpoint a");
    int b = ouf.readInt(1, n, "edge 1 endpoint b");
    orient(a, b, 1);
    for (int i = 2; i <= m; i++) {
        int x = ouf.readInt(1, n, format("edge %d endpoint a", i).c_str());
        int y = ouf.readInt(1, n, format("edge %d endpoint b", i).c_str());
        orient(x, y, i);
    }
    consumeAnsEdges(m, ansTok);

    for (const auto &kv : used) {
        if (kv.second != 0)
            quitf(_wa, "not every input edge was oriented exactly once");
    }

    auto reachable = [&](const vector<vector<int>> &adj) {
        vector<char> vis(n + 1, 0);
        queue<int> q;
        q.push(1);
        vis[1] = 1;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : adj[u]) {
                if (!vis[v]) {
                    vis[v] = 1;
                    q.push(v);
                }
            }
        }
        return vis;
    };

    vector<char> fwd = reachable(dg);
    vector<char> rev = reachable(rdg);
    for (int i = 1; i <= n; i++) {
        if (!fwd[i] || !rev[i])
            quitf(_wa, "directed graph is not strongly connected (node %d unreachable)", i);
    }

    if (!ouf.seekEof())
        quitf(_wa, "extra information in the output file");
    quitf(_ok, "valid strongly connected orientation");
}
