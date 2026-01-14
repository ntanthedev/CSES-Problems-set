# 2182 - Divisor Analysis

We are given a number

$$N=\prod\_{i=1}^n x\_i^{k\_i}$$

and our task is to calculate the number, sum and product of its divisors.

## Solution 1

We calculate the number of divisors as follows:

$$d(N) = \prod\_{i=1}^n (k\_i + 1)$$

The formula works because there are $k\_i+1$ ways to choose a factor $x\_i$.

We calculate the sum of divisors as follows:

$$s(N) = \prod\_{i=1}^n (1 + x\_i + x\_i^2 + \dots + x\_i^{k\_i})
= \prod\_{i=1}^n \frac{x\_i^{k\_i+1}-1}{x\_i-1}$$

This formula corresponds to a sum where each divisor appears exactly once. Since
each part of the product is a geometric sum, we can calculate the answer more
efficiently using the geometric sum formula.

We calculate the product of divisors as follows:

$$p(N) = \prod\_{i=1}^n (x\_i^{k\_i(k\_i+1)/2})^{d(N)/(k\_i+1)}$$

This formula works because if a factor $x\_i$ appears in a divisor, it can appear
between $1$ and $k\_i$ times, so we can use the sum formula $k\_i(k\_i+1)/2$ to
count the total number of factor appearances. Moreover, there are $d(N)/(k\_i+1)$
ways to choose the other factors.

Note that since we want to calculate the answer modulo $M$, we have to calculate
$d(N)/(k\_i+1)$ modulo $M-1$. We can't use modular multiplicative inverses here
because $k\_i+1$ and $M-1$ are not necessarily coprime. Instead, we create two
additional vectors that store prefix and suffix products of $k\_i+1$ values and
use them in the last loop.

```cpp
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const int M = 1000000007;

ll power(ll a, ll b) {
    if (b == 0) return 1;
    ll u = power(a, b / 2);
    u = u * u % M;
    if (b % 2 == 1) u = u * a % M;
    return u;
}

ll inv(ll x) {
    return power(x, M - 2);
}

int main() {
    int n;
    cin >> n;

    vector<ll> x(n), k(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> k[i];
    }

    ll count = 1;
    for (int i = 0; i < n; i++) {
        count = count * (k[i] + 1) % M;
    }

    ll sum = 1;
    for (int i = 0; i < n; i++) {
        sum = sum * (power(x[i], k[i] + 1) - 1) % M;
        sum = sum * inv(x[i] - 1) % M;
    }

    vector<ll> prefix(n + 1);
    prefix[0] = 1;
    for (int i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i] * (k[i] + 1) % (M - 1);
    }

    vector<ll> suffix(n);
    suffix[n - 1] = 1;
    for (int i = n - 1; i > 0; i--) {
        suffix[i - 1] = suffix[i] * (k[i] + 1) % (M - 1);
    }

    ll prod = 1;
    for (int i = 0; i < n; i++) {
        ll ways = prefix[i] * suffix[i] % (M - 1);
        prod *= power(power(x[i], k[i] * (k[i] + 1) / 2), ways);
        prod %= M;
    }

    cout << count << " " << sum << " " << prod << "\n";
}
```

## Solution 2

A more elegant way to calculate the product of divisors is as follows:

$$p(N) = N^{d(N)/2}$$

We can derive this formula from the previous formula by simplifying the
exponents:

$$p(N) = \prod\_{i=1}^n (x\_i^{k\_i(k\_i+1)/2})^{d(N)/(k\_i+1)}
= \prod\_{i=1}^n (x\_i^{k\_i})^{d(N)/2}
= N^{d(N)/2}$$

The following solution calculates the product of divisors using this formula
and does not require additional vectors.

We need to calculate $d(N)/2$ modulo $M-1$ and we can't use modular
multiplicative inverses because $M-1$ and $2$ are not coprime. We handle two
cases in the code:

Case 1: $N$ is not square. There is an even value $k\_i+1$ and we divide the
first such value by two to calculate the exponent $d(N)/2$.

Case 2: $N$ is square. Now $d(N)$ is odd and $d(N)/2$ is not an integer.
However, $\sqrt{N}$ is an integer so we can use the formula
$N^{d(N)/2}=\sqrt{N}^{d(N)}$ to calculate the answer. In this case all $k\_i$
values are even and we divide each of them by two in the last loop.

Another way to explain the formula $N^{d(N)/2}$ is to consider divisor pairs of
the form $(k,N/k)$ where $k<N/k$. When $N$ is not square, there are $d(N)/2$
pairs and the product of each pair is $N$. When $N$ is square, there are
$(d(N)-1)/2$ pairs with product $N$ and then an additional divisor
$\sqrt{N}=N^{1/2}$. The formula holds also in this case because

$$N^{(d(N)-1)/2} N^{1/2} = N^{d(N)/2}.$$

```cpp
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const int M = 1000000007;

ll power(ll a, ll b) {
    if (b == 0) return 1;
    ll u = power(a, b / 2);
    u = u * u % M;
    if (b % 2 == 1) u = u * a % M;
    return u;
}

ll inv(ll x) {
    return power(x, M - 2);
}

int main() {
    int n;
    cin >> n;

    vector<ll> x(n), k(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> k[i];
    }

    ll count = 1;
    for (int i = 0; i < n; i++) {
        count = count * (k[i] + 1) % M;
    }

    ll sum = 1;
    for (int i = 0; i < n; i++) {
        sum = sum * (power(x[i], k[i] + 1) - 1) % M;
        sum = sum * inv(x[i] - 1) % M;
    }

    ll count2 = 1;
    bool is_square = true;
    for (int i = 0; i < n; i++) {
        if (is_square && k[i] % 2 == 1) {
            count2 *= (k[i] + 1) / 2;
            is_square = false;
        } else {
            count2 *= (k[i] + 1);
        }
        count2 %= M - 1;
    }

    ll prod = 1;
    for (int i = 0; i < n; i++) {
        if (is_square) k[i] /= 2;
        prod *= power(power(x[i], k[i]), count2);
        prod %= M;
    }

    cout << count << " " << sum << " " << prod << "\n";
}
```