# 1736 - Polynomial Queries

This problem can be solved with a *lazy segment tree*.

Let us focus on a more general version of the problem, one where any arithmetic
progression may be added.

Any arithmetic progression $a,a+d,a+2d,\dots$ can be identified with two numbers
$a$ and $d$, the first element of the sequence and the difference between
subsequent elements.

How can one calculate the sum of the first $n$ elements in an arithmetic
progression? Firstly, notice that $a$ is repeated in each term. Thus we may take
the sum $n\cdot a$ and focus on the sequence $0,d,2d,\dots,(n-1)d$.

Recall the well-known sum formula

$$0+1+2+\dots+(n-1)=\frac{n(n-1)}{2}.$$

From the above formula we can derive

$$0+d+2d+\dots+d(n-1)=d\frac{n(n-1)}{2}.$$

In conclusion, the sum of the first $n$ elements in any arithmetic progression
$a,a+d,a+2d,\dots$ is equal to

$$na+d\frac{n(n-1)}{2}.$$

This can be implemented using three arrays for the segment tree:

1. `sum` stores the sum of the values in the range of each node
2. `lazy_a` stores the starting value of the sequence that needs to be added to
   the elements in the range of the node
3. `lazy_d` stores the difference between subsequent elements in the sequence
   that needs to be added to the elements in the range of the node

In other words, the values $a$ and $d$, of `lazy_a` and `lazy_d` respectively,
correspond to the sequence

$$a,a+d,a+2d,\dots$$

The *lazy* values only apply to the children of a node – the change is already
accounted for in the sum of the corresponding node.

When we push an arithmetic progression into the two children of a node in the
segment tree, the sequence of the right child will start from the value
$a+d\cdot\textrm{length}$, where $\mathrm{length}$ is the size of the range
corresponding to the left child.

```cpp
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

// This lazy segment tree implementation supports the following operations:
//  1. add(l, r, x): in range [l, r), add x + 0 to the first element,
//                                        x + 1 to the second,
//                                        x + 2 to the third and so on
//  3. query(l, r): find the sum of values in range [l, r)
struct Tree {
    int n;
    vector<ll> sum;
    vector<ll> lazy_a;
    vector<ll> lazy_d;

    Tree(int n) : n(n), sum(n * 4), lazy_a(n * 4), lazy_d(n * 4) {}

    void add(int s, int l, int r, int ql, int qr, int x) {
        if (r <= ql || qr <= l) return;
        if (ql <= l && r <= qr) {
            apply(s, r - l, x + (l - ql), 1);
            return;
        }
        push(s, r - l);
        int m = (l + r) / 2;
        add(s * 2 + 0, l, m, ql, qr, x);
        add(s * 2 + 1, m, r, ql, qr, x);
        sum[s] = sum[s * 2] + sum[s * 2 + 1];
    }

    ll query(int s, int l, int r, int ql, int qr) {
        if (r <= ql || qr <= l) return 0;
        if (ql <= l && r <= qr) return sum[s];
        push(s, r - l);
        int m = (l + r) / 2;
        return query(s * 2, l, m, ql, qr) + query(s * 2 + 1, m, r, ql, qr);
    }

    void push(int s, int len) {
        apply(s * 2 + 0, len / 2, lazy_a[s], lazy_d[s]);
        apply(s * 2 + 1, (len + 1) / 2, lazy_a[s] + len / 2 * lazy_d[s],
              lazy_d[s]);
        lazy_a[s] = 0;
        lazy_d[s] = 0;
    }

    void apply(int s, int len, ll a, ll d) {
        sum[s] += a * len + d * ll(len - 1) * len / 2;
        lazy_a[s] += a;
        lazy_d[s] += d;
    }

    void add(int l, int r, int x) { add(1, 0, n, l, r, x); }
    ll query(int l, int r) { return query(1, 0, n, l, r); }
};

int main() {
    int n, q;
    cin >> n >> q;

    Tree tree(n);

    for (int i = 0; i < n; ++i) {
        int t;
        cin >> t;
        tree.add(i, i + 1, t);
    }

    for (int qi = 0; qi < q; ++qi) {
        int t, l, r;
        cin >> t >> l >> r;
        l--;
        if (t == 1) {
            tree.add(l, r, 1);
        } else {
            cout << tree.query(l, r) << '\n';
        }
    }
}
```

## References

* [CPHB (Competitive Programmer's Handbook)](http://cses.fi/book), Chapter 28
* [CP-Algorithms, Segment
  Tree](https://cp-algorithms.com/data_structures/segment_tree.html)