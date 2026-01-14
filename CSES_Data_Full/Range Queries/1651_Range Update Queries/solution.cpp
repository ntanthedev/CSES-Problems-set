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
