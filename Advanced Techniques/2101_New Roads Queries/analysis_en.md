# 2101 - New Roads Queries

## Solution 1: Parallel Binary Search

This problem may be solved efficiently with a technique called *parallel binary
search*. This means that we binary search the answers to all queries
simultaneously.

Were we to use binary search for answering each query separately, we would have
to construct a union find structure for checking each midpoint during each
search. The time complexity of constructing a union find structure is $O(m \log
n)$, making the total time complexity of this solution $O(qm \log^2 n)$, which
is too slow.

The key idea is that we need only $O(\log m)$ of such structures to answer all
queries. We will start by assigning each query a range $[l, r]$ which means that
the cities will become connected at earliest on day $l$ and at latest on day
$r$. Initially the range will be $[0, m]$.

Then, we will simulate the construction of the roads $\log m$ times. Just like
with regular binary search, we will calculate the midpoint of each range, and
check if the cities at connected at that time. Depending on the result, we will
change the lower or upper bound of each range to the midpoint, effectively
halving each range.

Adding $m$ roads to the network takes $O(m \log n)$ time and updating the ranges
$O(q \log n)$ time, making the total time complexity $O(\log m \cdot (m + q)
\log n)$.

```cpp
#include <iostream>
#include <vector>
using namespace std;

struct UnionFind {
    int n;
    // If p[i] < 0, i is a root node with a tree size of -p[i].
    // Otherwise, p[i] represents the parent of i.
    vector<int> p;
    UnionFind(int n) : n(n), p(n, -1) {}
    int root(int s) {
        while (p[s] >= 0) {
            s = p[s];
        }
        return s;
    }
    void merge(int a, int b) {
        a = root(a);
        b = root(b);
        if (a == b) return;
        if (p[a] < p[b]) swap(a, b);
        p[b] += p[a];
        p[a] = b;
    }
};

int main() {
    int n, m, q;
    cin >> n >> m >> q;

    UnionFind graph(n);
    vector<pair<int, int>> edges(m);
    for (auto &[a, b] : edges) {
        cin >> a >> b;
        a--;
        b--;
        graph.merge(a, b);
    }

    vector<int> qa(q), qb(q), ql(q), qr(q);
    for (int i = 0; i < q; ++i) {
        int &a = qa[i], &b = qb[i];
        cin >> a >> b;
        a--;
        b--;
        ql[i] = 0;
        qr[i] = m;
    }

    int log2 = __lg(m + 1);

    for (int t = 0; t < log2 + 1; ++t) {
        vector<vector<int>> queries(m + 1);
        for (int i = 0; i < q; ++i) {
            if (ql[i] < qr[i]) {
                queries[(ql[i] + qr[i]) / 2].push_back(i);
            }
        }
        UnionFind uf(n);
        for (int i = 0; i < m; ++i) {
            for (int qi : queries[i]) {
                if (uf.root(qa[qi]) == uf.root(qb[qi])) {
                    qr[qi] = i;
                } else {
                    ql[qi] = i + 1;
                }
            }
            uf.merge(edges[i].first, edges[i].second);
        }
    }

    for (int i = 0; i < q; ++i) {
        if (graph.root(qa[i]) != graph.root(qb[i])) {
            cout << -1 << '\n';
        } else {
            cout << ql[i] << '\n';
        }
    }
}
```

## Solution 2: Binary Lifting

Another approach, which is able to answer the queries online, is to use binary
lifting.

First, we will have to examine the given graph. Note it may not be connected. If
two nodes are in different components, they will never be reachable. Thus, we
may only focus on a single component. If we think of the time an edge is added
to the graph as the weight of the edge, we may find a minimum spanning tree of
each component. The maximum edge weight on a path between two nodes in the
spanning tree corresponds to the first time the nodes will be reachable. The
construction of the spanning trees is easily done with Kruskal's algorithm as
the edges are already sorted by their weights.

Now, we may use binary lifting to find the maximum weight edge on a path between
any two nodes. We will proceed similarly to the binary lifting LCA algorithm,
except that for each jump, we will also store the maximum weight edge on the
path corresponding to the jump.

```cpp
#include <iostream>
#include <vector>
using namespace std;

struct UnionFind {
    int n;
    // If p[i] < 0, i is a root node with a tree size of -p[i].
    // Otherwise, p[i] represents the parent of i.
    vector<int> p;
    UnionFind(int n) : n(n), p(n, -1) {}
    int root(int s) {
        while (p[s] >= 0) {
            s = p[s];
        }
        return s;
    }
    void merge(int a, int b) {
        a = root(a);
        b = root(b);
        if (a == b) return;
        if (p[a] < p[b]) swap(a, b);
        p[b] += p[a];
        p[a] = b;
    }
};

const int N = 200000;
vector<pair<int, int>> g[N];
int jmp[N][20], jmp_time[N][20];
int depth[N], component[N];
bool visited[N];

void dfs(int node) {
    visited[node] = true;
    for (auto [nxt, t] : g[node]) {
        if (!visited[nxt]) {
            component[nxt] = component[node];
            depth[nxt] = depth[node] + 1;
            jmp[nxt][0] = node;
            jmp_time[nxt][0] = t;
            dfs(nxt);
        }
    }
}

int main() {
    int n, m, q;
    cin >> n >> m >> q;

    UnionFind uf(n);
    for (int i = 1; i <= m; ++i) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        if (uf.root(a) != uf.root(b)) {
            uf.merge(a, b);
            g[a].emplace_back(b, i);
            g[b].emplace_back(a, i);
        }
    }

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            depth[i] = 0;
            component[i] = i;
            jmp[i][0] = i;
            dfs(i);
        }
    }

    for (int j = 0; j < 19; ++j) {
        for (int i = 0; i < n; ++i) {
            jmp[i][j + 1] = jmp[jmp[i][j]][j];
            jmp_time[i][j + 1] = max(jmp_time[i][j], jmp_time[jmp[i][j]][j]);
        }
    }

    auto answer = [&](int a, int b) {
        int r = 0;
        if (depth[a] < depth[b]) {
            swap(a, b);
        }
        for (int j = 19; j >= 0; --j) {
            if (depth[jmp[a][j]] >= depth[b]) {
                r = max(r, jmp_time[a][j]);
                a = jmp[a][j];
            }
        }
        if (a == b) {
            return r;
        }
        for (int j = 19; j >= 0; --j) {
            if (jmp[a][j] != jmp[b][j]) {
                r = max(r, jmp_time[a][j]);
                r = max(r, jmp_time[b][j]);
                a = jmp[a][j];
                b = jmp[b][j];
            }
        }
        r = max(r, jmp_time[a][0]);
        r = max(r, jmp_time[b][0]);
        return r;
    };

    for (int i = 0; i < q; ++i) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        if (component[a] != component[b]) {
            cout << -1 << '\n';
        } else {
            cout << answer(a, b) << '\n';
        }
    }
}
```

## Solution 3: Union Find Merge

An even simpler offline-approach is to use the union find structure for
answering the queries directly.

Let us store a list of query indices in each node. We will store the index of each
query in the lists of both of the query nodes. After this, we will add each edge
to the structure, one by one. Before each addition, we will check if the lists
of the merged trees contain any equal indices. If an index is contained in the
lists of both of the disjoint trees, the added edge will be the first one after
which the cities of the corresponding query become reachable.

Implementation-wise, the lists will be stored in the root node of each tree, and
will be merged using the small-to-large technique. This ensures that each node
will be merged at most $O(\log n)$ times and since there are $q$ indices stored
in the lists, there will be at most $O(q \log n)$ list element merges. Each
merge, in turn, takes $O(\log n)$ time as a single union find query will be used
for checking whether the corresponding nodes became reachable. Thus, the
resulting algorithm has a time complexity of $O(m \log n + q \log^2 n)$.

```cpp
#include <iostream>
#include <vector>
using namespace std;

const int N = 200000;
int qa[N], qb[N], ans[N];

struct UnionFind {
    int n;
    // If p[i] < 0, i is a root node with a tree size of -p[i].
    // Otherwise, p[i] represents the parent of i.
    vector<int> p;
    // Stores the indices of queries at root nodes.
    vector<vector<int>> q;
    UnionFind(int n) : n(n), p(n, -1), q(n) {}
    int root(int s) {
        while (p[s] >= 0) {
            s = p[s];
        }
        return s;
    }
    void merge(int a, int b, int t) {
        a = root(a);
        b = root(b);
        if (a == b) return;
        if (p[a] < p[b]) {
            swap(a, b);
        }
        p[b] += p[a];
        p[a] = b;
        if (q[b].size() < q[a].size()) {
            swap(q[a], q[b]);
        }
        for (int i : q[a]) {
            if (ans[i] != -1) continue;
            if (root(qa[i]) == root(qb[i])) {
                ans[i] = t;
            } else {
                q[b].push_back(i);
            }
        }
        q[a].clear();
    }
};

int main() {
    int n, m, q;
    cin >> n >> m >> q;

    vector<pair<int, int>> edges(m);
    for (auto &[a, b] : edges) {
        cin >> a >> b;
        a--;
        b--;
    }

    UnionFind uf(n);
    for (int i = 0; i < q; ++i) {
        int &a = qa[i], &b = qb[i];
        cin >> a >> b;
        a--;
        b--;
        if (a == b) {
            ans[i] = 0;
        } else {
            ans[i] = -1;
            uf.q[a].push_back(i);
            uf.q[b].push_back(i);
        }
    }

    for (int i = 0; i < m; ++i) {
        uf.merge(edges[i].first, edges[i].second, i + 1);
    }

    for (int i = 0; i < q; ++i) {
        cout << ans[i] << '\n';
    }
}
```