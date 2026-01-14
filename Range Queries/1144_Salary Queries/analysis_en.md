# 1144 - Salary Queries

## First approach: Segment tree

We can use a segment tree to solve this problem.
First, though, we have to perform coordinate
compression. That is, we have to compress the
numbers from the input to a smaller range.
Only once the numbers are compressed,
can we make a segment tree.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int TREE_SIZE = 1 << 20;
int tree[TREE_SIZE * 2];

// Add x to position i.
void change(int i, int x) {
    i += TREE_SIZE;
    while (i > 0) {
        tree[i] += x;
        i /= 2;
    }
}

// Returns the sum of values in range [l, r]
int query(int l, int r) {
    int sum = 0;
    l += TREE_SIZE;
    r += TREE_SIZE;
    while (l <= r) {
        if (l % 2 == 1) sum += tree[l++];
        if (r % 2 == 0) sum += tree[r--];
        l /= 2;
        r /= 2;
    }
    return sum;
}

const int N = 200001;
int p[N];

char qt[N];
int qa[N], qb[N];

int main() {
    int n, q;
    cin >> n >> q;

    for (int i = 1; i <= n; ++i) {
        cin >> p[i];
    }

    vector<int> values(p + 1, p + 1 + n);

    for (int i = 1; i <= q; ++i) {
        cin >> qt[i] >> qa[i] >> qb[i];
        if (qt[i] == '?') {
            values.push_back(qa[i]);
            values.push_back(qb[i]);
        } else {
            values.push_back(qb[i]);
        }
    }

    sort(values.begin(), values.end());
    values.erase(unique(values.begin(), values.end()), values.end());

    // Returns the index of x in the sorted vector `values`.
    auto index = [&](int x) {
        return (int)(lower_bound(values.begin(), values.end(), x) -
                     values.begin());
    };

    for (int i = 1; i <= n; ++i) {
        change(index(p[i]), +1);
    }

    for (int i = 1; i <= q; ++i) {
        if (qt[i] == '?') {
            cout << query(index(qa[i]), index(qb[i])) << '\n';
        } else {
            change(index(p[qa[i]]), -1);
            p[qa[i]] = qb[i];
            change(index(p[qa[i]]), +1);
        }
    }
}
```

### References for segment trees

* [CPHB (Competitive Programmer's Handbook)](http://cses.fi/book), Chapter 9
* [CP-Algorithms, Segment Tree](https://cp-algorithms.com/data_structures/segment_tree.html)

## Second approach: Policy-based data structures

This problem can also be solved with so-called
policy-based data structures.
They are built into the g++ compiler –
the one on cses – but are not part of the C++
standard.

The policy-based `tree` provides a useful function:
`order_of_key` which can be used to solve this problem.
Other than that function, the tree works in almost
exactly the same way as `std::set`.

Note that the tree only stores unique values.
That is why we need to use pairs with a unique
second value, the index of the element.

```cpp
#include <iostream>
using namespace std;

// These lines are needed for the policy-based data structures.
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

template <typename T>
using indexed_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

const int N = 200001;
int p[N];

int main() {
    int n, q;
    cin >> n >> q;

    indexed_set<pair<int, int>> s;

    for (int i = 1; i <= n; ++i) {
        cin >> p[i];
        s.insert({p[i], i});
    }

    for (int i = 1; i <= q; ++i) {
        char c;
        cin >> c;
        if (c == '?') {
            int l, r;
            cin >> l >> r;
            cout << s.order_of_key({r + 1, 0}) - s.order_of_key({l, 0}) << '\n';
        } else {
            int k, x;
            cin >> k >> x;
            s.erase(s.find({p[k], k}));
            p[k] = x;
            s.insert({p[k], k});
        }
    }
}
```

### References for policy-based data structures

* [CPHB (Competitive Programmer's Handbook)](http://cses.fi/book), Chapter 4
* [Codeforces, *C++ STL: Policy based data structures* by adamant](https://codeforces.com/blog/entry/11080)
* [Codeforces, *C++ STL: Policy based data structures. Part 2* by adamant](https://codeforces.com/blog/entry/13279)
* [The GNU C++ Library Manual](https://gcc.gnu.org/onlinedocs/libstdc++/manual/policy_data_structures_design.html), Chapter 21. Policy-Based Data Structures