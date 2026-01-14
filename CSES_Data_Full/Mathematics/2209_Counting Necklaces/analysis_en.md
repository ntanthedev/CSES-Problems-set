# 2209 - Counting Necklaces

We solve the problem using Burnside's lemma which states that the number of
distinct combinations is

$$\frac{1}{n} \sum\_{i=1}^n c(i)$$

when there are $n$ ways to change the position of a combination and there are
$c(i)$ combinations that remain the same when the $i$th way is applied.

In this problem there are $n$ ways to rotate the necklace: we can rotate it
$0,1,\dots,n-1$ steps. The number of combinations that remain the same is

$$m^{\gcd(i,n)}$$

because there is a repeating block of $\gcd(i,n)$ pearls and there are $m$ ways
to choose the color of each pearl inside the block.

```cpp
#include <iostream>
using namespace std;
using ll = long long;
const int M = 1000000007;

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int power(int a, int b) {
    if (b == 0) return 1;
    ll p = power(a, b / 2);
    p = p * p % M;
    if (b % 2 == 1) p = p * a % M;
    return p;
}

int inv(int x) {
    return power(x, M - 2);
}

int main() {
    int n, m;
    cin >> n >> m;

    ll sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += power(m, gcd(i, n));
        sum %= M;
    }
    ll answer = sum * inv(n) % M;
    cout << answer << "\n";
}
```

## References

* [Burnside's lemma (Wikipedia)](https://en.wikipedia.org/wiki/Burnside%27s_lemma)