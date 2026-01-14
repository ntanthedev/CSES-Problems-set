#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

int main() {
    int n, t;
    cin >> n >> t;

    vector<int> times(n);
    for (int i = 0; i < n; i++) {
        cin >> times[i];
    }

    auto check = [&](ll x) {
        ll total = 0;
        for (int i = 0; i < n; i++) {
            total += x / times[i];
            if (total >= t) return true;
        }
        return false;
    };

    ll k = 0;
    for (ll b = 1e18; b >= 1; b /= 2) {
        while (!check(k + b)) k += b;
    }
    cout << k + 1 << "\n";
}
