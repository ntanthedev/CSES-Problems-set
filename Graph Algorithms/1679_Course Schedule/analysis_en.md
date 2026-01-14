# 1679 - Course Schedule

The problem asks us to create a topological sort of the courses. A
topological sorting of a directed graph is defined as an ordering of nodes such that
if there is a path from node $a$ to $b$, then $a$ appears before $b$ in
the ordering.

We will first solve the problem by using Kahn's algorithm. In Kahn's
algorithm we construct a topological sort by removing nodes one by one
from the graph, always selecting a node without any incoming edges. If we can
remove all nodes from the graph then the resulting order is a topological sort
as if there is a path $x\_1, \dots, x\_k$, then in order to remove $x\_k$ we must
have already removed $x\_{k-1},$ $x\_{k-2}, \dots$ and finally $x\_1$.

Let's then assume we cannot remove all nodes from the original graph $G$ and
denote these remaining nodes by $R = \{r\_1, \dots, r\_k\}$. Now for every
$x \in R$ there must be a node $y\in R$ so that there is an edge from
$y$ to $x$. Let's also assume that there still exists a topological sort
of the nodes in $G$. In the topological sort, one of the nodes $z \in R$
has to be the first among $R$. This is impossible since we assumed that there
always exists a node $y\in R$ so that there is an edge from to $z$. Therefore,
if we cannot remove all nodes from the graph, no topological sort exists for
the graph.

The time complexity of the solution is $O(n + m)$.

```cpp
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> in_degree(n + 1);
    vector<vector<int>> g(n + 1);

    for (int i = 1; i <= m; ++i) {
        int a, b;
        cin >> a >> b;
        ++in_degree[b];
        g[a].push_back(b);
    }

    vector<int> no_incoming;

    for (int i = 1; i <= n; ++i) {
        if (in_degree[i] == 0) {
            no_incoming.push_back(i);
        }
    }

    for (int i = 0; i < no_incoming.size(); ++i) {
        int x = no_incoming[i];
        for (int y : g[x]) {
            --in_degree[y];
            if (in_degree[y] == 0) {
                no_incoming.push_back(y);
            }
        }
    }

    if (no_incoming.size() < n) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    for (int x : no_incoming) {
        cout << x << ' ';
    }
    cout << '\n';
}
```

Let's then present another solution to the problem.
We solve the problem by running a depth-first search (DFS)
from every unvisited node in the graph. Every time we have processed
a node and are about to pop it from the DFS stack, we will add it
to the end of a vector `reverse_answer`. For every node we also check
if any of the node's neighbours are already in the DFS stack. If this is the
case, we have found a cycle which means that no topological sort exists for the
graph.

Let's then prove that if no cycles are found, then the `reverse_answer`
will contain a topological sort in reverse order. For every pair of nodes
$x$ and $y$, where $y$ is reachable from $x$, we need to consider two cases.
Either $x$ and $y$ were processed by the same search or different searches.
In both cases $y$ must have been added to `reverse_answer` before $x$.
Therefore reversed `reverse_answer` is a topological sort.

The time complexity of the solution is $O(n + m)$.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
const int N = 100001;

vector<int> g[N];
bool visited[N];
bool active[N];
vector<int> reverse_answer;

bool dfs(int x) {
    if (active[x]) return false;
    if (visited[x]) return true;
    active[x] = true;
    visited[x] = true;
    for (int y : g[x]) {
        if (!dfs(y)) return false;
    }
    active[x] = false;
    reverse_answer.push_back(x);
    return true;
}

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
    }

    for (int i = 1; i <= n; ++i) {
        if (!dfs(i)) {
            cout << "IMPOSSIBLE\n";
        }
    }
    reverse(reverse_answer.begin(), reverse_answer.end());

    for (int x : reverse_answer) {
        cout << x << ' ';
    }
    cout << '\n';
}
```

## References

* [Topological sorting (Wikipedia)](https://en.wikipedia.org/wiki/Topological_sorting)
* [CPHB (Competitive Programmer's Handbook)](http://cses.fi/book),
  Chapter 7.4.1