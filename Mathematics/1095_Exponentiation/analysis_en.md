# 1095 - Exponentiation

A simple way to calculate the value of $a^b \bmod m$ would be to use a loop that
consists of $b$ rounds:

```cpp
for (int i = 0; i < b; i++) {
    p = p * a % m;
}
```

Such a solution requires $O(b)$ time and would be too slow. However, we can
create a more efficient $O(\log b)$ time solution by using the fact that
$a^b = a^{b/2} a^{b/2}$ when $b$ is even. Using this formula, it suffices to
calculate $a^{b/2}$ only once and reuse the result.

## Solution 1 (recursive)

Let $\textrm{power}(a,b,m) = a^b \bmod m$. If $b=0$, the answer is $1 \bmod m$.
Otherwise, we first calculate $p = \textrm{power}(a,\lfloor b/2 \rfloor,m)$.
If $b$ is even, the answer is $p^2 \bmod m$, and if $b$ is odd, the answer is
$p^2 a \bmod m$.

```cpp
#include <iostream>
using namespace std;
using ll = long long;

int power(int a, int b, int m) {
    if (b == 0) return 1 % m;
    ll p = power(a, b / 2, m);
    p = p * p % m;
    if (b % 2 == 1) p = p * a % m;
    return p;
}

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int a, b;
        cin >> a >> b;
        cout << power(a, b, 1e9 + 7) << "\n";
    }
}
```

## Solution 2 (iterative)

We can also implement the algorithm iteratively which is more efficient in
practice. The following code goes through the binary representation of $b$ and
stores the corresponding power of $a$ in $f$, that is, for each power of two
$2^k$, $f$ is equal to $a^{2^k}$.

```cpp
#include <iostream>
using namespace std;
using ll = long long;

int power(int a, int b, int m) {
    ll p = 1 % m;
    ll f = a;
    while (b) {
        if (b & 1) p = p * f % m;
        f = f * f % m;
        b /= 2;
    }
    return p;
}

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int a, b;
        cin >> a >> b;
        cout << power(a, b, 1e9 + 7) << "\n";
    }
}
```

## References

* [Binary Exponentiation (CP-algorithms)](https://cp-algorithms.com/algebra/binary-exp.html)