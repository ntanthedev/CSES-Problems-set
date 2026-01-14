#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

const int TREE_SIZE = 1 << 18;
int tree[TREE_SIZE * 2];

void change(int k, int x) {
    k += TREE_SIZE;
    tree[k] = x;
    while (k > 1) {
        k /= 2;
        tree[k] = tree[k * 2] + tree[k * 2 + 1];
    }
}

// Returns the sum of values in range [l, r].
int query(int l, int r) {
    int ans = 0;
    l += TREE_SIZE;
    r += TREE_SIZE;
    while (l <= r) {
        if (l % 2 == 1) ans += tree[l++];
        if (r % 2 == 0) ans += tree[r--];
        l /= 2;
        r /= 2;
    }
    return ans;
}

struct Query {
    int l, r, i;
};

int main() {
    int n, q;
    cin >> n >> q;

    vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }

    // Stores occurrences of each value – in decreasing order.
    // Done this way, we can, at any time, efficiently
    // remove the smallest occurrence of any value
    // using the function `pop_back`.
    map<int, vector<int>> occurrences;
    for (int i = n - 1; i >= 0; --i) {
        occurrences[v[i]].push_back(i);
    }

    for (auto &[v, l] : occurrences) {
        change(l.back(), 1);
        l.pop_back();
    }

    vector<Query> queries(q);
    for (int i = 0; i < q; ++i) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].l--;
        queries[i].r--;
        queries[i].i = i;
    }

    sort(queries.begin(), queries.end(),
         [&](auto a, auto b) { return a.l < b.l; });

    vector<int> answer(q);

    for (int i = 0, j = 0; i < n; ++i) {
        while (j < q && queries[j].l == i) {
            answer[queries[j].i] = query(i, queries[j].r);
            ++j;
        }
        if (!occurrences[v[i]].empty()) {
            change(occurrences[v[i]].back(), 1);
            occurrences[v[i]].pop_back();
        }
    }

    for (int a : answer) {
        cout << a << ' ';
    }
    cout << '\n';
}
