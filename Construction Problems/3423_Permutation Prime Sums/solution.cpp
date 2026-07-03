#include <bits/stdc++.h>
using namespace std;

vector<bool> is_prime;
vector<int> primes;

void sieve(int n) {
    is_prime.assign(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= n; ++i) {
        if (is_prime[i]) {
            for (int j = i * i; j <= n; j += i) is_prime[j] = false;
        }
    }
    for (int i = 2; i <= n; ++i)
        if (is_prime[i]) primes.push_back(i);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    sieve(2 * n + 5);

    vector<int> b(n + 1, 0);
    int cur = n;
    while (cur > 0) {
        int prime = *upper_bound(primes.begin(), primes.end(), cur);
        int a = prime / 2;
        int bb = prime - a;
        while (a > 0 && bb <= cur) {
            b[a] = bb;
            b[bb] = a;
            --a;
            ++bb;
        }
        cur = a;
    }

    for (int i = 1; i <= n; ++i) {
        if (i > 1) cout << ' ';
        cout << i;
    }
    cout << '\n';
    for (int i = 1; i <= n; ++i) {
        if (i > 1) cout << ' ';
        cout << b[i];
    }
    cout << '\n';
    return 0;
}
