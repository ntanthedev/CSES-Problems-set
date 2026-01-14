# 2143 - Reachability Queries

It is useful to think of the problem in terms of strongly connected components.
In particular, if two nodes are in the same in the same component, they are both
reachable from each other.

The strongly connected components of the graph also form a directed acyclic
graph (DAG) of their own. There cannot be cycles in the graph condensed from the
components because if it contained a cycle of multiple components, the nodes of
the cycle would, by definition, form only a single component.

Once we have found the strongly connected components using Tarjan's algorithm,
we have reduced the problem to a DAG. Because there are no cycles in a DAG, we
can make a dynamic programming solution. In particular, we may store, for each
node, information about which other nodes are reachable from it. The
reachability information can be copied to each *parent* of a node, once all
the children of the node have been fully processed.

If we were to store the reachability information in a boolean array, the
solution would turn out too slow. We may, however, use bitsets to speed up the
transformation of the information as bitsets allow us to update 64 elements at
once.

```cpp
#include <bitset>
#include <iostream>
#include <vector>
using namespace std;

const int N = 5e4 + 1;
vector<int> g[N];
int cur_depth, comp_cnt;
int comp[N], depth[N], low[N];
vector<int> stack;
bool in_stack[N];

// Tarjan's strongly connected components algorithm
void scc_dfs(int node) {
    low[node] = depth[node] = ++cur_depth;
    stack.push_back(node);
    in_stack[node] = true;
    for (int nxt : g[node]) {
        if (!depth[nxt]) {
            scc_dfs(nxt);
            low[node] = min(low[node], low[nxt]);
        } else if (in_stack[nxt]) {
            low[node] = min(low[node], depth[nxt]);
        }
    }
    if (depth[node] == low[node]) {
        int i = -1;
        ++comp_cnt;
        while (i != node) {
            i = stack.back();
            stack.pop_back();
            in_stack[i] = false;
            comp[i] = comp_cnt;
        }
    }
}

using B = bitset<N>;
// `cg` is a condensed graph constructed from the SCC's.
vector<int> cg[N];
B reach[N];
bool visited[N];

void dfs(int node) {
    if (visited[node]) return;
    visited[node] = true;
    reach[node][node] = true;
    for (int nxt : cg[node]) {
        dfs(nxt);
        reach[node] |= reach[nxt];
    }
}

int main() {
    int n, m, q;
    cin >> n >> m >> q;

    for (int i = 1; i <= m; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
    }

    for (int i = 1; i <= n; ++i) {
        if (!depth[i]) scc_dfs(i);
    }

    for (int i = 1; i <= n; ++i) {
        for (int j : g[i]) {
            if (comp[i] != comp[j]) {
                cg[comp[i]].push_back(comp[j]);
            }
        }
    }

    for (int i = 1; i <= comp_cnt; ++i) {
        dfs(i);
    }

    for (int qi = 1; qi <= q; ++qi) {
        int a, b;
        cin >> a >> b;
        cout << (reach[comp[a]][comp[b]] ? "YES" : "NO") << '\n';
    }
}
```