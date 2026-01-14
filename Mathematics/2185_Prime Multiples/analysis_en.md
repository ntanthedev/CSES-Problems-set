# 2185 - Prime Multiples

We solve the problem using the inclusion-exclusion technique.

We go through every nonempty subset of $\{a\_1,a\_2,\dots,a\_k\}$. The number of
integers between $1$ and $n$ that are divisible by all primes in the chosen
subset equals $x=\lfloor n/p \rfloor$ where $p$ is the product of the primes in
the subset.

If the subset has an odd number of primes, we increase the answer by $x$, and
otherwise we decrease the answer by $x$. After processing all the subsets, we
have counted the numbers that are divisible by at least one prime.

Note that $p$ can be a large number and it can overflow, so we have to make sure
that the code works also in this case.

The algorithm works in $O(2^k k)$ time because it goes through $O(2^k)$ subsets
and processes each subset in $O(k)$ time.

```cpp
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
```