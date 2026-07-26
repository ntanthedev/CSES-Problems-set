/*
 * HEADER CONTRACT
 * Problem:      1752 Creating Offices
 * Input read:   n, d; n-1 tree edges (a,b)
 * Validity:     print k then k distinct cities in [1,n]; every pair of chosen cities
 *               has tree distance at least d.
 * Optimality:   k must equal ans.readInt() (maximum office count)
 * Complexity:   O(n) time and memory — one multi-source BFS, no O(k^2) pairwise LCA
 */
#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int d = inf.readInt();
    vector<vector<int>> g(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int a = inf.readInt();
        int b = inf.readInt();
        g[a].push_back(b);
        g[b].push_back(a);
    }

    int kAns = ans.readInt();
    int k = ouf.readInt(0, n, "k");
    if (k != kAns)
        quitf(_wa, "contestant printed k = %d but optimal is %d", k, kAns);

    vector<int> offices(k);
    vector<char> isOffice(n + 1, 0);
    for (int i = 0; i < k; i++) {
        offices[i] = ouf.readInt(1, n, format("office[%d]", i + 1).c_str());
        if (isOffice[offices[i]])
            quitf(_wa, "city %d selected more than once", offices[i]);
        isOffice[offices[i]] = 1;
    }

    if (k <= 1) {
        if (!ouf.seekEof())
            quitf(_wa, "extra information in the output file");
        quitf(_ok, "valid maximum office placement with %d offices", k);
    }

    const int INF = 1e9;
    vector<int> dist(n + 1, INF), source(n + 1, -1);
    queue<int> q;
    for (int i = 0; i < k; i++) {
        int o = offices[i];
        dist[o] = 0;
        source[o] = o;
        q.push(o);
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : g[u]) {
            if (dist[v] != INF) {
                if (source[v] != source[u]) {
                    int sep = dist[v] + dist[u] + 1;
                    if (sep < d)
                        quitf(_wa,
                              "distance between offices %d and %d is %d, need at least %d",
                              source[v], source[u], sep, d);
                }
                continue;
            }
            dist[v] = dist[u] + 1;
            source[v] = source[u];
            q.push(v);
        }
    }

    if (!ouf.seekEof())
        quitf(_wa, "extra information in the output file");
    quitf(_ok, "valid maximum office placement with %d offices", k);
}
