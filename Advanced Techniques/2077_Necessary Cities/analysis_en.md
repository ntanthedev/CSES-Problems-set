# 2077 - Necessary Cities

*Necessary cities* are more commonly referred to as the *articulation points* of
a graph. It is useful to think of the graph in terms of its DFS trees. A DFS
tree represents the order in which we visit the nodes when we do a depth-first
search. The root of the tree is the first node of the traversal and subsequent
nodes are placed as children of the nodes from which they are visited.

Here is an example of a graph and one of its DFS trees where the traversal was
started at node 1.

![](725ee9e085b0ca93fe59b5f4b206a05b8d551c5b51378a107f1f04b12bc72b26)

From the DFS tree, it can be seen that the nodes $1$ and $3$ are the
articulation points of the graph.

The edges of the DFS tree form a subset of the edges of the original graph. Let
us call the edges that are part of the tree *tree edges* and the rest of them
*back-edges*. There is a simple condition for checking whether a node is an
articulation point which works for all nodes expect the root of the DFS tree:
The node $x$ is an articulation point of the graph if it has a child from whose
subtree there are no *back-edges* to any of the $x$'s strict ancestors. In the
example graph, $3$ is an articulation point as neither of its children's
subtrees contain *back-edges* to $3$'s ancestors. Lastly, the root of the DFS
tree is an articulation point if the has more than one child.

The implementation details of the algorithm are similar to Tarjan's algorithm
for finding the strongly connected components of a directed graph. We will start
by assigning each node a depth value which tells us its distance from the root
node in the DFS tree. We will then find, for each node, the minimum depth of a
node that is reachable by a back-edge from the subtree of the node. The
algorithm can be implemented in linear time.

```cpp
#include <iostream>
#include <vector>
using namespace std;

const int N = 1e5 + 1;
vector<int> g[N];
vector<int> answer;
bool visited[N];
int depth[N], min_depth[N];

void dfs(int node, int prev) {
    bool is_root = prev == 0;
    bool found = false;
    int children = 0;
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
            children++;
            if (min_depth[nxt] >= depth[node]) found = true;
        }
    }
    if ((is_root && children > 1) || (!is_root && found)) {
        answer.push_back(node);
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

    cout << answer.size() << '\n';
    for (int node : answer) {
        cout << node << ' ';
    }
    cout << '\n';
}
```