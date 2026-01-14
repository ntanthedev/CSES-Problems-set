#include <iostream>
using namespace std;
using ll = long long;
const int M = 1000000007;

int main() {
    ll n;
    cin >> n;

    ll s = 0;
    for (ll k = 1; k <= n; k++) {
        s += (n / k) * k;
        s %= M;
    }
    cout << s << "\n";
}
