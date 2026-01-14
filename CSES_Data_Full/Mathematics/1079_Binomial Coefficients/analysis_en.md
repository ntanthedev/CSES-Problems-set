# 1079 - Binomial Coefficients

## Solution 1

Our task is to efficiently calculate values of binomial coefficients

$${a \choose b} = \frac{a!}{b!(a-b)!}$$

modulo $M$ where $a$ and $b$ are between $0$ and $N$ (in this problem $N=10^6$).

We first precalculate all factorials $k!$ modulo $M$ where $k$ is between $0$
and $N$. After that, we can calculate any binomial coefficient as a product of
a factorial and two inverse factorials.

```cpp
#include <iostream>
using namespace std;
using ll = long long;
const int M = 1000000007;
const int N = 1000000;

int power(int a, int b) {
    if (b == 0) return 1;
    ll u = power(a, b / 2);
    u = u * u % M;
    if (b % 2 == 1) u = u * a % M;
    return u;
}

int inv(int x) {
    return power(x, M - 2);
}

ll fac[N + 1];

int ncr(int a, int b) {
    return fac[a] * inv(fac[b] * fac[a - b] % M) % M;
}

int main() {
    fac[0] = 1;
    for (int i = 1; i <= N; i++) {
        fac[i] = fac[i - 1] * i % M;
    }

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int a, b;
        cin >> a >> b;
        cout << ncr(a, b) << "\n";
    }
}
```

## Solution 2

To create a more efficient solution, we can also precalculate the inverse values
of each factorial.

In the following code, we first calculate the inverse of $N!$. After that we can
use a simple loop that calculates the other inverse factorials. The loop works
because if we know the value of $\frac{1}{(k+1)!}$, we can multiply it by $k+1$
to get the value of $\frac{1}{k!}$.

```cpp
#include <iostream>
using namespace std;
using ll = long long;
const int M = 1000000007;
const int N = 1000000;

int power(int a, int b) {
    if (b == 0) return 1;
    ll u = power(a, b / 2);
    u = u * u % M;
    if (b % 2 == 1) u = u * a % M;
    return u;
}

int inv(int x) {
    return power(x, M - 2);
}

ll fac[N + 1];
ll inv_fac[N + 1];

int ncr(int a, int b) {
    return fac[a] * inv_fac[b] % M * inv_fac[a - b] % M;
}

int main() {
    fac[0] = 1;
    for (int i = 1; i <= N; i++) {
        fac[i] = fac[i - 1] * i % M;
    }
    inv_fac[N] = inv(fac[N]);
    for (int i = N - 1; i >= 0; i--) {
        inv_fac[i] = inv_fac[i + 1] * (i + 1) % M;
    }

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int a, b;
        cin >> a >> b;
        cout << ncr(a, b) << "\n";
    }
}
```