# 1669 - Round Trip

Our task is to find a cycle in an undirected graph.
The following code uses a modified depth-first search that
maintains a path from the starting node to the current node
in the depth-first search tree.
When we visit a node we have visited before,
we construct a cycle that includes that node.

Consider a node $x$ that is the first node in a cycle
we visit during the search.
Since there is a path from node $x$ to itself through
unvisited nodes, the depth-first search tree path will
eventually contain node $x$ twice.
This allows us to construct a cycle.

We go through all nodes in the graph
and start a search from every unvisited node.
If we do not find a cycle, there is no cycle in the graph.

The code works in $O(n + m)$ time.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> graph;
vector<bool> visited;
vector<int> path;

void cycle_search(int node, int parent) {
    path.push_back(node);

    if (visited[node]) {
        auto it = find(path.begin(), path.end(), node);
        cout << path.end() - it << "\n";

        auto cycle = vector<int>(it, path.end());
        for (auto node : cycle) {
            cout << node << " ";
        }
        cout << "\n";

        exit(0);
    }

    visited[node] = true;

    for (auto next_node : graph[node]) {
        if (next_node != parent) {
            cycle_search(next_node, node);
        }
    }

    path.pop_back();
}

int main() {
    int n, m;
    cin >> n >> m;

    graph.resize(n + 1);
    for (int i = 1; i <= m; ++i) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    visited.resize(n + 1);
    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            cycle_search(i, 0);
        }
    }

    cout << "IMPOSSIBLE\n";
}
```