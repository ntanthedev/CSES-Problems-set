#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;
using ll = long long;
const int N = 20;

int main() {
    int t;
    cin >> t;

    vector<ll> fact(N + 1);
    fact[0] = 1;
    for (int i = 1; i <= N; i++) {
        fact[i] = fact[i - 1] * i;
    }

    while (t--) {
        int op;
        cin >> op;

        int n;
        cin >> n;

        ll f = fact[n];
        vector<int> numbers(n);
        iota(numbers.begin(), numbers.end(), 1);

        if (op == 1) {
            ll k;
            cin >> k;
            k--;
            for (int i = 0; i < n; i++) {
                f /= n - i;
                cout << numbers[k / f] << " ";
                numbers.erase(numbers.begin() + (k / f));
                k %= f;
            }
            cout << "\n";
        }

        if (op == 2) {
            ll k = 1;
            for (int i = 0; i < n; i++) {
                int x;
                cin >> x;
                f /= n - i;
                auto it = find(numbers.begin(), numbers.end(), x);
                k += (it - numbers.begin()) * f;
                numbers.erase(it);
            }
            cout << k << "\n";
        }
    }
}
