# 2081 - Fixed Length Paths II

## Solution 1: Centroid Decomposition

This problem can be solved with centroid decomposition.

The idea is to recursively split the tree into disjoint trees. We find a
centroid node of each tree and calculate the number of paths with a length
between $k\_1$ and $k\_2$ which go through the centroid. After this, all
unaccounted paths are completely contained in the subtrees of the node. Thus, we
may remove the centroid from the tree and repeat the same procedure for the
resulting new trees.

We use a Fenwick tree to count the number of nodes at specific distances from
the centroid.

At each step, the sizes of the resulting trees will be at most half of the
original size. This means that each node will be part of at most $O(\log n)$
trees. As processing a node corresponds to a query in the Fenwick tree and every
node of every tree is processed exactly twice, the total time complexity of the
solution is $O(n\log^2n)$.

```cpp
#include <array>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

struct FenwickTree {
    static const int N = 200000;
    array<int, N + 1> tree;
    void add(int k, int d) {
        for (int i = k + 1; i <= N; i += i & -i) {
            tree[i] += d;
        }
    }
    int sum(int k) {
        int s = 0;
        for (int i = k; i > 0; i -= i & -i) {
            s += tree[i];
        }
        return s;
    }
    int sum(int l, int r) { return sum(r + 1) - sum(l); }
} tree;

const int N = 200001;
bool deleted[N];
int n, k1, k2, sizes[N];
vector<int> g[N];
ll answer;

void dfs_sizes(int node, int parent) {
    sizes[node] = 1;
    for (int child : g[node]) {
        if (child == parent || deleted[child]) continue;
        dfs_sizes(child, node);
        sizes[node] += sizes[child];
    }
}

int find_centroid(int node, int parent, int n) {
    for (int child : g[node]) {
        if (child != parent && !deleted[child] && sizes[child] > n / 2) {
            return find_centroid(child, node, n);
        }
    }
    return node;
}

void dfs_add(int node, int parent, int depth, int change) {
    tree.add(depth, change);
    for (int child : g[node]) {
        if (child == parent || deleted[child]) continue;
        dfs_add(child, node, depth + 1, change);
    }
}

void dfs_query(int node, int parent, int depth) {
    answer += tree.sum(k1 - depth, k2 - depth);
    for (int child : g[node]) {
        if (child == parent || deleted[child]) continue;
        dfs_query(child, node, depth + 1);
    }
}

void recurse(int node) {
    dfs_sizes(node, -1);
    int r = find_centroid(node, -1, sizes[node]);
    tree.add(0, 1);
    for (int child : g[r]) {
        if (!deleted[child]) {
            dfs_query(child, r, 1);
            dfs_add(child, r, 1, 1);
        }
    }
    dfs_add(r, -1, 0, -1);
    deleted[r] = true;
    for (int child : g[r]) {
        if (!deleted[child]) {
            recurse(child);
        }
    }
}

int main() {
    cin >> n >> k1 >> k2;

    for (int i = 1; i <= n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    recurse(1);
    cout << answer << '\n';
}
```

## Solution 2: Small-To-Large Merging

There is another, simpler solution to this problem. It uses a technique known as
*small-to-large merging* combined with *policy-based* data structures.

*Policy-based* data structures are not part of the C++ standard, rather they are
built-in to the GNU compiler. The policy-based balanced binary tree allows us to
query the number of elements in a range using the function `order_of_key`.

After rooting the tree, we make a depth-first traversal of it. During the
traversal, we calculate the number of paths with a length
between $k\_1$ and $k\_2$ whose highest node is the current one.

With small-to-large merging, it can be proven that each element will be moved at
most $O(\log n)$ times making the total time complexity of the solution
$O(n\log^2n)$.

Note that a policy-based tree only supports unique values. We can get around
this by storing the depths in `pair`s with the node index as the second element.

```cpp
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

template <typename T>
using indexed_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

int query_range(indexed_set<pair<int, int>> &tree, int l, int r) {
    return tree.order_of_key({r + 1, 0}) - tree.order_of_key({l, 0});
}

const int N = 200001;
int n, k1, k2;
vector<int> g[N];
ll answer;

indexed_set<pair<int, int>> dfs(int node, int parent, int depth) {
    indexed_set<pair<int, int>> dist;
    dist.insert({depth, node});
    for (int child : g[node]) {
        if (child == parent) continue;
        auto child_dist = dfs(child, node, depth + 1);
        if (child_dist.size() > dist.size()) {
            dist.swap(child_dist);
        }
        for (auto [d, s] : child_dist) {
            answer += query_range(dist, k1 - d + 2 * depth, k2 - d + 2 * depth);
        }
        for (auto p : child_dist) dist.insert(p);
    }
    return dist;
}

int main() {
    cin >> n >> k1 >> k2;

    for (int i = 1; i <= n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    dfs(1, -1, 0);
    cout << answer << '\n';
}
```

## Solution 3: Improved merge

Instead of using a policy-based tree to store information about the depths of
the nodes, we may use a `deque`. If each position of the deque corresponds to a
depth, we are only able to query the amount of nodes at a specific depth. To
query the number of nodes with a depth between $k\_1$ and $k\_2$, we may store
suffix sums to the deque. That way, each position corresponds to the amount of
nodes with a depth larger or equal to the index of the position.

We use small-to-large merging but as the sizes of merged data structures
correspond to the depth of the subtrees, rather than to the sizes, the solution
runs in $O(n)$ time.

```cpp
#include <deque>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

const int N = 200001;
int n, k1, k2;
vector<int> g[N];
ll answer;

void merge(deque<int> &a, deque<int> &b) {
    if (b.size() > a.size()) swap(a, b);
    auto get = [&](int i) {
        if (i < 0) return a.front();
        if (i >= a.size()) return 0;
        return a[i];
    };
    int bs = b.size();
    b.push_back(0);
    for (int i = 0; i < bs; ++i) {
        ll cur_b = b[i] - b[i + 1];
        answer += cur_b * (get(k1 - i) - get(k2 - i + 1));
    }
    for (int i = 0; i < bs; ++i) {
        a[i] += b[i];
    }
}

deque<int> dfs(int node, int parent) {
    deque<int> ret{1};
    for (int child : g[node]) {
        if (child == parent) continue;
        auto child_depths = dfs(child, node);
        child_depths.push_front(child_depths.front());
        merge(ret, child_depths);
    }
    return ret;
}

int main() {
    cin >> n >> k1 >> k2;

    for (int i = 1; i <= n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    dfs(1, -1);
    cout << answer << '\n';
}
```