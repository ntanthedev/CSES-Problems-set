/*

* Problem:      1756 Acyclic Graph Edges
* Input read:   n, m; m undirected edges
* Validity:     Output exactly m directed edges. Each output edge must orient one original
* ```
            undirected edge, respecting multiplicity, and the resulting directed graph
* ```
            must be acyclic
* Optimality:   Any valid acyclic orientation is accepted
* Complexity:   O(n + m log m) time, O(n + m) memory
  */
  #include "testlib.h"
  #include <bits/stdc++.h>
  using namespace std;

static long long edge_key(int a, int b, int n) {
if (a > b) swap(a, b);
return 1LL * a * (n + 1LL) + b;
}

int main(int argc, char* argv[]) {
registerTestlibCmd(argc, argv);

int n = inf.readInt();
int m = inf.readInt();

unordered_map<long long, int> edgeCount;
edgeCount.reserve((size_t)m * 2 + 10);

for (int i = 0; i < m; i++) {
    int a = inf.readInt();
    int b = inf.readInt();
    edgeCount[edge_key(a, b, n)]++;
}

vector<vector<int>> g(n + 1);
vector<int> indeg(n + 1, 0);

for (int i = 1; i <= m; i++) {
    int a = ouf.readInt(1, n, format("edge[%d].from", i).c_str());
    int b = ouf.readInt(1, n, format("edge[%d].to", i).c_str());

    if (a == b) {
        quitf(_wa, "edge %d is a self-loop at node %d", i, a);
    }

    long long key = edge_key(a, b, n);
    auto it = edgeCount.find(key);

    if (it == edgeCount.end() || it->second == 0) {
        quitf(_wa, "edge %d-%d does not exist in the original graph or is used too many times",
              min(a, b), max(a, b));
    }

    it->second--;

    g[a].push_back(b);
    indeg[b]++;
}

for (auto [key, cnt] : edgeCount) {
    if (cnt != 0) {
        quitf(_wa, "not all original undirected edges were oriented");
    }
}

queue<int> q;
for (int i = 1; i <= n; i++) {
    if (indeg[i] == 0) q.push(i);
}

int processed = 0;
while (!q.empty()) {
    int u = q.front();
    q.pop();
    processed++;

    for (int v : g[u]) {
        indeg[v]--;
        if (indeg[v] == 0) q.push(v);
    }
}

if (processed != n) {
    quitf(_wa, "directed graph contains a cycle");
}

if (!ouf.seekEof())
    quitf(_wa, "extra information in the output file");

quitf(_ok, "valid acyclic orientation of %d edges", m);

}
