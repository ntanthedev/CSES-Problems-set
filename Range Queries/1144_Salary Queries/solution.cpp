#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int TREE_SIZE = 1 << 20;
int tree[TREE_SIZE * 2];

// Add x to position i.
void change(int i, int x) {
    i += TREE_SIZE;
    while (i > 0) {
        tree[i] += x;
        i /= 2;
    }
}

// Returns the sum of values in range [l, r]
int query(int l, int r) {
    int sum = 0;
    l += TREE_SIZE;
    r += TREE_SIZE;
    while (l <= r) {
        if (l % 2 == 1) sum += tree[l++];
        if (r % 2 == 0) sum += tree[r--];
        l /= 2;
        r /= 2;
    }
    return sum;
}

const int N = 200001;
int p[N];

char qt[N];
int qa[N], qb[N];

int main() {
    int n, q;
    cin >> n >> q;

    for (int i = 1; i <= n; ++i) {
        cin >> p[i];
    }

    vector<int> values(p + 1, p + 1 + n);

    for (int i = 1; i <= q; ++i) {
        cin >> qt[i] >> qa[i] >> qb[i];
        if (qt[i] == '?') {
            values.push_back(qa[i]);
            values.push_back(qb[i]);
        } else {
            values.push_back(qb[i]);
        }
    }

    sort(values.begin(), values.end());
    values.erase(unique(values.begin(), values.end()), values.end());

    // Returns the index of x in the sorted vector `values`.
    auto index = [&](int x) {
        return (int)(lower_bound(values.begin(), values.end(), x) -
                     values.begin());
    };

    for (int i = 1; i <= n; ++i) {
        change(index(p[i]), +1);
    }

    for (int i = 1; i <= q; ++i) {
        if (qt[i] == '?') {
            cout << query(index(qa[i]), index(qb[i])) << '\n';
        } else {
            change(index(p[qa[i]]), -1);
            p[qa[i]] = qb[i];
            change(index(p[qa[i]]), +1);
        }
    }
}
