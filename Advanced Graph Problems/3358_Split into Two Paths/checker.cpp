/*
 * HEADER CONTRACT
 * Problem:      3358 Split into Two Paths
 * Input read:   n, m; m directed edges (a, b)
 * Validity:     YES iff two vertex-disjoint directed paths partition all n nodes;
 *               each path's consecutive vertices have an input edge; one path may
 *               be empty (length 0); NO iff impossible
 * Optimality:   bound only — any valid partition accepted; YES/NO must match ans
 * Complexity:   O(n + m) time, O(n + m) memory
 */
#include "testlib.h"
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = inf.readInt();
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int a = inf.readInt();
        int b = inf.readInt();
        adj[a].push_back(b);
    }
    for (int v = 1; v <= n; v++)
        sort(adj[v].begin(), adj[v].end());

    string ansFlag = ans.readToken();
    if (ansFlag != "YES" && ansFlag != "NO")
        quitf(_fail, "invalid judge answer token \"%s\"", compress(ansFlag).c_str());

    if (ansFlag == "YES") {
        int lenA = ans.readInt();
        for (int i = 0; i < lenA; i++)
            ans.readInt();
        int lenB = ans.readInt();
        for (int i = 0; i < lenB; i++)
            ans.readInt();
    }

    string outFlag = ouf.readToken();
    if (outFlag != "YES" && outFlag != "NO")
        quitf(_wa, "contestant must print YES or NO, got \"%s\"", compress(outFlag).c_str());

    if (outFlag == "NO") {
        if (ansFlag != "NO")
            quitf(_wa, "jury answer is YES but contestant printed NO");
        if (!ouf.seekEof())
            quitf(_wa, "extra information in the output file");
        quitf(_ok, "correctly reported NO");
    }

    if (ansFlag == "NO")
        quitf(_wa, "jury answer is NO but contestant printed YES (claims a partition exists)");

    int len1 = ouf.readInt(0, n, "first path length");
    vector<int> path1(len1);
    for (int i = 0; i < len1; i++)
        path1[i] = ouf.readInt(1, n, format("first path node %d", i + 1).c_str());

    int len2 = ouf.readInt(0, n, "second path length");
    vector<int> path2(len2);
    for (int i = 0; i < len2; i++)
        path2[i] = ouf.readInt(1, n, format("second path node %d", i + 1).c_str());

    if (len1 + len2 != n)
        quitf(_wa, "path lengths %d + %d = %d but n = %d", len1, len2, len1 + len2, n);

    vector<char> seen(n + 1, 0);
    for (int x : path1) {
        if (seen[x])
            quitf(_wa, "node %d appears in more than one path", x);
        seen[x] = 1;
    }
    for (int x : path2) {
        if (seen[x])
            quitf(_wa, "node %d appears in more than one path", x);
        seen[x] = 1;
    }
    for (int v = 1; v <= n; v++) {
        if (!seen[v])
            quitf(_wa, "node %d is missing from both paths", v);
    }

    for (int i = 0; i + 1 < len1; i++) {
        int a = path1[i], b = path1[i + 1];
        if (!binary_search(adj[a].begin(), adj[a].end(), b))
            quitf(_wa, "first path step %d: edge %d -> %d does not exist", i + 1, a, b);
    }
    for (int i = 0; i + 1 < len2; i++) {
        int a = path2[i], b = path2[i + 1];
        if (!binary_search(adj[a].begin(), adj[a].end(), b))
            quitf(_wa, "second path step %d: edge %d -> %d does not exist", i + 1, a, b);
    }

    if (!ouf.seekEof())
        quitf(_wa, "extra information in the output file");
    quitf(_ok, "valid partition into two paths");
}
