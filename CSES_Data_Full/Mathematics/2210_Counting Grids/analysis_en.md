# 2210 - Counting Grids

We solve the problem using Burnside's lemma which states that the number of
distinct combinations is

$$\frac{1}{n} \sum\_{i=1}^n c(i)$$

when there are $n$ ways to change the position of a combination and there are
$c(i)$ combinations that remain the same when the $i$th way is applied.

In this problem there are $4$ ways to rotate the grid: $0^{\circ}$,
$90^{\circ}$, $180^{\circ}$, and $270^{\circ}$. Our task is to count the
combinations that remain the same after each rotation. In each case we count the
number of squares whose color we can choose.

When $n$ is even, the numbers are as follows:

* $0^{\circ}$: $n^2$
* $90^{\circ}$: $\frac{n^2}{4}$
* $180^{\circ}$: $\frac{n^2}{2}$
* $270^{\circ}$: $\frac{n^2}{4}$

When $n$ is odd, the numbers are as follows:

* $0^{\circ}$: $n^2$
* $90^{\circ}$: $\lfloor \frac{n}{2} \rfloor \lfloor \frac{n}{2} + 1 \rfloor + 1$
* $180^{\circ}$: $n \lfloor \frac{n}{2} \rfloor + \lfloor \frac{n}{2} + 1 \rfloor$
* $270^{\circ}$: $\lfloor \frac{n}{2} \rfloor \lfloor \frac{n}{2} + 1 \rfloor + 1$

```cpp
#include <iostream>
using namespace std;
using ll = long long;
const int M = 1000000007;

int power(int a, ll b) {
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
    ll n;
    cin >> n;

    ll sum = 0;
    if (n % 2 == 0) {
        sum += power(2, n * n);
        sum += power(2, n * n / 4);
        sum += power(2, n * n / 2);
        sum += power(2, n * n / 4);
    } else {
        sum += power(2, n * n);
        sum += power(2, (n / 2) * (n / 2 + 1) + 1);
        sum += power(2, n * (n / 2) + (n / 2 + 1));
        sum += power(2, (n / 2) * (n / 2 + 1) + 1);
    }
    ll answer = sum * inv(4) % M;
    cout << answer << "\n";
}
```

## References

* [Burnside's lemma (Wikipedia)](https://en.wikipedia.org/wiki/Burnside%27s_lemma)