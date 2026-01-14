# 1132 - Tree Distances I

This task can be solved with dynamic programming.
For each node, we will calculate and store two values

1. $\texttt{max\\_dist}\_0$ the longest distance from this node to some other node
2. $\texttt{max\\_dist}\_1$ the longest distance from this node to some other node
   provided that the path to that node goes through some other neighbour
   than the path corresponding to $\texttt{max\\_dist}\_0$.

Let us root the tree.
First, we will calculate the maximum distances downwards (not going through
the parent). Then, we will do another depth-first search that
offers paths through the parents.

At each node, we will offer the child a candidate for the maximum distance.
If the path corresponding to $\texttt{max\\_dist}\_0$ goes through that child,
we will offer it the distance $\texttt{max\\_dist}\_1+1$, otherwise
we will offer it $\texttt{max\\_dist}\_0+1$.

```cpp
#include <iostream>
#include <vector>
using namespace std;

const int N = 200001;
vector<int> g[N];
int max_dist[N][2];

void update(int node, int offer) {
    if (offer > max_dist[node][0]) {
        max_dist[node][1] = max_dist[node][0];
        max_dist[node][0] = offer;
    } else if (offer > max_dist[node][1]) {
        max_dist[node][1] = offer;
    }
}

void dfs1(int node, int parent) {
    for (int child : g[node]) {
        if (child == parent) continue;
        dfs1(child, node);
        update(node, max_dist[child][0] + 1);
    }
}

void dfs2(int node, int parent) {
    for (int child : g[node]) {
        if (child == parent) continue;
        if (max_dist[node][0] == max_dist[child][0] + 1) {
            update(child, max_dist[node][1] + 1);
        } else {
            update(child, max_dist[node][0] + 1);
        }
        dfs2(child, node);
    }
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

    dfs1(1, 1);

    dfs2(1, 1);

    for (int i = 1; i <= n; ++i) {
        cout << max_dist[i][0] << ' ';
    }
    cout << '\n';
}
```

## References

* [CPHB (Competitive Programmer's Handbook)](http://cses.fi/book), Chapter 14