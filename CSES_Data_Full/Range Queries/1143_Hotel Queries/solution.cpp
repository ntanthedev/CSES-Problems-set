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
