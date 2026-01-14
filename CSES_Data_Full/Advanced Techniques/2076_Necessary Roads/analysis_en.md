# 2076 - Necessary Roads

It is worth acknowledging that the *necessary roads* are more commonly known as
bridges. To find the bridges of the given graph, think of the graph in terms of
its DFS trees. A DFS tree represents the order we visit the nodes when we do a
depth-first search. The root of the tree is the first node of the traversal and
subsequent nodes are placed as children of the nodes from which they are
visited.

Here is an example of a graph and one of its DFS trees where the traversal was
started at node 1.

![](725ee9e085b0ca93fe59b5f4b206a05b8d551c5b51378a107f1f04b12bc72b26)

The bridges of the graph are $(3, 6), (1, 3)$ and $(1, 4)$.

Note that there may be more than one way to visit the nodes and thus, more than
one DFS tree. However, the properties we are interested in apply to all DFS
trees. The edges of the DFS tree form a subset of the edges of the original
graph. The edges that are not part of the tree are called *back-edges*. It can
be proven that back-edges always go from a node to its ancestor.

Notice that bridge edges are always *tree edges*, that is, they are always part
of the DFS tree as otherwise, if a back-edge was a bridge, removing the edge
would not break the graph into two separate components. Bridges also have
another important property. A tree edge $a\rightarrow b$ is bridge if there are
no back-edges from $b$'s subtree to $a$ or any $a$'s ancestors. In the example,
the edge $(1, 3)$ is a bridge as there are no back-edges from the subtree of 3
to 1.

The implementation details of the algorithm are similar to Tarjan's algorithm
for finding the strongly connected components of a directed graph. We will start
by assigning each node a depth value which tells us its distance from the root
node in the DFS tree. We will then find, for each node, the minimum depth of a
node that is reachable by a back-edge from the subtree of the node. The minimum
reachable depth determines which edges are bridges. The implementation has a
time complexity of $O(n)$

```cpp
#include <iostream>
#include <vector>
using namespace std;

const int N = 1e5 + 1;
vector<int> g[N];
vector<pair<int, int>> bridges;
bool visited[N];
int depth[N], min_depth[N];

void dfs(int node, int prev) {
    visited[node] = true;
    min_depth[node] = depth[node];
    for (int nxt : g[node]) {
        if (nxt == prev) continue;
        if (visited[nxt]) {
            min_depth[node] = min(min_depth[node], depth[nxt]);
        } else {
            depth[nxt] = depth[node] + 1;
            dfs(nxt, node);
            min_depth[node] = min(min_depth[node], min_depth[nxt]);
            if (min_depth[nxt] > depth[node]) {
                bridges.emplace_back(node, nxt);
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= m; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    dfs(1, 0);

    cout << bridges.size() << '\n';
    for (auto [a, b] : bridges) {
        cout << a << ' ' << b << '\n';
    }
}
```

## References

* [Bridge (Wikipedia)](https://en.wikipedia.org/wiki/Bridge_(graph_theory))