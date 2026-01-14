# 1160 - Planets Queries II

We start by noticing that the planets and teleports form a graph where
every connected component is formed of a cycle and trees (possibly consisting
of only one planet) starting from each planet in the cycle.

Instead of answering the queries in the order they appear in the input,
we will first read all queries, go through all planets and, for each planet
$x$, find answers to the queries which have $x$ as their starting planet.

We will process every component separately. We start processing a component by
finding the cycle (in the example solution, using Floyd's tortoise and hare
algorithm). Let's denote the nodes in the cycle by $c\_1, \dots, c\_k$
where $c\_{i + 1}$ can be reached from $c\_{i}$ with a teleport. We will
then run a depth-first search (DFS) from $c\_1$ in a graph where we have
reversed all teleports.

We generalize the notion of depth in the DFS by
associating $c\_2$ with depth $-1$, $c\_3$ with depth $-2$, and so on
for all nodes in the cycle. In the DFS we maintain an array $\mathrm{depth}$
containing, for each node, the maximum depth associated with the node
(considering both the DFS tree and the cycle). If a node $x$ is neither part of
the cycle nor the DFS tree, we set $\mathrm{depth}[x] = -\infty$.

To answer a query $a,b$ while processing node $a$
we can now simply check if $\mathrm{depth}[b]$ has been set to negative
infinity and, if not, calculate the difference
$\mathrm{depth}[a] - \mathrm{depth}[b]$.

The time complexity of the solution is $O(n + q)$

```cpp
#include <iostream>
#include <vector>

using namespace std;

const int N = 200001;
const int INF = 1e9;
int teleport[N];
vector<int> rev_graph[N];
int answer[N];
// pairs of b, id
vector<pair<int, int>> queries[N];
int depth[N];
bool visited[N];

vector<int> extract_cycle(int x) {
    int a = x;
    int b = teleport[x];
    while (a != b) {
        a = teleport[a];
        b = teleport[teleport[b]];
    }
    vector<int> cycle;
    do {
        a = teleport[a];
        cycle.push_back(a);
    } while (a != b);
    return cycle;
}

void dfs(int x, int d) {
    visited[x] = true;
    int previous_depth = depth[x];
    depth[x] = d;
    for (auto [b, id] : queries[x]) {
        if (depth[b] > -INF) {
            answer[id] = d - depth[b];
        } else {
            answer[id] = -1;
        }
    }
    for (int y : rev_graph[x]) {
        if (!visited[y]) {
            dfs(y, d + 1);
        }
    }
    depth[x] = previous_depth;
}

int main() {
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; ++i) {
        int t;
        cin >> t;
        teleport[i] = t;
        rev_graph[t].push_back(i);
        depth[i] = -INF;
    }
    for (int i = 1; i <= q; ++i) {
        int a, b;
        cin >> a >> b;
        queries[a].emplace_back(b, i);
    }

    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            auto cycle = extract_cycle(i);
            for (int j = 1; j < cycle.size(); ++j) {
                depth[cycle[j]] = -j;
            }
            dfs(cycle[0], 0);
            for (int j = 1; j < cycle.size(); ++j) {
                depth[cycle[j]] = -INF;
            }
        }
    }

    for (int i = 1; i <= q; ++i) {
        cout << answer[i] << '\n';
    }
}
```