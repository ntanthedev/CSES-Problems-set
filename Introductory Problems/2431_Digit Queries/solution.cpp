#include <iostream>
using namespace std;
using ll = long long;

int digit(ll k) {
    k--;
    ll a = 1;
    ll b = 9;
    int c = 1;
    while (k >= (b - a + 1) * c) {
        k -= (b - a + 1) * c;
        a = a * 10;
        b = b * 10 + 9;
        c++;
    }
    ll x = a + k / c;
    return to_string(x)[k % c] - '0';
}

int main() {
    int q;
    cin >> q;
    for (int qi = 0; qi < q; ++qi) {
        ll k;
        cin >> k;
        cout << digit(k) << "\n";
    }
}
