#include <iostream>
using namespace std;
using ll = long long;

ll f(ll y, ll x) {
    ll m = max(y, x);
    ll r = (m - 1) * (m - 1);
    if (m % 2 == 0) {
        r += y + m - x;
    } else {
        r += x + m - y;
    }
    return r;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        ll y, x;
        cin >> y >> x;
        cout << f(y, x) << "\n";
    }
}
