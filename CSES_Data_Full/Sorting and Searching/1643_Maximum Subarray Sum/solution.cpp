#include <iostream>
using namespace std;
using ll = long long;

int main() {
    int n;
    cin >> n;

    ll sum = -1e9;
    ll best = -1e9;
    for (int i = 1; i <= n; i++) {
        ll x;
        cin >> x;
        sum = max(sum + x, x);
        best = max(best, sum);
    }
    cout << best << "\n";
}
