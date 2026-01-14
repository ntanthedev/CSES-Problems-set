# 1712 - Exponentiation II

Our task is to calculate the value of $a^{b^c}$ where the exponent $b^c$ can be
a large number. To solve the problem, we use Fermat's little theorem which
states that

$$a^{m-1} \bmod m = 1$$

when $m$ is a prime and $a$ is not divisible by $m$. Thus,

$$a^{b^c} \bmod m = a^{b^c \, \bmod \, (m-1)} \bmod m$$

which allows us to calculate the answer efficiently.

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
        int a, b, c;
        cin >> a >> b >> c;
        cout << power(a, power(b, c, 1e9 + 6), 1e9 + 7) << "\n";
    }
}
```

## References

* [Fermat's little theorem (Wikipedia)](https://en.wikipedia.org/wiki/Fermat%27s_little_theorem)