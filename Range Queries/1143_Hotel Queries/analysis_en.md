# 1143 - Hotel Queries

## First approach: Regular binary search, $O(q \log^2 n)$

With binary search and a regular segment tree, this problem can be solved
straightforwardly. Each binary search makes $O(\log n)$
segment tree queries which all take $O(\log n)$ time. Thus answering all queries
takes
$O(q \log^2 n)$ time in total.

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
        tree[i] = max(tree[i * 2], tree[i * 2 + 1]);
    }
}

// Returns the maximum value in range [l, r]
int get_max(int l, int r) {
    int res = 0;
    l += TREE_SIZE;
    r += TREE_SIZE;
    while (l <= r) {
        if (l % 2 == 1) res = max(res, tree[l++]);
        if (r % 2 == 0) res = max(res, tree[r--]);
        l /= 2;
        r /= 2;
    }
    return res;
}

const int N = 200001;
int h[N];

int main() {
    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; ++i) {
        cin >> h[i];
        change(i, h[i]);
    }

    for (int i = 1; i <= m; ++i) {
        int x;
        cin >> x;
        if (tree[1] < x) {
            cout << 0 << ' ';
        } else {
            int l = 1, r = n;
            while (l < r) {
                int m = (l + r) / 2;
                if (get_max(1, m) < x) {
                    l = m + 1;
                } else {
                    r = m;
                }
            }
            h[l] -= x;
            change(l, h[l]);
            cout << l << ' ';
        }
    }
    cout << '\n';
}
```

## Second approach: Binary search in a segment tree, $O(q \log n)$

The special structure of the segment tree allows us to make a binary
search inside the tree.

The search starts in root node with the query range
being the whole array. The query proceeds by repeatedly moving to either the left
or the right child of the current node – each time halving the query range.
If there is a suitable hotel on the
range corresponding to the left node, the left child will be selected, otherwise
the right child will be selected.
A segment tree
has the height of
$O(\log n)$. Thus, the binary search takes $O(\log n)$ time.
Therefore, answering all queries
takes
$O(q \log n)$ time in total.

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
        tree[i] = max(tree[i * 2], tree[i * 2 + 1]);
    }
}

// Returns the index of the first value larger than x
int query(int x) {
    int s = 1;
    while (s < TREE_SIZE) {
        // The index of the left child is s * 2.
        // The index of the right child is s * 2 + 1.
        s = s * 2 + (tree[s * 2] < x);
    }
    return s - TREE_SIZE;
}

const int N = 200001;
int h[N];

int main() {
    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; ++i) {
        cin >> h[i];
        change(i, h[i]);
    }

    for (int i = 1; i <= m; ++i) {
        int x;
        cin >> x;
        if (tree[1] < x) {
            cout << 0 << ' ';
        } else {
            int pos = query(x);
            h[pos] -= x;
            change(pos, h[pos]);
            cout << pos << ' ';
        }
    }
    cout << '\n';
}
```

## References

* [CPHB (Competitive Programmer's Handbook)](http://cses.fi/book), Chapter 9
* [CP-Algorithms, Segment Tree](https://cp-algorithms.com/data_structures/segment_tree.html)