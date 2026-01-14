# 2416 - Increasing Array Queries

There are many approaches to this problem. Let us first analyze the situation
before discussing any specific approach.

One important question is "When do we need to increase an element?" Let an
element of the array be *special* if it is larger than the value following it.
Only *special* elements can cause other elements to increase. Each smaller value
after a *special* element will be increased to match the *special* element's
size.

The picture following illustrates the idea – the heights of the towers
represents the sizes of the array elements and the red squares are added using
the operation.

![](33a248716f823b63b45b3188e958889a25f20f08c4139bd4fd6762b00273e156)

## First approach: Lazy segment tree

This is an offline approach as we answer the queries in the order of their
starting index. We will go through the array in reverse order and keep track of
the amount of increase each element needs. This way we can answer a query with a
sum query in a lazy segment tree.

To each position in the tree, we will store the amount the element in this
position will need to be increased, in other words, the increased value
subtracted by the initial value.

To figure out the amount of increase each element needs we will use a stack of
increasing values. For each element, we will remove all values smaller than it
from the stack. Note that all of the values in the stack are *special*
elements. The topmost element in the stack will be the next larger value and
all of the values before it will need to be increased which can be done by
adding the current value to the corresponding range in the tree.

We will use segment tree operations either when we remove an element from the
stack or when we answer a query. Each index can be removed from the stack at
most once – in other words, the number of removed items is $O(n)$.
Further, each segment tree operation will take $O(\log n)$ time. Thus,
the total time complexity of the solution is $O((n+q)\log n)$.

```cpp
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

// Lazy propagation segment tree.
// Supports the following operations:
//  1. `add`: add x to every element in range [l, r)
//  2. `query`: find the sum of values in range [l, r)
struct Tree {
    int n;
    vector<ll> tree;
    vector<ll> lazy;

    Tree(int n) : n(n), tree(n * 4), lazy(n * 4) {}

    void add(int s, int l, int r, int ql, int qr, ll x) {
        if (r <= ql || qr <= l) return;
        if (ql <= l && r <= qr) return apply(s, r - l, x);
        push(s, r - l);
        int m = (l + r) / 2;
        add(s * 2 + 0, l, m, ql, qr, x);
        add(s * 2 + 1, m, r, ql, qr, x);
        pull(s);
    }

    ll query(int s, int l, int r, int ql, int qr) {
        if (r <= ql || qr <= l) return 0;
        if (ql <= l && r <= qr) return tree[s];
        push(s, r - l);
        int m = (l + r) / 2;
        return query(s * 2, l, m, ql, qr) + query(s * 2 + 1, m, r, ql, qr);
    }

    void push(int s, int length) {
        if (lazy[s]) {
            apply(s * 2 + 0, length / 2, lazy[s]);
            apply(s * 2 + 1, (length + 1) / 2, lazy[s]);
            lazy[s] = 0;
        }
    }

    void apply(int s, int length, ll x) {
        tree[s] += x * length;
        lazy[s] += x;
    }

    void pull(int s) { tree[s] = tree[s * 2] + tree[s * 2 + 1]; }
    void add(int l, int r, ll x) { add(1, 0, n, l, r, x); }
    ll query(int l, int r) { return query(1, 0, n, l, r); }
};

int main() {
    int n, q;
    cin >> n >> q;

    Tree tree(n);

    vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
        tree.add(i, i + 1, -v[i]);
    }

    vector<vector<pair<int, int>>> queries(n);
    vector<ll> ans(q);

    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        l--;
        queries[l].emplace_back(r, i);
    }

    vector<int> stack{n};

    for (int i = n - 1; i >= 0; --i) {
        while (stack.back() < n && v[stack.back()] <= v[i]) {
            int j = stack.back();
            stack.pop_back();
            tree.add(j, stack.back(), -v[j]);
        }
        tree.add(i, stack.back(), v[i]);
        stack.push_back(i);
        for (auto [r, j] : queries[i]) {
            ans[j] = tree.query(i, r);
        }
    }

    for (ll u : ans) {
        cout << u << '\n';
    }
}
```

## Second approach: Regular segment tree

The above solution can be modified to work with a regular segment tree.

When working with a regular segment tree, we will store the increase amounts to
the positions of the corresponding *special elements*. Note that the effective
range of the last *special* element in the query range can extend beyond the
query's right end. In this case, we have to subtract the surplus increase.

This approach has the same time complexity as the previous one.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

const int TREE_SIZE = 1 << 18;
ll tree[TREE_SIZE * 2];

// Adds x to position i
void add(int i, ll x) {
    i += TREE_SIZE;
    while (i > 0) {
        tree[i] += x;
        i /= 2;
    }
}

// Returns the sum of values in range [l, r)
ll query(int l, int r) {
    ll res = 0;
    l += TREE_SIZE;
    r += TREE_SIZE;
    while (l < r) {
        if (l % 2 == 1) res += tree[l++];
        if (r % 2 == 1) res += tree[--r];
        l /= 2;
        r /= 2;
    }
    return res;
}

int main() {
    int n, q;
    cin >> n >> q;

    vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
        add(i, -v[i]);
    }

    vector<vector<pair<int, int>>> queries(n);
    vector<ll> ans(q);

    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        l--;
        queries[l].emplace_back(r, i);
    }

    vector<pair<int, int>> stack{{n, 0}};

    for (int i = n - 1; i >= 0; --i) {
        while (stack.back().first < n && v[stack.back().first] <= v[i]) {
            auto [j, len] = stack.back();
            stack.pop_back();
            add(j, -ll(len) * v[j]);
        }
        add(i, ll(stack.back().first - i) * v[i]);
        stack.emplace_back(i, stack.back().first - i);
        for (auto [r, j] : queries[i]) {
            auto iter = lower_bound(stack.rbegin(), stack.rend(), pair{r, 0});
            auto [it, len] = *prev(iter);
            ans[j] = query(i, r) - ll(len - (r - it)) * v[it];
        }
    }

    for (ll u : ans) {
        cout << u << '\n';
    }
}
```

## Third approach: Sparse table

There is a simple solution that uses a sparse table. We will, for each element,
store a pointer to the next larger element. Later, a sparse table will be built
for repeatedly following the pointers efficiently.

The amount of increase needed to make the range from the position $i$ to the
position $j$ of the next larger element non-decreasing is calculated with the
formula $(j-i)\cdot x\_i-\sum\_{i\le k < j}a\_k$. The formula represents the
difference between the increased values and the initial values.

Note that, also in this solution, the final jump might exceed the query range.
In this case, we know that each remaining element in the range will have the
same value – as they are smaller than our current value. Thus we can calculate
the amount of increase needed for these elements separately.

Building the sparse table takes $O(n\log n)$ time and answering a
single query takes $O(\log n)$ time. Thus, the total time complexity
is $O((n+q)\log n)$.

```cpp
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const int INF = 1e9;

const int N = 200001;
const int L = 19;
int jump[L][N];
ll cost[L][N];

int main() {
    int n, q;
    cin >> n >> q;

    vector<int> a(n + 1);
    vector<ll> prefix_sum(n + 1);

    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        prefix_sum[i + 1] = prefix_sum[i] + a[i];
    }

    a[n] = INF;
    jump[0][n] = n;

    vector<int> stack{n};

    for (int i = n - 1; i >= 0; --i) {
        while (a[stack.back()] <= a[i]) {
            stack.pop_back();
        }

        int j = stack.back();
        jump[0][i] = j;
        cost[0][i] = ll(j - i) * a[i];
        stack.push_back(i);
    }

    for (int j = 0; j < L - 1; ++j) {
        for (int i = 0; i <= n; ++i) {
            cost[j + 1][i] = cost[j][i] + cost[j][jump[j][i]];
            jump[j + 1][i] = jump[j][jump[j][i]];
        }
    }

    for (int qi = 0; qi < q; ++qi) {
        int l, r;
        cin >> l >> r;
        l--;
        ll ans = -(prefix_sum[r] - prefix_sum[l]);

        for (int j = L - 1; j >= 0; --j) {
            if (jump[j][l] < r) {
                ans += cost[j][l];
                l = jump[j][l];
            }
        }

        ans += ll(r - l) * a[l];

        cout << ans << '\n';
    }
}
```