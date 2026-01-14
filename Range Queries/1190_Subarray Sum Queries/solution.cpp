#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

const int TREE_SIZE = 1 << 18;
struct Node {
    ll sum;            // Sum of the values
    ll max_sum;        // Maximum subarray sum
    ll max_sum_left;   // Maximum subarray sum from the left side
    ll max_sum_right;  // Maximum subarray sum from the right side
} tree[TREE_SIZE * 2];

Node merge(Node l, Node r) {
    return {l.sum + r.sum,
            max({l.max_sum, r.max_sum, l.max_sum_right + r.max_sum_left}),
            max(l.max_sum_left, l.sum + r.max_sum_left),
            max(r.max_sum_right, r.sum + l.max_sum_right)};
}

void update(int i, int x) {
    i += TREE_SIZE;
    tree[i] = {x, max(x, 0), max(x, 0), max(x, 0)};
    while (i > 1) {
        i /= 2;
        tree[i] = merge(tree[i * 2], tree[i * 2 + 1]);
    }
}

int main() {
    int n, q;
    cin >> n >> q;

    for (int i = 1; i <= n; ++i) {
        int x;
        cin >> x;
        update(i, x);
    }

    for (int qi = 0; qi < q; ++qi) {
        int k, x;
        cin >> k >> x;
        update(k, x);
        cout << tree[1].max_sum << '\n';
    }
}
