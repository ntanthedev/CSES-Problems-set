# 2206 - Pizzeria Queries

This one is a bit trickier to solve
with regular segment trees.

Let us examine the price offers
in the cases of the first few indices.

The offers for the first position will look like this
$$p\_0+0,\ p\_1+1,\ p\_2+2,\ p\_3+3\ldots$$
and the offers for the second one like this
$$p\_0+1,\ p\_1+0,\ p\_2+1,\ p\_3+2\ldots$$

As can be seen from the examples,
the price offers for the second building
look almost exactly the same as the prices
for the first building.
In fact, from the second building on,
all of the prices differ by
only one unit.

Motivated by these observations,
an idea of a segment tree where
the index of each element is
added to its value comes to mind.

These segments trees would need to
be constructed for both
directions separately.
It turns out this works.

In the attached solutions, two
segment trees are used –
$\texttt{left\\_tree}$
and
$\texttt{right\\_tree}$.

To
$\texttt{left\\_tree}$
we will store,
to each position $i$,
the value $p\_i-i$
and
to
$\texttt{right\\_tree}$
we will store,
to each position $i$,
the value $p\_i+i$.
Then, we can answer queries
by taking the minimum values
separately, shifting them
by the current index
and returning the smaller of them.

```cpp
#include <iostream>
#include <vector>
using namespace std;
const int INF = (int)1e9;

struct Tree {
    int tree_size;
    vector<int> t;
    Tree(int n) {
        tree_size = 1;
        while (tree_size < n) {
            tree_size *= 2;
        }
        t.resize(tree_size * 2);
    }
    // Changes the value at position k to x.
    void change(int k, int x) {
        k += tree_size;
        t[k] = x;
        while (k > 1) {
            k /= 2;
            t[k] = min(t[k * 2], t[k * 2 + 1]);
        }
    }
    // Returns the minimum value in range [l, r]
    int query(int l, int r) {
        int ans = INF;
        l += tree_size;
        r += tree_size;
        while (l <= r) {
            if (l % 2 == 1) ans = min(ans, t[l++]);
            if (r % 2 == 0) ans = min(ans, t[r--]);
            l /= 2;
            r /= 2;
        }
        return ans;
    }
};

int main() {
    int n, q;
    cin >> n >> q;

    Tree left_tree(n), right_tree(n);

    vector<int> p(n);

    auto update = [&](int i) {
        left_tree.change(i, p[i] - i);
        right_tree.change(i, p[i] + i);
    };

    for (int i = 0; i < n; ++i) {
        cin >> p[i];
        update(i);
    }

    for (int qi = 0; qi < q; ++qi) {
        int t;
        cin >> t;
        if (t == 1) {
            int i;
            cin >> i;
            i--;
            cin >> p[i];
            update(i);
        } else {
            int i;
            cin >> i;
            i--;
            int left_ans = left_tree.query(0, i) + i;
            int right_ans = right_tree.query(i, n - 1) - i;
            cout << min(left_ans, right_ans) << '\n';
        }
    }
}
```