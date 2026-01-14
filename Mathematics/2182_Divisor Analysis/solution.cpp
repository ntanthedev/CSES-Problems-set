#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const int M = 1000000007;

ll power(ll a, ll b) {
    if (b == 0) return 1;
    ll u = power(a, b / 2);
    u = u * u % M;
    if (b % 2 == 1) u = u * a % M;
    return u;
}

ll inv(ll x) {
    return power(x, M - 2);
}

int main() {
    int n;
    cin >> n;

    vector<ll> x(n), k(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> k[i];
    }

    ll count = 1;
    for (int i = 0; i < n; i++) {
        count = count * (k[i] + 1) % M;
    }

    ll sum = 1;
    for (int i = 0; i < n; i++) {
        sum = sum * (power(x[i], k[i] + 1) - 1) % M;
        sum = sum * inv(x[i] - 1) % M;
    }

    vector<ll> prefix(n + 1);
    prefix[0] = 1;
    for (int i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i] * (k[i] + 1) % (M - 1);
    }

    vector<ll> suffix(n);
    suffix[n - 1] = 1;
    for (int i = n - 1; i > 0; i--) {
        suffix[i - 1] = suffix[i] * (k[i] + 1) % (M - 1);
    }

    ll prod = 1;
    for (int i = 0; i < n; i++) {
        ll ways = prefix[i] * suffix[i] % (M - 1);
        prod *= power(power(x[i], k[i] * (k[i] + 1) / 2), ways);
        prod %= M;
    }

    cout << count << " " << sum << " " << prod << "\n";
}
