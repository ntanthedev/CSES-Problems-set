# 2080 - Fixed Length Paths I

## Solution 1: Centroid Decomposition

This problem can be solved with a technique known as centroid decomposition.

The idea is to recursively split the tree into disjoint trees. We start by
selecting a node from the tree. Then, we calculate the number of paths of length
$k$ which go through the selected node. After this, all unaccounted paths are
completely contained in the subtrees of the node. Thus, we may remove the
selected node and repeat the same procedure for the resulting new trees.

The solution would be too slow if we each time selected the node at random. The
key idea is to pick the node so that it is a centroid of the tree, i.e., a node
such that when it is appointed the root of the tree, each subtree has at most
$\lfloor n/2 \rfloor$ nodes.

If we choose a centroid node, the sizes of the resulting trees will be at most
half of the original size. This means that each node will be part of at most
$O(\log n)$ trees. As every node of every tree is processed once, the total time
complexity of the solution is $O(n\log n)$.

At each step, a centroid node can be found with a greedy algorithm, which works
as follows: root the tree, traverse recursively from the root, each time choosing
a child with a subtree size of at least $\lfloor n/2 \rfloor$. If there is no
such child, the traversal has arrived at a centroid node.

When we have found a centroid, we can start counting the paths. For this
purpose, we use an array `dist`. Each position $i$ of `dist` stores the amount
of nodes at distance $i$ from the centroid. To ensure that the counted paths are
not contained solely in a single subtree and that each path is only counted
once, we count the number of paths ending in a subtree before updating the array
`dist` with the distances of the nodes in the subtree.

The `dist` array is reused for all of the individually processed trees. So, we
have to reset it between the recursive calls.

```cpp
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

const int N = 200001;
bool deleted[N];
int n, k, sizes[N];
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

int dist[N];

void dfs_add(int node, int parent, int depth, int change) {
    dist[depth] += change;
    for (int child : g[node]) {
        if (child == parent || deleted[child]) continue;
        dfs_add(child, node, depth + 1, change);
    }
}

void dfs_query(int node, int parent, int depth) {
    if (k - depth >= 0) answer += dist[k - depth];
    for (int child : g[node]) {
        if (child == parent || deleted[child]) continue;
        dfs_query(child, node, depth + 1);
    }
}

void recurse(int node) {
    dfs_sizes(node, -1);
    int r = find_centroid(node, -1, sizes[node]);
    dist[0] = 1;
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
    cin >> n >> k;

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

There is another, simpler solution to this problem. It uses a technique
sometimes known as *small-to-large merging*. The implementation has only one
tree traversal.

After rooting the tree, we make a depth-first traversal of it. During the
traversal, we calculate the number of paths through each node. Any path in a
tree has a highest node: a node that is the closest to the root. We will
calculate each path only once, at its highest node.

To make sure we only count paths of length $k$, we use the fact that the
distance between tree nodes $a$ and $b$ equals

$$\textrm{depth}(a)+\textrm{depth}(b)-2\cdot\textrm{depth}(c),$$

where $c$ is the highest node on the path between $a$ and $b$, also known as the
lowest common ancestor of $a$ and $b$. With this, finding the number of paths of
length $k$ through node $x$ corresponds to finding the number of ways to pick
two nodes $a$ and $b$ from different subtrees of $x$ with the following
condition:

$$\textrm{depth}(a)+\textrm{depth}(b)-2\cdot\textrm{depth}(x)=k.$$

We create a `map` for each node, which stores the depths of the nodes in the
subtree of the node. We use the technique of *small-to-large* merging for
merging a node's `map` to its parent's `map` efficiently: if a map of a child is
larger than the map of its parent, we swap the data structures before
merging. This means that instead of moving elements from the map of the child to
the map of its parent, we move them from the smaller map to the larger map.

It can be proven that each element will be moved at most $O(\log n)$ times
making the total time complexity of the solution $O(n\log^2n)$.

```cpp
#include <iostream>
#include <map>
#include <vector>
using namespace std;
using ll = long long;

const int N = 200001;
int n, k;
vector<int> g[N];
ll answer;

map<int, int> dfs(int node, int parent, int depth) {
    map<int, int> dist;
    dist[depth] = 1;
    for (int child : g[node]) {
        if (child == parent) continue;
        auto child_dist = dfs(child, node, depth + 1);
        if (child_dist.size() > dist.size()) {
            swap(dist, child_dist);
        }
        for (auto [d, amt] : child_dist) {
            answer += 1ll * dist[k - d + 2 * depth] * amt;
        }
        for (auto [d, amt] : child_dist) {
            dist[d] += amt;
        }
    }
    return dist;
}

int main() {
    cin >> n >> k;

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

Instead of using a `map` to store information about the depths of the nodes in
each subtree, we use a `deque`. Other than that, this solution works in a way
that is very similar to the previous solution.

Note that, in contrast to the previous solution, the `deque` indexes represent
depths relative to the current node, as opposed to relative to the root node.
Also note that the size of the merged data structure is proportional to the
depth of the node, instead of the subtree size of the node.

It may come as a surprise that this solution runs in $O(n)$ time.

This proof was first [presented](https://codeforces.com/blog/entry/70822) by
Codeforces user [neal](https://codeforces.com/profile/neal).

The time complexity of constructing the `deque`s is linear because each
insertion works in $O(1)$ time and each node corresponds to at most two
insertions. Thus, we need to focus only on the `merge` function.

A `merge` operation results in a `deque` with a size equal to the size of the
larger of the merged `deque`s, as opposed to the sum of the two sizes. Thus,
the smaller `deque` is "consumed" and its elements will not amount to any more
work. As there are only $O(n)$ `deque` elements in total and each of them is
consumed at most once, the total time complexity is linear.

```cpp
#include <deque>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

const int N = 200001;
int n, k;
vector<int> g[N];
ll answer;

void merge(deque<int> &a, deque<int> &b) {
    if (b.size() > a.size()) swap(a, b);
    int bs = b.size();
    for (int i = 0; i < bs; ++i) {
        if (0 <= k - i && k - i < (int)a.size()) {
            answer += b[i] * a[k - i];
        }
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
        child_depths.push_front(0);
        merge(ret, child_depths);
    }
    return ret;
}

int main() {
    cin >> n >> k;

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