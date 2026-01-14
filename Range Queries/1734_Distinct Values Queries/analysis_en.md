# 1734 - Distinct Values Queries

## First approach: Segment tree

This problem can be solved using a segment tree.
Note that we can answer the queries offline,
which means that we can change the order in which we answer them.

We process the queries in increasing order of their starting points.
At each point, we answer all queries that begin at that point.

We always want to have only one occurrence
of each distinct value in the segment tree,
and we store, for each value, the next occurrence
to the right of our pointer.

It is guaranteed that if
any occurrence of a value is
in the query range then
the leftmost occurrence is also
in the query range.
Thus, each distinct value in the query range
is counted exactly once
which is precisely what we want.

The time complexity of this implementation
is $O(n\log n)$.

```cpp
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

const int TREE_SIZE = 1 << 18;
int tree[TREE_SIZE * 2];

void change(int k, int x) {
    k += TREE_SIZE;
    tree[k] = x;
    while (k > 1) {
        k /= 2;
        tree[k] = tree[k * 2] + tree[k * 2 + 1];
    }
}

// Returns the sum of values in range [l, r].
int query(int l, int r) {
    int ans = 0;
    l += TREE_SIZE;
    r += TREE_SIZE;
    while (l <= r) {
        if (l % 2 == 1) ans += tree[l++];
        if (r % 2 == 0) ans += tree[r--];
        l /= 2;
        r /= 2;
    }
    return ans;
}

struct Query {
    int l, r, i;
};

int main() {
    int n, q;
    cin >> n >> q;

    vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }

    // Stores occurrences of each value – in decreasing order.
    // Done this way, we can, at any time, efficiently
    // remove the smallest occurrence of any value
    // using the function `pop_back`.
    map<int, vector<int>> occurrences;
    for (int i = n - 1; i >= 0; --i) {
        occurrences[v[i]].push_back(i);
    }

    for (auto &[v, l] : occurrences) {
        change(l.back(), 1);
        l.pop_back();
    }

    vector<Query> queries(q);
    for (int i = 0; i < q; ++i) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].l--;
        queries[i].r--;
        queries[i].i = i;
    }

    sort(queries.begin(), queries.end(),
         [&](auto a, auto b) { return a.l < b.l; });

    vector<int> answer(q);

    for (int i = 0, j = 0; i < n; ++i) {
        while (j < q && queries[j].l == i) {
            answer[queries[j].i] = query(i, queries[j].r);
            ++j;
        }
        if (!occurrences[v[i]].empty()) {
            change(occurrences[v[i]].back(), 1);
            occurrences[v[i]].pop_back();
        }
    }

    for (int a : answer) {
        cout << a << ' ';
    }
    cout << '\n';
}
```

## Second approach: Mo's algorithm

Mo's algorithm is an offline
algorithm for answering range queries.
The algorithm is based on a special
ordering where queries are split in
blocks of size $B=\sqrt n$.
The query $[l\_0,r\_0]$ comes before
$[l\_1,r\_1]$ if either

* $\left\lfloor \frac{l\_0}{B}\right\rfloor<\left\lfloor \frac{l\_1}{B}\right\rfloor$
* $\left\lfloor \frac{l\_0}{B}\right\rfloor=\left\lfloor \frac{l\_1}{B}\right\rfloor$ and $r\_0< r\_1$.

We maintain an active range with two pointers.
These pointers are moved, one step at a time,
from one query to the next.

The left pointer moves $O(n)$ times $O(\sqrt n)$
steps
and
the right pointer moves $O(\sqrt n)$ times $O(n)$
steps.

Thus, the total time complexity of this algorithm
is
$$O(n\cdot f(n)\sqrt n)$$
where
$f(n)$ represents the cost of moving a pointer.

An implementation of Mo's algorithm can be found below. Unfortunately, this
solution is too slow.

As moving a pointer changes
a value inside a `map`, it takes
$O(\log n)$ time and
the total time complexity of the
implementation is
$O(n \sqrt{n} \log{n})$
if we assume that there
are $n$ queries. This translates
to roughly $1.57\cdot 10^9$
operations with a large constant factor.

```cpp
#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

// Set block size equal to sqrt(N).
const int B = (int)sqrt(2e5);

struct Query {
    int l, r, i;
};

int main() {
    int n, q;
    cin >> n >> q;

    vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }

    vector<Query> queries(q);
    for (int i = 0; i < q; ++i) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].l--;
        queries[i].r--;
        queries[i].i = i;
    }

    sort(queries.begin(), queries.end(), [&](auto a, auto b) {
        if (a.l / B != b.l / B) {
            return a.l / B < b.l / B;
        }
        return a.r < b.r;
    });

    vector<int> answer(q);

    map<int, int> s;

    auto add = [&](int i) {
        s[v[i]]++;
    };

    auto remove = [&](int i) {
        auto it = s.find(v[i]);
        it->second--;
        if (it->second == 0) {
            s.erase(it);
        }
    };

    int al = 0, ar = 0;
    add(0);

    for (auto [l, r, i] : queries) {
        while (ar < r) add(++ar);
        while (al > l) add(--al);
        while (al < l) remove(al++);
        while (ar > r) remove(ar--);
        answer[i] = (int)s.size();
    }

    for (int a : answer) {
        cout << a << ' ';
    }
    cout << '\n';
}
```

Fortunately, there is an easy fix: coordinate compression.
When we translate the numbers from the range $[1,10^9]$
to the range $[0,n-1]$, we do not need a `map` anymore.
Instead, we can use an array to count the number
of each value.
This new implementation has a time complexity
of $O(n\sqrt n)$ which easily fits
in the time limit.

```cpp
#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

// Set block size equal to sqrt(N).
const int B = (int)sqrt(2e5);

struct Query {
    int l, r, i;
};

int main() {
    int n, q;
    cin >> n >> q;

    vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }

    auto values = v;
    sort(values.begin(), values.end());

    for (int &x : v) {
        x = lower_bound(values.begin(), values.end(), x) - values.begin();
    }

    vector<Query> queries(q);
    for (int i = 0; i < q; ++i) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].l--;
        queries[i].r--;
        queries[i].i = i;
    }

    sort(queries.begin(), queries.end(), [&](auto a, auto b) {
        if (a.l / B != b.l / B) {
            return a.l / B < b.l / B;
        }
        return a.r < b.r;
    });

    int distinct = 0;
    vector<int> occurrences(n);
    vector<int> answer(q);

    auto add = [&](int i) {
        if (occurrences[v[i]]++ == 0) {
            distinct++;
        }
    };

    auto remove = [&](int i) {
        if (--occurrences[v[i]] == 0) {
            distinct--;
        }
    };

    int al = 0, ar = 0;
    add(0);

    for (auto [l, r, i] : queries) {
        while (ar < r) add(++ar);
        while (al > l) add(--al);
        while (al < l) remove(al++);
        while (ar > r) remove(ar--);
        answer[i] = distinct;
    }

    for (int a : answer) {
        cout << a << ' ';
    }
    cout << '\n';
}
```

### References for Mo's algorithm

* [CP-Algorithms, Sqrt Decomposition](https://cp-algorithms.com/data_structures/sqrt_decomposition.html#toc-tgt-4), Mo's algorithm
* [Codeforces, *Mo's Algorithm* by kAc](https://codeforces.com/blog/entry/7383)
* [CPHB (Competitive Programmer's Handbook)](http://cses.fi/book), Chapter 27, Mo's algorithm