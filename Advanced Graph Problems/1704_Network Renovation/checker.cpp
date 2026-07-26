/*

* Problem:      1704 Network Renovation
* Input read:   n; n-1 tree edges
* Validity:     Output k new non-self connections; after adding them, the graph must have no bridges
* Optimality:   k must equal the minimum number of new connections from ans
* Complexity:   O(n + k) time, O(n + k) memory
  */
  #include "testlib.h"
  #include <bits/stdc++.h>
  using namespace std;

struct BridgeChecker {
vector<vector<int>> incident;
vector<pair<int, int>> edges;

explicit BridgeChecker(int n = 0) {
    incident.assign(n + 1, {});
}

void add_edge(int a, int b) {
    int id = (int)edges.size();
    edges.push_back({a, b});
    incident[a].push_back(id);
    incident[b].push_back(id);
}

int other(int u, int edgeId) const {
    return edges[edgeId].first ^ edges[edgeId].second ^ u;
}

bool has_bridge(int n) const {
    vector<int> tin(n + 1, 0), low(n + 1, 0), parent(n + 1, -1), parentEdge(n + 1, -1);
    vector<int> iter(n + 1, 0);

    int timer = 0;
    bool foundBridge = false;

    for (int root = 1; root <= n; root++) {
        if (tin[root]) continue;

        parent[root] = 0;

        vector<int> st;
        st.push_back(root);

        while (!st.empty()) {
            int u = st.back();

            if (!tin[u]) {
                tin[u] = low[u] = ++timer;
            }

            if (iter[u] < (int)incident[u].size()) {
                int edgeId = incident[u][iter[u]++];

                if (edgeId == parentEdge[u]) {
                    continue;
                }

                int v = other(u, edgeId);

                if (!tin[v]) {
                    parent[v] = u;
                    parentEdge[v] = edgeId;
                    st.push_back(v);
                } else {
                    low[u] = min(low[u], tin[v]);
                }
            } else {
                st.pop_back();

                if (parent[u] != 0) {
                    int p = parent[u];

                    if (low[u] > tin[p]) {
                        foundBridge = true;
                    }

                    low[p] = min(low[p], low[u]);
                }
            }
        }
    }

    return foundBridge;
}

};

int main(int argc, char* argv[]) {
registerTestlibCmd(argc, argv);

int n = inf.readInt();

BridgeChecker checker(n);

for (int i = 0; i < n - 1; i++) {
    int a = inf.readInt();
    int b = inf.readInt();

    checker.add_edge(a, b);
}

int optimal = ans.readInt();

int k = ouf.readInt(0, n, "number of new connections");
if (k != optimal) {
    quitf(_wa, "contestant printed %d new connections, but optimum is %d", k, optimal);
}

for (int i = 1; i <= k; i++) {
    int a = ouf.readInt(1, n, format("connection[%d].a", i).c_str());
    int b = ouf.readInt(1, n, format("connection[%d].b", i).c_str());

    if (a == b) {
        quitf(_wa, "connection %d is a self-loop at computer %d", i, a);
    }

    checker.add_edge(a, b);
}

if (checker.has_bridge(n)) {
    quitf(_wa, "graph still has a bridge after adding the new connections");
}

if (!ouf.seekEof())
    quitf(_wa, "extra information in the output file");

quitf(_ok, "valid minimum solution with %d new connections", k);

}
