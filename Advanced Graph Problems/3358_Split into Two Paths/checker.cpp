#include "testlib.h"
#include <vector>
#include <string>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = inf.readInt();
    vector<set<int>> g(n + 1);
    for (int i = 0; i < m; i++) {
        int a = inf.readInt();
        int b = inf.readInt();
        g[a].insert(b);
    }

    string ansFlag = ans.readToken();
    if (ansFlag != "YES" && ansFlag != "NO")
        quitf(_fail, "Invalid judge answer token '%s'", ansFlag.c_str());

    string outFlag = ouf.readToken();
    if (outFlag != "YES" && outFlag != "NO")
        quitf(_wa, "Expected YES or NO, got '%s'", outFlag.c_str());

    if (outFlag == "NO") {
        if (ansFlag != "NO")
            quitf(_wa, "Output is NO but a valid partition exists");
        if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
        quitf(_ok, "Correct: no valid partition");
    }

    if (ansFlag == "NO")
        quitf(_wa, "A valid partition exists but output is NO");

    if (ansFlag == "YES") {
        int len = ans.readInt();
        for (int i = 0; i < len; i++)
            ans.readInt();
        len = ans.readInt();
        for (int i = 0; i < len; i++)
            ans.readInt();
    }

    int len1 = ouf.readInt();
    if (len1 < 0 || len1 > n)
        quitf(_wa, "First path length %d out of range", len1);

    vector<int> path1;
    for (int i = 0; i < len1; i++) {
        int x = ouf.readInt();
        if (x < 1 || x > n)
            quitf(_wa, "Node %d out of range", x);
        path1.push_back(x);
    }

    int len2 = ouf.readInt();
    if (len2 < 0 || len2 > n)
        quitf(_wa, "Second path length %d out of range", len2);

    vector<int> path2;
    for (int i = 0; i < len2; i++) {
        int x = ouf.readInt();
        if (x < 1 || x > n)
            quitf(_wa, "Node %d out of range", x);
        path2.push_back(x);
    }

    if (len1 + len2 != n)
        quitf(_wa, "Total nodes in paths (%d+%d=%d) must equal n=%d",
              len1, len2, len1 + len2, n);

    vector<bool> seen(n + 1, false);
    for (int x : path1) {
        if (seen[x])
            quitf(_wa, "Node %d appears more than once", x);
        seen[x] = true;
    }
    for (int x : path2) {
        if (seen[x])
            quitf(_wa, "Node %d appears more than once", x);
        seen[x] = true;
    }

    for (int i = 0; i + 1 < len1; i++) {
        int a = path1[i], b = path1[i + 1];
        if (!g[a].count(b))
            quitf(_wa, "Edge %d -> %d does not exist in the graph (path 1)", a, b);
    }
    for (int i = 0; i + 1 < len2; i++) {
        int a = path2[i], b = path2[i + 1];
        if (!g[a].count(b))
            quitf(_wa, "Edge %d -> %d does not exist in the graph (path 2)", a, b);
    }

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid partition into two paths");
}
