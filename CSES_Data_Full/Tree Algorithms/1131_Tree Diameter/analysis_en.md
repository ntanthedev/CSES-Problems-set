# 1131 - Tree Diameter

There are multiple ways to approach this problem. On this page,
two of them will be presented.

## First approach

The first approach is based on the fact that when
we root the tree the diameter will have a single node
that is "higher" (i.e. closer to the root) than any other node.

![](95bf2a3f882b1fc0433559f862ce2c4dd93ff6a4f897df2820073396a8529798)

This observation leads to a dynamic programming solution where we, for each node, construct the longest
path in which the current node is the highest one. The longest of these paths will be the diameter.

In each node, we will store the longest distance from that node to any leaf in its subtree.
Let this distance for node $x$ be denoted by $\texttt{dist}(x)$.
The longest path, where the current node is the highest one, will be the maximum
of $\texttt{dist}(a) + \texttt{dist}(b) + 2$, where $a$ and $b$ are
any two distinct children of the current node.

When implementing this algorithm, we cannot check all pairs of children
for each node. What we can do instead is to store the largest distance
seen so far.

```cpp
#include <iostream>
#include <vector>
using namespace std;

const int N = 200001;
vector<int> g[N];
int dist[N];
int diameter = 0;

void dfs(int node, int parent) {
    int max_distance = 0;
    for (int child : g[node]) {
        if (child != parent) {
            dfs(child, node);
            diameter = max(diameter, max_distance + dist[child] + 1);
            max_distance = max(max_distance, dist[child] + 1);
        }
    }
    dist[node] = max_distance;
}

int main() {
    int n;
    cin >> n;

    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    dfs(1, 1);

    cout << diameter << '\n';
}
```

## Second approach

The second approach is based on an nontrivial observation:

The diameter of a tree can be found with two passes of DFS.
First, we begin at an arbitrary node $a$ and find the farthest node $b$ from $a$.
Similarly, we find the farthest node $c$ from $b$.
The path from $b$ to $c$ corresponds to the tree's diameter.

```cpp
#include <array>
#include <iostream>
#include <vector>
using namespace std;

const int N = 200001;
vector<int> g[N];

// Returns the pair
// {distance to the farthest node, label of the farthest node}
pair<int, int> dfs(int node, int parent) {
    auto result = pair{0, node};
    for (int child : g[node]) {
        if (child == parent) continue;
        auto ret = dfs(child, node);
        result = max(result, make_pair(ret.first + 1, ret.second));
    }
    return result;
}

int main() {
    int n;
    cin >> n;

    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    int farthest = dfs(1, 1).second;
    cout << dfs(farthest, farthest).first << '\n';
}
```

## References

* [CPHB (Competitive Programmer's Handbook)](http://cses.fi/book), Chapter 14