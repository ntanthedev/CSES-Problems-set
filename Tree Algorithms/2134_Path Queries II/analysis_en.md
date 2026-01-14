# 2134 - Path Queries II

This problem can be solved with a technique known as *heavy-light
decomposition*.

We will call, for each node, the child with the largest (by size) subtree a
*heavy child*. Every other child is a *light child*.

*Heavy* and *light* children will partition the tree into paths. A path consists
of repeated *heavy* nodes. For each node, let us store a pointer that points to
the end of the path the node belongs to.

![](908b4d6363d0991d77d3aaf11c5cdd885c6b0e170ebcf43c71565825f69b5f8f)

The key observation here is that the path from any node to the root will consist
of $O(\log n)$ of these *heavy* paths. This, in itself, does not seem like a
powerful technique. We need a few more observations.

We will move the *heavy* child the first place in the adjacency list for each
node. After this, we will make a depth-first search and store the nodes – in the
order they are visited – to an array. Any heavy child will follow its parent in
the DFS array. Furthermore, each heavy path corresponds to a contiguous range
in the array.

Now, how do we partition a path between two nodes into heavy paths? We can think
of this similarly to finding the lowest common ancestor of the two nodes. We
greedily move the lower of the nodes up until the two nodes meet. If we pair the
DFS array with a segment tree, we can efficiently query the maximum value during
this process. Whenever we make move a node, we will do a segment tree query.

A single query will split the path between two nodes into $O(\log n)$ parts.
Each of the $O(\log n)$ segment tree queries takes $O(\log n)$ time. Thus, the
total time complexity is $O(n+q\log^2n)$.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// This segment tree supports the following operations:
// 1. SegmentTree(v) constructs the tree from the vector v.
// 2. set(k, x) sets the value in position k to x.
// 3. query(l, r) returns the maximum value in range [l, r].
struct SegmentTree {
    int n;
    vector<int> tree;

    SegmentTree(vector<int> &v) {
        n = 1;
        while (n < v.size()) n *= 2;
        tree.resize(n * 2);
        for (int i = 0; i < v.size(); ++i) {
            tree[i + n] = v[i];
        }
        for (int i = n - 1; i > 0; --i) {
            tree[i] = max(tree[i * 2], tree[i * 2 + 1]);
        }
    }

    void set(int k, int x) {
        k += n;
        tree[k] = x;
        while (k > 1) {
            k /= 2;
            tree[k] = max(tree[k * 2], tree[k * 2 + 1]);
        }
    }

    int query(int l, int r) {
        int ans = 0;
        for (l += n, r += n; l <= r; l /= 2, r /= 2) {
            if (l % 2 == 1) ans = max(ans, tree[l++]);
            if (r % 2 == 0) ans = max(ans, tree[r--]);
        }
        return ans;
    }
};

using graph = vector<vector<int>>;

// Heavy-light decomposition.
// Decomposes the given tree into heavy and light paths.
// Provides the following functions:
// 1. `position(x)`: Returns the position of node x in the DFS order array.
// 2. `subtree(x)`: Returns range in the DFS order array that corresponds to the
//                  subtree of node x.
// 3. `path_query(a, b, f)`: Partitions the path between nodes a and b into
//                           O(log n) contiguous ranges of the DFS order array.
//                           Calls f(l, r) for each such range [l, r].
//                           The function f may, for example, query/update a
//                           segment tree.
struct HLD {
    int n;
    graph &g;
    vector<int> parent;
    vector<int> jump;
    vector<int> total;
    vector<int> order;

    HLD(graph &g) : n(g.size()), g(g), parent(n), jump(n), total(n), order(n) {
        dfs_size(0);
        int order_index = 0;
        dfs_hld(0, order_index);
    }

    template <typename F>
    void path_query(int a, int b, F f) {
        for (;; a = parent[jump[a]]) {
            if (order[a] < order[b]) swap(a, b);
            if (order[jump[a]] <= order[b]) {
                f(order[b], order[a]);
                return;
            }
            f(order[jump[a]], order[a]);
        }
    }

    int position(int x) { return order[x]; }
    pair<int, int> subtree(int x) {
        return {order[x], order[x] + total[x] - 1};
    }

private:
    void dfs_size(int node) {
        total[node] = 1;
        for (auto &child : g[node]) {
            g[child].erase(find(g[child].begin(), g[child].end(), node));
            dfs_size(child);
            total[node] += total[child];
            if (total[child] > total[g[node][0]]) {
                swap(child, g[node][0]);
            }
        }
    }

    void dfs_hld(int node, int &order_index) {
        order[node] = order_index++;
        for (auto child : g[node]) {
            parent[child] = node;
            if (child == g[node][0]) {
                jump[child] = jump[node];
            } else {
                jump[child] = child;
            }
            dfs_hld(child, order_index);
        }
    }
};

int main() {
    int n, q;
    cin >> n >> q;

    vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }

    graph g(n);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    HLD hld(g);

    vector<int> initial(n);
    for (int i = 0; i < n; ++i) {
        initial[hld.position(i)] = v[i];
    }
    SegmentTree tree(initial);

    for (int qi = 0; qi < q; ++qi) {
        int t;
        cin >> t;
        if (t == 1) {
            int s, x;
            cin >> s >> x;
            tree.set(hld.position(s - 1), x);
        } else {
            int a, b;
            cin >> a >> b;
            int ans = 0;
            auto update_ans = [&](int l, int r) {
                ans = max(ans, tree.query(l, r));
            };
            hld.path_query(a - 1, b - 1, update_ans);
            cout << ans << '\n';
        }
    }
}
```

Note that the way we implemented HLD, modifying the order of the adjacency
lists, allows us to make subtree queries in addition to path queries. Not all
implementations support this.

## References

* [Codeforces, *Easiest HLD with subtree queries* by adamant](https://codeforces.com/blog/entry/53170)
* [CP-Algorithms, Heavy-light decomposition](https://cp-algorithms.com/graph/hld.html)