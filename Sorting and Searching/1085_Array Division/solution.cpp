#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> x(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }

    auto check = [&](ll s) {
        int p = 1;
        ll c = 0;
        for (int i = 0; i < n; i++) {
            if (x[i] > s) return false;
            c += x[i];
            if (c > s) {
                p++;
                c = x[i];
            }
        }
        return p <= k;
    };

    ll s = 0;
    for (ll b = 1e18; b >= 1; b /= 2) {
        while (!check(s + b)) s += b;
    }
    cout << s + 1 << "\n";
}
