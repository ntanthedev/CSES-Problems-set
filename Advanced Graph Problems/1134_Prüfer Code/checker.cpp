/*

* Problem:      1134 Prufer Code
* Input read:   n; Prufer code of length n-2
* Validity:     Output exactly n-1 undirected edges on nodes [1,n], forming a tree whose
* ```
            Prufer code is exactly the input code
* Optimality:   Any edge order and orientation for the unique tree is accepted
* Complexity:   O(n log n) time, O(n) memory
  */
  #include "testlib.h"
  #include <bits/stdc++.h>
  using namespace std;

struct DSU {
vector<int> p, sz;

explicit DSU(int n) : p(n + 1), sz(n + 1, 1) {
    iota(p.begin(), p.end(), 0);
}

int find(int x) {
    while (p[x] != x) {
        p[x] = p[p[x]];
        x = p[x];
    }
    return x;
}

bool unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return false;
    if (sz[a] < sz[b]) swap(a, b);
    p[b] = a;
    sz[a] += sz[b];
    return true;
}

};

static long long edge_key(int a, int b, int n) {
if (a > b) swap(a, b);
return 1LL * a * (n + 1LL) + b;
}

static vector<int> encode_prufer(int n, const vector<vector<int>>& adj) {
vector<int> deg(n + 1, 0);
for (int i = 1; i <= n; i++) deg[i] = (int)adj[i].size();

priority_queue<int, vector<int>, greater<int>> leaves;
for (int i = 1; i <= n; i++) {
    if (deg[i] == 1) leaves.push(i);
}

vector<int> code;
code.reserve(max(0, n - 2));

for (int step = 0; step < n - 2; step++) {
    while (!leaves.empty() && deg[leaves.top()] != 1) leaves.pop();

    if (leaves.empty()) {
        quitf(_wa, "output graph is not a valid tree during Prufer encoding");
    }

    int leaf = leaves.top();
    leaves.pop();

    int parent = -1;
    for (int to : adj[leaf]) {
        if (deg[to] > 0) {
            parent = to;
            break;
        }
    }

    if (parent == -1) {
        quitf(_wa, "leaf %d has no active neighbor during Prufer encoding", leaf);
    }

    code.push_back(parent);
    deg[leaf] = 0;
    deg[parent]--;
    if (deg[parent] == 1) leaves.push(parent);
}

return code;

}

int main(int argc, char* argv[]) {
registerTestlibCmd(argc, argv);

int n = inf.readInt();

vector<int> target(max(0, n - 2));
for (int i = 0; i < n - 2; i++) {
    target[i] = inf.readInt();
}

vector<vector<int>> adj(n + 1);
DSU dsu(n);
unordered_set<long long> seenEdges;
seenEdges.reserve((size_t)n * 2 + 10);

for (int i = 0; i < n - 1; i++) {
    int a = ouf.readInt(1, n, format("edge[%d].a", i + 1).c_str());
    int b = ouf.readInt(1, n, format("edge[%d].b", i + 1).c_str());

    if (a == b) {
        quitf(_wa, "edge %d is a self-loop at node %d", i + 1, a);
    }

    long long key = edge_key(a, b, n);
    if (seenEdges.count(key)) {
        quitf(_wa, "duplicate edge %d-%d", min(a, b), max(a, b));
    }
    seenEdges.insert(key);

    if (!dsu.unite(a, b)) {
        quitf(_wa, "edge %d-%d creates a cycle", a, b);
    }

    adj[a].push_back(b);
    adj[b].push_back(a);
}

int root = dsu.find(1);
for (int v = 2; v <= n; v++) {
    if (dsu.find(v) != root) {
        quitf(_wa, "output graph is disconnected; node %d is not connected to node 1", v);
    }
}

vector<int> got = encode_prufer(n, adj);
if (got != target) {
    int pos = -1;
    for (int i = 0; i < (int)target.size(); i++) {
        if (got[i] != target[i]) {
            pos = i;
            break;
        }
    }
    if (pos == -1) {
        quitf(_wa, "encoded Prufer code does not match the input code");
    }
    quitf(_wa, "Prufer code mismatch at position %d: got %d, expected %d",
          pos + 1, got[pos], target[pos]);
}

if (!ouf.seekEof())
    quitf(_wa, "extra information in the output file");

quitf(_ok, "valid tree for Prufer code with %d nodes", n);

}
