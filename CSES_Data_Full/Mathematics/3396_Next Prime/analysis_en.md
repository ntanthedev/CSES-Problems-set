# 3396 - Next Prime

Let $\pi(n)$ denote the number of prime numbers between $1$ and $n$. It is known that
$$\pi(n) \approx \frac{n}{\log n}$$
and in practice, the gaps between two successive prime numbers are not very large. For this reason, we can solve this problem just by iterating over numbers greater than $n$ until we find the first prime number.

The largest prime gap between $1$ and $10^{12}$ is $540$, which occurs between the prime numbers $738832927927$ and $738832928467$.

```cpp
#include <iostream>
using namespace std;
using ll = long long;

bool prime(ll n) {
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (ll x = 3; x * x <= n; x += 2) {
        if (n % x == 0) return false;
    }
    return true;
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        ll n;
        cin >> n;
        n++;
        while (!prime(n)) n++;
        cout << n << "\n";
    }
}
```