# 1647 - Static Range Minimum Queries

## First approach: Segment tree

As there is no inverse operation for the minimum, a static array will not suffice.
However, a segment tree handles the dynamic queries with ease.

```cpp
#include <iostream>
using namespace std;

const int TREE_SIZE = 1 << 18;
int tree[TREE_SIZE * 2];

void change(int i, int x) {
    i += TREE_SIZE;
    tree[i] = x;
    while (i > 1) {
        i /= 2;
        tree[i] = min(tree[i * 2], tree[i * 2 + 1]);
    }
}

// Returns the minimum value in range [l, r]
int get_min(int l, int r) {
    int res = (int)1e9;
    l += TREE_SIZE;
    r += TREE_SIZE;
    while (l <= r) {
        if (l % 2 == 1) res = min(res, tree[l++]);
        if (r % 2 == 0) res = min(res, tree[r--]);
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
        int l, r;
        cin >> l >> r;
        cout << get_min(l, r) << '\n';
    }
}
```

### Additional resources for segment trees

* [CPHB (Competitive Programmer's Handbook)](http://cses.fi/book), Chapter 9
* [CP-Algorithms, Segment Tree](https://cp-algorithms.com/data_structures/segment_tree.html)

## Second approach: Sparse table

Another way to solve this problem is using a sparse table.
The sparse table is a data structure capable of answering queries
in $O(1)$ time. The construction of the table takes
$O(n \log n)$ time.

Note that, in contrast
to the segment tree, the sparse table
is built once and cannot be changed afterward.

```cpp
#include <iostream>
using namespace std;

const int N = 200000;
const int L = 20;

int x[N];
int table[N][L];

// Returns the minimum value in range [l, r)
int get_min(int l, int r) {
    // __lg(x) returns the base-2 logarithm of x, rounded down.
    // With it, we'll figure out the largest power of two
    // that is not larger than the length of the query.
    int i = __lg(r - l);
    return min(table[l][i], table[r - (1 << i)][i]);
}

int main() {
    int n, q;
    cin >> n >> q;

    for (int i = 0; i < n; ++i) {
        cin >> x[i];
        table[i][0] = x[i];
    }

    for (int j = 0; (1 << j) < n; ++j) {
        for (int i = 0; i + (1 << j) < n; ++i) {
            table[i][j + 1] = min(table[i][j], table[i + (1 << j)][j]);
        }
    }

    for (int qi = 0; qi < q; ++qi) {
        int l, r;
        cin >> l >> r;
        l--;
        cout << get_min(l, r) << '\n';
    }
}
```

### Additional resources for sparse table

* [CPHB (Competitive Programmer's Handbook)](http://cses.fi/book), Chapter 9
* [CP-Algorithms, Sparse Table](https://cp-algorithms.com/data_structures/sparse-table.html)