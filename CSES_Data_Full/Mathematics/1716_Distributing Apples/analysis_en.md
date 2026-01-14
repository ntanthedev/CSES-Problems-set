# 1716 - Distributing Apples

We can calculate the answer using the formula

$${n+m-1 \choose m}$$

where $n$ is the number of children and $m$ is the number of apples.

The idea is that there is a one-to-one mapping between apple distributions and
strings of length $n+m-1$ that have $m$ times character $X$ and $n-1$ times
character $\rightarrow$. The interpretation of each string is as follows: We
begin at the first child and read the string from left to right. If the
character is $X$, we give an apple to the current child, and if the character is
$\rightarrow$, we move to the next child.

```cpp
#include <iostream>
using namespace std;
using ll = long long;
const int M = 1000000007;
const int N = 2000000;

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

    int n, m;
    cin >> n >> m;
    cout << ncr(n + m - 1, m) << "\n";
}
```

## References

* [Stars and bars (combinatorics) (Wikipedia)](https://en.wikipedia.org/wiki/Stars_and_bars_(combinatorics))