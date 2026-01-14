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
