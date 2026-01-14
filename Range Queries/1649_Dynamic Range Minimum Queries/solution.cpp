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
        int t;
        cin >> t;
        if (t == 1) {
            int k, u;
            cin >> k >> u;
            change(k, u);
        } else {
            int l, r;
            cin >> l >> r;
            cout << get_min(l, r) << '\n';
        }
    }
}
