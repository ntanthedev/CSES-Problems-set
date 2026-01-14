# 1137 - Subtree Queries

Let us construct an *Euler tour* of it. Each subtree corresponds to a
contiguous range in the tour which means that we can answer queries efficiently
with a segment tree.

```cpp
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

const int N = 200001;
int v[N];
vector<int> g[N];
int tour_in[N], tour_out[N], tour_index;

void dfs(int node, int parent) {
    tour_in[node] = ++tour_index;
    for (int child : g[node]) {
        if (child == parent) continue;
        dfs(child, node);
    }
    tour_out[node] = tour_index;
}

const int TREE_SIZE = 1 << 18;
ll tree[TREE_SIZE * 2];

// Changes the value in position k to x.
void change(int k, int x) {
    k += TREE_SIZE;
    tree[k] = x;
    while (k > 1) {
        k /= 2;
        tree[k] = tree[2 * k] + tree[2 * k + 1];
    }
}

// Returns the sum of values in range [l, r].
ll query(int l, int r) {
    l += TREE_SIZE;
    r += TREE_SIZE;
    ll sum = 0;
    while (l <= r) {
        if (l % 2 == 1) sum += tree[l++];
        if (r % 2 == 0) sum += tree[r--];
        l /= 2;
        r /= 2;
    }
    return sum;
}

int main() {
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> v[i];
    }
    for (int i = 1; i <= n - 1; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfs(1, -1);
    for (int i = 1; i <= n; i++) {
        change(tour_in[i], v[i]);
    }
    for (int i = 1; i <= q; i++) {
        int t, s;
        cin >> t >> s;
        if (t == 1) {
            int x;
            cin >> x;
            change(tour_in[s], x);
        } else {
            cout << query(tour_in[s], tour_out[s]) << '\n';
        }
    }
}
```

### Resources for Euler tour technique

* [CP-Algorithms, *Lowest Common Ancestor*](https://cp-algorithms.com/graph/lca.html)
* [CPHB (Competitive Programmer's Handbook)](http://cses.fi/book), Chapter 18