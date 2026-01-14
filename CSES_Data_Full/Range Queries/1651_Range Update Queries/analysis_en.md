# 1651 - Range Update Queries

There are range updates operations in this problem.
A regular segment tree cannot handle them.
A more powerful data structre like
*a Lazy Propagation Segment Tree*
could be used.
If we want, though, to
keep on using a regular segment tree, we have to
get a little creative.

## First approach: Difference array

A shift in perspective makes solving this problem
easier. We should not think of our array conventionally.
Rather, we should operate on an array where each element
represents the difference between subsequent elements
in the original array. The $i$-th element of the original
array is represented by the sum
of the values in the first $i$ positions, i.e.
positions $1\ldots i$, in the new array.

At first, we initialize the array with zeros.
Then, we add the original elements.
For each element, $x\_i$ we add $x\_i$ to the position $i$
and $-x\_i$ to the position $i+1$.
Now, for each $i$, the sum of positions $1\ldots i$
has the value $x\_i$.

Updates are handled in a similar manner – for any update
$a, b, u$, We add $u$ to the
position $a$ and subtract $u$ from the position $b+1$.

Because we only do point updates and query ranges, this array can be
represented with a regular segment tree or a Fenwick tree.

Done this way, it does take $O(\log n)$ time
to look up a single value but it is a drawback
we have to accept.

```cpp
#include <iostream>
using namespace std;
using ll = long long;

const int TREE_SIZE = 1 << 18;
ll tree[TREE_SIZE * 2];

void change(int i, int x) {
    i += TREE_SIZE;
    while (i) {
        tree[i] += x;
        i /= 2;
    }
}

// Returns the sum of values in range [l, r]
ll get_sum(int l, int r) {
    ll res = 0;
    l += TREE_SIZE;
    r += TREE_SIZE;
    while (l <= r) {
        if (l % 2 == 1) res += tree[l++];
        if (r % 2 == 0) res += tree[r--];
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
        change(i + 1, -x);
    }

    for (int qi = 0; qi < q; ++qi) {
        int t;
        cin >> t;
        if (t == 1) {
            int l, r, u;
            cin >> l >> r >> u;
            change(l, u);
            change(r + 1, -u);
        } else {
            int k;
            cin >> k;
            cout << get_sum(1, k) << '\n';
        }
    }
}
```

## Second approach: Modified segment tree

Let us take a closer look at how the segment
tree works.

The following function finds the sum of the values
corresponding to the positions $[l,r]$.
It does this by finding the minimum number of nodes that correspond
to non-overlapping ranges which cover the whole range of the query.

```cpp
ll query(int l, int r) {
    ll ret = 0;
    l += tree_size;
    r += size_size;
    while (l <= r) {
        if (l % 2 == 1) ret += tree[l++];
        if (r % 2 == 0) ret += tree[r--];
        l /= 2;
        r /= 2;
    }
    return ret;
}
```

The following picture depicts one example of a query and
the nodes used to answer the query.

![](879551a5b0a78c9bb90b10134245a5487d9f5ae3fb42aa9bc8abc029c89157ac)

The following function changes a single value in the array.
It also changes all nodes on the path from the array element to the
root. That is, the nodes that correspond to the ranges of which
the index is a part of.

```cpp
void change(int i, int d) {
    i += tree_size;
    while (i > 0) {
        tree[i] += d;
        i /= 2;
    }
}
```

An example of a change operation. All of the nodes on the path to root
are selected.

![](3d604ec96dd9d81bbf21ab0931ceab113a347b72262aee16627fb775255d28e9)

What if we swapped the roles of these functions? Could we use the current
method of answering queries (selecting the smallest amount of nodes that cover a
given range) for modifying ranges and use the method for updating single values
for querying single values? Turns out that it is possible.

The $\texttt{change}$ function will look like this:

```cpp
void change(int l, int r, int d) {
    l += tree_size;
    r += tree_size;
    while (l <= r) {
        if (l % 2 == 1) tree[l++] += d;
        if (r % 2 == 0) tree[r--] += d;
        l /= 2;
        r /= 2;
    }
}
```

Note that, in our new representation, in order to find out an individual value,
one has to sum up the value of each node on the path from the index to the root.

```cpp
ll query(int i) {
    ll ans = 0;
    i += tree_size;
    while (i > 0) {
        ans += tree[i];
        i /= 2;
    }
    return ans;
}
```

The complete implementation of this can be find below. It is a bit challenging
to come up with this solution and it requires a deep understanding of the ideas
around segment trees. However, the completed implementation is quite short.

```cpp
#include <iostream>
using namespace std;
using ll = long long;

const int TREE_SIZE = 1 << 18;
ll tree[TREE_SIZE * 2];

ll query(int i) {
    ll ans = 0;
    i += TREE_SIZE;
    while (i > 0) {
        ans += tree[i];
        i /= 2;
    }
    return ans;
}

void change(int l, int r, int d) {
    l += TREE_SIZE;
    r += TREE_SIZE;
    while (l <= r) {
        if (l % 2 == 1) tree[l++] += d;
        if (r % 2 == 0) tree[r--] += d;
        l /= 2;
        r /= 2;
    }
}

int main() {
    int n, q;
    cin >> n >> q;

    for (int i = 1; i <= n; ++i) {
        int x;
        cin >> x;
        change(i, i, x);
    }

    for (int qi = 0; qi < q; ++qi) {
        int t;
        cin >> t;
        if (t == 1) {
            int l, r, u;
            cin >> l >> r >> u;
            change(l, r, u);
        } else {
            int k;
            cin >> k;
            cout << query(k) << '\n';
        }
    }
}
```