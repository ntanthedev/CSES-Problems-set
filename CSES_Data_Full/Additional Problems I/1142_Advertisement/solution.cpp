#include <iostream>
using namespace std;
using ll = long long;

const int N = 200002;
int k[N];
int prev_lower[N], next_lower[N];

int main() {
    int n;
    cin >> n;

    for (int i = 1; i <= n; ++i) {
        cin >> k[i];
    }

    for (int i = 1; i <= n; ++i) {
        prev_lower[i] = i - 1;
        while (prev_lower[i] >= 0 && k[prev_lower[i]] >= k[i]) {
            prev_lower[i] = prev_lower[prev_lower[i]];
        }
    }

    for (int i = n; i >= 1; --i) {
        next_lower[i] = i + 1;
        while (next_lower[i] <= n && k[next_lower[i]] >= k[i]) {
            next_lower[i] = next_lower[next_lower[i]];
        }
    }

    ll ans = 0;
    for (int i = 1; i <= n; ++i) {
        ans = max(ans, 1ll * (next_lower[i] - prev_lower[i] - 1) * k[i]);
    }

    cout << ans << '\n';
}
