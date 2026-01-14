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
