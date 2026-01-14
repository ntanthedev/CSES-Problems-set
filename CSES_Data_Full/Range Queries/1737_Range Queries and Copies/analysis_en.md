# 1737 - Range Queries and Copies

This problem can be solved with a *persistent segment tree*. Persistent segment
trees allow us to query and modify historical versions of the tree.

We will make a new segment tree after each operation. The key observation here
is that only $O(\log n)$ nodes are changed per operation and the rest
of the nodes can be reused.

Each segment tree operation takes $O(\log n)$ time making the total
time complexity of the solution $O((n+q)\log n)$.

As each operation creates $O(\log n)$ nodes, the solution uses
$O(q\log n)$ memory.

```cpp
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

struct Node {
    Node *left = nullptr, *right = nullptr;
    ll sum;
};

// Builds a segment tree from vector v.
// Returns a pointer to the constructed tree.
Node *build(int l, int r, vector<int> &v) {
    Node *p = new Node();
    if (r - l == 1) {
        p->sum = v[l];
    } else {
        int m = (l + r) / 2;
        p->left = build(l, m, v);
        p->right = build(m, r, v);
        p->sum = p->left->sum + p->right->sum;
    }
    return p;
}

// Changes value in position k to x in tree p.
// Returns a pointer to the new tree.
Node *change(Node *p, int l, int r, int k, int x) {
    Node *n = new Node(*p);
    if (r - l == 1) {
        n->sum = x;
    } else {
        int m = (l + r) / 2;
        if (k < m) {
            n->left = change(p->left, l, m, k, x);
        } else {
            n->right = change(p->right, m, r, k, x);
        }
        n->sum = n->left->sum + n->right->sum;
    }
    return n;
}

// Returns the sum of values in range [ql, qr).
ll query(Node *p, int l, int r, int ql, int qr) {
    if (qr <= l || r <= ql) return 0;
    if (ql <= l && r <= qr) return p->sum;
    int m = (l + r) / 2;
    return query(p->left, l, m, ql, qr) + query(p->right, m, r, ql, qr);
}

int main() {
    int n, q;
    cin >> n >> q;

    vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }

    vector<Node *> trees{build(0, n, v)};

    for (int qi = 0; qi < q; ++qi) {
        int t, k;
        cin >> t >> k;
        k--;
        if (t == 1) {
            int a, x;
            cin >> a >> x;
            trees[k] = change(trees[k], 0, n, a - 1, x);
        } else if (t == 2) {
            int l, r;
            cin >> l >> r;
            cout << query(trees[k], 0, n, l - 1, r) << '\n';
        } else {
            trees.push_back(trees[k]);
        }
    }
}
```

## References

* [CPHB (Competitive Programmer's Handbook)](http://cses.fi/book), Chapter 28
* [CP-Algorithms, Segment Tree](https://cp-algorithms.com/data_structures/segment_tree.html)