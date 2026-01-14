# 1749 - List Removals

## First approach: Segment tree

We can use a segment tree to solve this problem.
In the tree, active (not yet removed) elements
are represented by a one and inactive (removed) by
a zero.

To find the $k$th active value, we will do a
binary search in the tree.

```cpp
#include <iostream>
using namespace std;

const int TREE_SIZE = 1 << 18;
int tree[TREE_SIZE * 2];

// Changes the value in the position i to x.
void change(int i, int x) {
    i += TREE_SIZE;
    tree[i] = x;
    while (i > 1) {
        i /= 2;
        tree[i] = tree[i * 2] + tree[i * 2 + 1];
    }
}

// Returns the index of the kth 'active' position.
int query(int k) {
    int s = 1;
    while (s < TREE_SIZE) {
        // The index of the left child is s * 2.
        // The index of the right child is s * 2 + 1.
        if (tree[s * 2] >= k) {
            s = s * 2;
        } else {
            k -= tree[s * 2];
            s = s * 2 + 1;
        }
    }
    return s - TREE_SIZE;
}

const int N = 200001;
int x[N];

int main() {
    int n;
    cin >> n;

    for (int i = 1; i <= n; ++i) {
        cin >> x[i];
        change(i, 1);
    }

    for (int i = 1; i <= n; ++i) {
        int p;
        cin >> p;
        int pos = query(p);
        cout << x[pos] << ' ';
        change(pos, 0);
    }
    cout << '\n';
}
```

### References for segment trees

* [CPHB (Competitive Programmer's Handbook)](http://cses.fi/book), Chapter 9
* [CP-Algorithms, Segment Tree](https://cp-algorithms.com/data_structures/segment_tree.html)

## Second approach: Policy-based data structures

The g++ compiler – the one used on CSES – has some built-in data structures
that are not part of the C++ standard library.
One of these data structures is a binary tree, similar to `std::set`.
This binary search tree provides some useful additional functionality,
including a function for finding the i-th element in the set.

With this function, we may solve this problem without using a segment tree.

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
int x[N];

int main() {
    int n;
    cin >> n;

    indexed_set<int> s;

    for (int i = 1; i <= n; ++i) {
        cin >> x[i];
        s.insert(i);
    }

    for (int i = 1; i <= n; ++i) {
        int p;
        cin >> p;
        // Note, that the function `find_by_order` expects
        // a 0-indexed position.
        auto it = s.find_by_order(p - 1);
        int pos = *it;
        cout << x[pos] << ' ';
        s.erase(it);
    }
    cout << '\n';
}
```

Note that these unorthodox data structures are seldom
used in the indented solution to a competitive programming
problem.
That said they are worth knowing as they sometimes come in
handy and can be used to achieve better time complexities and
much shorter implementations.

Lastly, the policy-based binary search tree
has a notable pitfall:
there exists no policy-based
alternative for `std::multiset`. To get around
this problem
`std::pairs` can be stored in the tree with
the second element of each pair being a unique value.

### References for policy-based data structures

* [CPHB (Competitive Programmer's Handbook)](http://cses.fi/book), Chapter 4
* [Codeforces, *C++ STL: Policy based data structures* by adamant](https://codeforces.com/blog/entry/11080)
* [Codeforces, *C++ STL: Policy based data structures. Part 2* by adamant](https://codeforces.com/blog/entry/13279)
* [The GNU C++ Library Manual](https://gcc.gnu.org/onlinedocs/libstdc++/manual/policy_data_structures_design.html), Chapter 21. Policy-Based Data Structures