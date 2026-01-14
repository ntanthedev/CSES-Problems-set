# 1136 - Counting Paths

Let us root the tree arbitrarily.
Notice that, in a rooted tree, any path between
some nodes $a$ and $b$ can be split into two paths:

1. the part from $a$ to $\textrm{lca}(a, b)$,
2. the part from $b$ to $\textrm{lca}(a, b)$.

In this problem we will process these parts separately.
Each node will have two values:

1. the number of paths starting at that node (going up),
2. the number of paths ending at this node.

We will use a dynamic programming approach.
The paths through this node can be calculated by
adding up the amount of paths that come from the children
and the amount of paths starting at this node.

We have to make sure to remove the paths that end
at this node from our counter.
Note that each path is counted twice at
its highest node (the LCA node). Fortunately, the number
of doubly counted paths at any node is simply the number
of paths ending at that node.

```cpp
#include <iostream>
#include <vector>
using namespace std;

const int N = 200000;
int jmp[N][20];
int depth[N];
vector<int> g[N];

void dfs(int node, int parent) {
    jmp[node][0] = parent;
    for (int child : g[node]) {
        if (child == parent) continue;
        depth[child] = depth[node] + 1;
        dfs(child, node);
    }
}

int lca(int a, int b) {
    if (depth[a] < depth[b]) {
        swap(a, b);
    }
    int depth_difference = depth[a] - depth[b];
    for (int j = 19; j >= 0; --j) {
        if ((1 << j) & depth_difference) {
            a = jmp[a][j];
        }
    }
    if (a == b) {
        return a;
    } else {
        for (int j = 19; j >= 0; --j) {
            if (jmp[a][j] != jmp[b][j]) {
                a = jmp[a][j];
                b = jmp[b][j];
            }
        }
        return jmp[a][0];
    }
}

int paths_starting[N];
int paths_ending[N];
int answer[N];

int dfs_paths(int node, int parent) {
    int current_paths = paths_starting[node];
    for (int child : g[node]) {
        if (child == parent) continue;
        current_paths += dfs_paths(child, node);
    }
    // Paths ending at the current node are counted twice.
    current_paths -= paths_ending[node];
    answer[node] = current_paths;
    current_paths -= paths_ending[node];
    return current_paths;
}

int main() {
    int n, m;

    cin >> n >> m;

    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    dfs(0, 0);

    for (int j = 0; (1 << j) <= n; ++j) {
        for (int i = 0; i < n; ++i) {
            jmp[i][j + 1] = jmp[jmp[i][j]][j];
        }
    }

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        int c = lca(a, b);
        paths_starting[a]++;
        paths_starting[b]++;
        paths_ending[c]++;
    }

    dfs_paths(0, 0);

    for (int i = 0; i < n; ++i) {
        cout << answer[i] << ' ';
    }
    cout << '\n';
}
```

### References

* [CPHB (Competitive Programmer's Handbook)](http://cses.fi/book), Chapter 18