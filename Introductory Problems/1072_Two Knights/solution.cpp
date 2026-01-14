#include <iostream>
using namespace std;
using ll = long long;

ll f(ll n) {
    ll r = n * n * (n * n - 1);
    r -= 4 * 2;
    r -= 8 * 3;
    r -= 4 * 4;
    r -= (n - 4) * 4 * 4;
    r -= (n - 4) * 4 * 6;
    r -= (n - 4) * (n - 4) * 8;
    return r / 2;
}

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cout << f(i) << "\n";
    }
}
