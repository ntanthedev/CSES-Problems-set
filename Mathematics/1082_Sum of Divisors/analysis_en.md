# 1082 - Sum of Divisors

## Solution 1

Since a divisor $k$ appears in $\lfloor n / k \rfloor$ numbers between $1$ and
$n$, the problem can be restated as calculating the sum

$$\sum\_{k=1}^n \lfloor n / k \rfloor k.$$

The following solution calculates the sum in $O(n)$ time. It is a good start but
it is too slow when $n=10^{12}$.

```cpp
#include <iostream>
using namespace std;
using ll = long long;
const int M = 1000000007;

int main() {
    ll n;
    cin >> n;

    ll s = 0;
    for (ll k = 1; k <= n; k++) {
        s += (n / k) * k;
        s %= M;
    }
    cout << s << "\n";
}
```

## Solution 2

We can improve the first solution by calculating the sum in two parts.

First, we use the original formula for small divisors between $1$ and
$\lfloor \sqrt n \rfloor$. Then, we calculate the rest of the sum by considering
blocks of large divisors where each divisor appears the same number of times.

For example, we know that the divisors between $\lfloor n / 2 \rfloor + 1$ and
$n$ appear once, the divisors between $\lfloor n / 3 \rfloor + 1$ and
$\lfloor n / 2 \rfloor$ appear twice, and so on. More generally, the divisors
between $\lfloor n / (k + 1) \rfloor + 1$ and $\lfloor n / k \rfloor$ appear
$k$ times.

We calculate the sum of divisors in a block using the sum formula

$$a+(a+1)+\dots+b = \frac{(a + b) (b - a + 1)}{2}.$$

Note that since the sum may be large, we use the multiplicative inverse of $2$
modulo $M$ to divide the product by $2$.

We calculate both parts of the sum in $O(\sqrt n)$ time, so the algorithm works
in $O(\sqrt n)$ time which is enough when $n=10^{12}$.

```cpp
#include <iostream>
using namespace std;
using ll = long long;
const int M = 1000000007;
const int INV2 = 500000004;

// a + (a+1) + ... + b
ll sum(ll a, ll b) {
    return (a + b) % M * ((b - a + 1) % M) % M * INV2 % M;
}

int main() {
    ll n;
    cin >> n;

    ll s = 0;
    for (ll k = 1; k * k <= n; k++) {
        s += (n / k) * k;
        s %= M;
    }
    for (ll k = 1; n / k > k; k++) {
        s += sum(n / (k + 1) + 1, n / k) * k;
        s %= M;
    }
    cout << s << "\n";
}
```