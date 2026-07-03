#include "testlib.h"
#include <vector>
#include <map>
using namespace std;

int main(int argc, char* argv[]) {
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

    vector<vector<int>> dg(n + 1);
    for (int i = 0; i < m; i++) {
        int a = ouf.readInt();
        int b = ouf.readInt();
        if (a < 1 || a > n || b < 1 || b > n)
            quitf(_wa, "Node %d or %d out of range [1,%d]", a, b, n);
        if (a == b)
            quitf(_wa, "Self-loop not allowed: %d %d", a, b);

        pair<int, int> key = {min(a, b), max(a, b)};
        if (!edgeCnt.count(key) || edgeCnt[key] == 0)
            quitf(_wa, "Edge %d %d does not exist in the original graph", a, b);
        edgeCnt[key]--;
        dg[a].push_back(b);
    }

    for (auto [key, cnt] : edgeCnt) {
        if (cnt != 0)
            quitf(_wa, "Not all original edges are oriented");
    }

    for (int i = 0; i < m; i++)
        ans.readInt(), ans.readInt();

    vector<int> state(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        if (state[i] != 0)
            continue;
        vector<int> stack = {i};
        while (!stack.empty()) {
            int u = stack.back();
            if (state[u] == 0) {
                state[u] = 1;
                for (int v : dg[u]) {
                    if (state[v] == 1)
                        quitf(_wa, "Directed graph contains a cycle");
                    if (state[v] == 0)
                        stack.push_back(v);
                }
            } else if (state[u] == 1) {
                state[u] = 2;
                stack.pop_back();
            } else {
                stack.pop_back();
            }
        }
    }

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid acyclic orientation of %d edges", m);
}
