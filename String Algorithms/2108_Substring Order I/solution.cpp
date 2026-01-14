#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;
using ll = long long;

struct SuffixArray {
    string s;
    int n;
    vector<int> sa;
    vector<int> lcp;

    SuffixArray(string x) : s(x + "$"), n(s.size()), sa(n), lcp(n) {
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
            inv[i]--;
            sa[inv[i]] = i;
        }
        for (int i = 0; i < n - 1; i++) {
            int k = inv[i];
            if (i) lcp[k] = max(0, lcp[inv[i - 1]] - 1);
            while (s[sa[k - 1] + lcp[k]] == s[sa[k] + lcp[k]]) lcp[k]++;
        }
    }
};

int main() {
    string s;
    cin >> s;
    int n = s.size();
    ll k;
    cin >> k;

    SuffixArray sa(s);
    for (int i = 1; i <= n; i++) {
        int add = n - sa.sa[i] - sa.lcp[i];
        if (k > add) {
            k -= add;
        } else {
            cout << s.substr(sa.sa[i], sa.lcp[i] + k) << "\n";
            break;
        }
    }
}
