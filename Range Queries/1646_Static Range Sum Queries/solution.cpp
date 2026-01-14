#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

int main() {
    int n, q;
    cin >> n >> q;

    vector<int> x(n);
    for (int &t : x) {
        cin >> t;
    }

    vector<ll> prefix_sums(n + 1);
    for (int i = 0; i < n; ++i) {
        prefix_sums[i + 1] = prefix_sums[i] + x[i];
    }

    for (int qi = 0; qi < q; ++qi) {
        int l, r;
        cin >> l >> r;
        l--;
        // Output the sum for range [l, r)
        cout << prefix_sums[r] - prefix_sums[l] << '\n';
    }
}
