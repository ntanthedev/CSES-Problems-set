# 2166 - Prefix Sum Queries

A simple sum/max segment tree will not suffice for this problem.
We need to store additional information in the nodes.

For each node, we will store the sum of the values in the range
corresponding to that node and also the maximum prefix sum of those values.

A regular query function will not work because we have to keep track
of the prefix sum. For this purpose, two variables are used:

1. $\texttt{prefix\\_sum}$, this variable will be used by the left pointer which
   will accumulate a prefix sum from the left. It will hold the
   sum of values from the beginning of the query range to the beginning of the current node.
2. $\texttt{subfix\\_sum}$, this variable will be used by the right pointer.
   We cannot accumulate the sum as we go
   because the right pointer starts from the very end of the query range.
   Thus, the sum needs to be calculated beforehand and
   the right pointer will subtract from it as it moves up in the tree.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

const int TREE_SIZE = 1 << 18;
struct Node {
    ll sum;
    ll max_prefix;
} tree[TREE_SIZE * 2];

Node merge(Node l, Node r) {
    return {l.sum + r.sum, max(l.max_prefix, l.sum + r.max_prefix)};
}

void change(int i, int x) {
    i += TREE_SIZE;
    tree[i] = {x, x};
    while (i > 1) {
        i /= 2;
        tree[i] = merge(tree[i * 2], tree[i * 2 + 1]);
    }
}

// Returns the sum of the value in range [l, r]
ll query_sum(int l, int r) {
    ll sum = 0;
    l += TREE_SIZE;
    r += TREE_SIZE;
    while (l <= r) {
        if (l % 2 == 1) sum += tree[l++].sum;
        if (r % 2 == 0) sum += tree[r--].sum;
        l /= 2;
        r /= 2;
    }
    return sum;
}

// Returns the maximum prefix sum in range [l, r]
ll query(int l, int r) {
    ll prefix_sum = 0;
    ll subfix_sum = query_sum(l, r);
    ll res = 0;
    l += TREE_SIZE;
    r += TREE_SIZE;
    while (l <= r) {
        if (l % 2 == 1) {
            res = max(res, prefix_sum + tree[l].max_prefix);
            prefix_sum += tree[l].sum;
            l++;
        }
        if (r % 2 == 0) {
            subfix_sum -= tree[r].sum;
            res = max(res, subfix_sum + tree[r].max_prefix);
            r--;
        }
        l /= 2;
        r /= 2;
    }
    return res;
}

int main() {
    int n, q;
    cin >> n >> q;

    for (int i = 1; i <= n; ++i) {
        int x;
        cin >> x;
        change(i, x);
    }

    for (int qi = 0; qi < q; ++qi) {
        int t;
        cin >> t;
        if (t == 1) {
            int k, u;
            cin >> k >> u;
            change(k, u);
        } else {
            int l, r;
            cin >> l >> r;
            cout << query(l, r) << '\n';
        }
    }
}
```