#include <iostream>
#include <set>
#include <vector>
using namespace std;
const int INF = 999999999;
const int N = 1 << 18;

int tree[2 * N];

void set_val(int pos, int value) {
    pos += N;
    tree[pos] = value;
    for (pos /= 2; pos >= 1; pos /= 2) {
        tree[pos] = min(tree[2 * pos], tree[2 * pos + 1]);
    }
}

int get_min(int a, int b) {
    a += N;
    b += N;
    int result = tree[a];
    while (a <= b) {
        if (a % 2 == 1) {
            result = min(result, tree[a++]);
        }
        if (b % 2 == 0) {
            result = min(result, tree[b--]);
        }
        a /= 2;
        b /= 2;
    }
    return result;
}

set<pair<int, int>> pairs;

int find_next(int pos, int value) {
    auto it = pairs.upper_bound({value, pos});
    if (it == pairs.end() || it->first != value) {
        return INF;
    }
    return it->second;
}

int find_prev(int pos, int value) {
    auto it = pairs.lower_bound({value, pos});
    if (it == pairs.begin()) {
        return 0;
    }
    it--;
    if (it->first != value) {
        return 0;
    }
    return it->second;
}

int main() {
    int n, q;
    cin >> n >> q;

    vector<int> values(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> values[i];
        pairs.insert({values[i], i});
    }

    for (int i = 1; i < 2 * N; i++) {
        tree[i] = INF;
    }

    for (int i = 1; i <= n; i++) {
        int next_pos = find_next(i, values[i]);
        set_val(i, next_pos);
    }

    while (q--) {
        int op;
        cin >> op;

        if (op == 1) {
            int k, u;
            cin >> k >> u;

            int prev_pos, next_pos;

            prev_pos = find_prev(k, values[k]);
            next_pos = find_next(k, values[k]);
            set_val(prev_pos, next_pos);
            pairs.erase({values[k], k});

            values[k] = u;

            prev_pos = find_prev(k, values[k]);
            set_val(prev_pos, k);
            next_pos = find_next(k, values[k]);
            set_val(k, next_pos);
            pairs.insert({values[k], k});
        }

        if (op == 2) {
            int a, b;
            cin >> a >> b;
            int pos = get_min(a, b);
            if (pos <= b) {
                cout << "NO\n";
            } else {
                cout << "YES\n";
            }
        }
    }
}
