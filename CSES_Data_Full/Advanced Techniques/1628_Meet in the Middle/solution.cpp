#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

// Returns a list of all subset sums, in sorted order.
vector<ll> subsets(vector<int> x) {
    int n = x.size();
    vector<ll> ret(1 << n);
    for (int m = 0; m < (1 << n); ++m) {
        for (int j = 0; j < n; ++j) {
            if ((1 << j) & m) ret[m] += x[j];
        }
    }
    sort(ret.begin(), ret.end());
    return ret;
}

int main() {
    int n, x;
    cin >> n >> x;

    vector<int> t(n);
    for (int i = 0; i < n; ++i) {
        cin >> t[i];
    }

    auto a = subsets(vector<int>(t.begin(), t.begin() + n / 2));
    auto b = subsets(vector<int>(t.begin() + n / 2, t.end()));

    ll r = 0;
    int m = a.size(), bi = b.size() - 1;

    for (int i = 0, j = 0; i < m; i = j) {
        while (j < m && a[i] == a[j]) ++j;
        while (bi >= 0 && a[i] + b[bi] > x) --bi;
        while (bi >= 0 && a[i] + b[bi] == x) {
            r += j - i;
            bi--;
        }
    }

    cout << r << '\n';
}
