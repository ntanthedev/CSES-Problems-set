#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

int main() {
    ll n;
    int k;
    cin >> n >> k;

    vector<ll> primes(k);
    for (int i = 0; i < k; i++) {
        cin >> primes[i];
    }

    ll answer = 0;
    for (int b = 1; b < (1 << k); b++) {
        ll prod = 1;
        bool fail = false;

        for (int i = 0; i < k; i++) {
            if (b & (1 << i)) {
                if (primes[i] > n / prod) fail = true;
                prod *= primes[i];
            }
        }

        if (fail) continue;

        ll add = n / prod;
        if (__builtin_parity(b) == 0) add = -add;
        answer += add;
    }

    cout << answer << "\n";
}
