/*

* Problem:      1695 Police Chase
* Input read:   n, m; m undirected streets
* Validity:     Output k streets from the input, all distinct; after closing them,
* ```
            there must be no route from crossing 1 to crossing n
* Optimality:   k must equal the minimum cut size from ans
* Complexity:   O(n + m) expected time, O(n + m) memory
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

vector<pair<int, int>> edges;
edges.reserve(m);

vector<vector<pair<int, int>>> adj(n + 1);
unordered_set<long long> inputEdges;
inputEdges.reserve((size_t)m * 2 + 10);

for (int i = 0; i < m; i++) {
    int a = inf.readInt();
    int b = inf.readInt();

    edges.push_back({a, b});
    adj[a].push_back({b, i});
    adj[b].push_back({a, i});
    inputEdges.insert(edge_key(a, b, n));
}

int optimal = ans.readInt();

int k = ouf.readInt(0, m, "number of streets");
if (k != optimal) {
    quitf(_wa, "contestant printed %d streets, but optimum is %d", k, optimal);
}

vector<char> closed(m, 0);
unordered_set<long long> closedKeys;
closedKeys.reserve((size_t)k * 2 + 10);

for (int i = 1; i <= k; i++) {
    int a = ouf.readInt(1, n, format("street[%d].a", i).c_str());
    int b = ouf.readInt(1, n, format("street[%d].b", i).c_str());

    if (a == b) {
        quitf(_wa, "street %d is a self-loop at crossing %d", i, a);
    }

    long long key = edge_key(a, b, n);

    if (!inputEdges.count(key)) {
        quitf(_wa, "street %d-%d does not exist in the city", a, b);
    }

    if (closedKeys.count(key)) {
        quitf(_wa, "street %d-%d is listed more than once", min(a, b), max(a, b));
    }

    closedKeys.insert(key);
}

for (int id = 0; id < m; id++) {
    if (closedKeys.count(edge_key(edges[id].first, edges[id].second, n))) {
        closed[id] = 1;
    }
}

vector<char> vis(n + 1, 0);
queue<int> q;

vis[1] = 1;
q.push(1);

while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (auto [v, id] : adj[u]) {
        if (closed[id] || vis[v]) continue;

        vis[v] = 1;
        q.push(v);
    }
}

if (vis[n]) {
    quitf(_wa, "a route from crossing 1 to crossing %d still exists after closing %d streets",
          n, k);
}

if (!ouf.seekEof())
    quitf(_wa, "extra information in the output file");

quitf(_ok, "valid minimum cut of size %d", k);

}
