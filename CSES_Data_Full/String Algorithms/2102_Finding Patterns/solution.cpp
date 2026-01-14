#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

struct SuffixArray {
    string s;
    int n;
    vector<int> sa;

    SuffixArray(string x) : s(x + "$"), n(s.size()), sa(n) {
        int bound = 1;
        while (bound < n) bound *= 2;
        vector<int> inv(2 * bound);
        copy(s.begin(), s.end(), inv.begin());
        vector<int> order(n);
        iota(order.begin(), order.end(), 0);
        for (int add = 1; add < bound; add *= 2) {
            vector<pair<int, int>> pairs(n);
            for (int i = 0; i < n; i++) {
                pairs[i] = {inv[i], inv[i + add]};
            }
            sort(order.begin(), order.end(),
                 [&](int a, int b) { return pairs[a] < pairs[b]; });
            int label = 1;
            for (int i = 0; i < n; i++) {
                label += i && pairs[order[i - 1]] != pairs[order[i]];
                inv[order[i]] = label;
            }
        }
        for (int i = 0; i < n; i++) {
            sa[inv[i] - 1] = i;
        }
    }

    // Returns the (half-open) range where pattern p appears in the suffix array
    pair<int, int> find(string p) {
        int m = p.size();
        auto left = sa.begin();
        auto right = sa.end();
        for (int i = 0; i < m; i++) {
            auto cmp = [&](int e, int v) {
                return s[e + i] < v;
            };
            auto new_left = lower_bound(left, right, p[i], cmp);
            auto new_right = lower_bound(left, right, p[i] + 1, cmp);
            left = new_left;
            right = new_right;
        }
        return {left - sa.begin(), right - sa.begin()};
    }
};

int main() {
    string s;
    cin >> s;
    SuffixArray sa(s);

    int k;
    cin >> k;
    for (int ki = 1; ki <= k; ki++) {
        string p;
        cin >> p;
        auto [l, r] = sa.find(p);
        cout << (r > l ? "YES" : "NO") << "\n";
    }
}
