# 1715 - Creating Strings II

## Solution 1

We first count the number of times each character appears in the string. After
that, we go through the characters and calculate the answer using binomial
coefficients.

Suppose the string has $n$ characters and the first character appears $k$ times
in the string. This means that there are ${n \choose k}$ ways to choose the
positions for the first character. After that, there are $n-k$ positions left
and we continue in the same way.

```cpp
#include <iostream>
#include <map>
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

    string s;
    cin >> s;
    int n = s.size();

    map<char, int> count;
    for (auto c : s) count[c]++;

    ll answer = 1;
    for (auto [c, k] : count) {
        answer = answer * ncr(n, k) % M;
        n -= k;
    }
    cout << answer << "\n";
}
```

## Solution 2

We can also calculate a multinomial coefficient

$${n \choose k\_1, k\_2, \dots, k\_m} = \frac{n!}{k\_1! k\_2! \dots k\_m!}$$

which corresponds to the number of ways we can divide $n$ elements into $m$ sets
whose sizes are $k\_1,k\_2,\dots,k\_m$.

In this problem $m$ equals the number of characters and $k\_i$ denotes the
number of times the $i$th character appears in the string.

```cpp
#include <iostream>
#include <map>
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

int main() {
    fac[0] = 1;
    for (int i = 1; i <= N; i++) {
        fac[i] = fac[i - 1] * i % M;
    }

    string s;
    cin >> s;
    int n = s.size();

    map<char, int> count;
    for (auto c : s) count[c]++;

    ll answer = fac[n];
    for (auto [c, k] : count) {
        answer = answer * inv(fac[k]) % M;
    }
    cout << answer << "\n";
}
```

## References

* [Wikipedia (Multinomial theorem)](https://en.wikipedia.org/wiki/Multinomial_theorem)