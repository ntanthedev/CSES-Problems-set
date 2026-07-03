#include "testlib.h"
#include <vector>
#include <string>
#include <queue>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = inf.readInt();
    vector<vector<int>> g(n + 1), rg(n + 1);
    for (int i = 0; i < m; i++) {
        int a = inf.readInt();
        int b = inf.readInt();
        g[a].push_back(b);
        rg[b].push_back(a);
    }

    string ansFlag = ans.readToken();
    if (ansFlag != "YES" && ansFlag != "NO")
        quitf(_fail, "Invalid judge answer token '%s'", ansFlag.c_str());

    string outFlag = ouf.readToken();
    if (outFlag != "YES" && outFlag != "NO")
        quitf(_wa, "Expected YES or NO, got '%s'", outFlag.c_str());

    if (outFlag == "NO") {
        if (ansFlag != "NO")
            quitf(_wa, "Output is NO but all routes are possible");
        int a = ouf.readInt();
        int b = ouf.readInt();
        if (a < 1 || a > n || b < 1 || b > n)
            quitf(_wa, "Cities %d %d out of range [1,%d]", a, b, n);

        vector<char> vis(n + 1, 0);
        queue<int> q;
        q.push(a);
        vis[a] = 1;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : g[u]) {
                if (!vis[v]) {
                    vis[v] = 1;
                    q.push(v);
                }
            }
        }
        if (vis[b])
            quitf(_wa, "Path from %d to %d exists but output is NO", a, b);

        if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
        quitf(_ok, "Correct: no path from %d to %d", a, b);
    }

    if (ansFlag == "NO")
        quitf(_wa, "All routes are possible but output is YES");

    vector<char> vis1(n + 1, 0), vis2(n + 1, 0);
    queue<int> q;
    q.push(1);
    vis1[1] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : g[u]) {
            if (!vis1[v]) {
                vis1[v] = 1;
                q.push(v);
            }
        }
    }
    q.push(1);
    vis2[1] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : rg[u]) {
            if (!vis2[v]) {
                vis2[v] = 1;
                q.push(v);
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        if (!vis1[i])
            quitf(_wa, "City %d not reachable from 1", i);
        if (!vis2[i])
            quitf(_wa, "City 1 not reachable from %d", i);
    }

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Graph is strongly connected");
}
