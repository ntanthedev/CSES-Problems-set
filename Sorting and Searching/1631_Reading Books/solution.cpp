#include <iostream>
using namespace std;
using ll = long long;

int main() {
    int n;
    cin >> n;

    ll total = 0;
    ll longest = 0;
    for (int i = 1; i <= n; i++) {
        ll x;
        cin >> x;
        total += x;
        longest = max(longest, x);
    }

    cout << max(total, 2 * longest) << "\n";
}
