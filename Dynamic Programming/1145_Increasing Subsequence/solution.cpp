#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int TREE_SIZE = 1 << 18;
int tree[TREE_SIZE * 2];

void update(int i, int x) {
    i += TREE_SIZE;
    tree[i] = max(tree[i], x);
    while (i > 1) {
        i /= 2;
        tree[i] = max(tree[2 * i], tree[2 * i + 1]);
    }
}

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

int main() {
    int n;
    cin >> n;
    vector<int> x(n);
    vector<int> sorted(n);
    for (int i = 0; i < n; ++i) {
        cin >> x[i];
        sorted[i] = x[i];
    }

    sort(sorted.begin(), sorted.end());

    for (int i = 0; i < n; ++i) {
        x[i] = lower_bound(sorted.begin(), sorted.end(), x[i]) - sorted.begin();
    }

    int result = 0;
    for (int i = 0; i < n; ++i) {
        int len = get_max(0, x[i] - 1) + 1;
        update(x[i], len);
        result = max(result, len);
    }

    cout << result << endl;
}
