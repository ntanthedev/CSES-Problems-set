# 1717 - Christmas Party

In this problem our task is to calculate the number of derangements of $n$
elements, i.e., the number of permutations of $n$ elements where no element has
its original position.

## Solution 1

Let us first calculate the number of permutations that are *not* derangements.
We can do that using the inclusion-exclusion technique. After that, we subtract
the result from the number of all permutations.

We calculate a value $f(n,i)$ for $i=1,2,\dots,n$: the number of permutations of
$n$ elements where $i$ elements have their original positions and other elements
have arbitrary positions. We use the formula

$$f(n,i) = {n \choose i} (n - i)!$$

where ${n \choose i}$ counts the number of ways to choose the elements that have
their original positions and $(n-i)!$ counts the number of ways to order the
other elements. If $i$ is odd, we add $f(n,i)$ to the result, and if $i$ is
even, we subtract $f(n,i)$ from the result.

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
    ll count = 0;
    for (int i = 1; i <= n; i++) {
        ll add = ncr(n, i) * fac[n - i] % M;
        if (i % 2 == 0) add = -add;
        count += add;
    }
    ll answer = ((fac[n] - count) % M + M) % M;
    cout << answer << "\n";
}
```

## Solution 2

We can also count the number of derangements recursively as follows:

$$d(n) = (n - 1) (d(n - 2) + d(n - 1))$$

The base cases are $d(1)=0$ and $d(2)=1$.

We can derive the formula as follows: Suppose there are $n$ children and there
is a fixed child $x$. We know that child $x$ gives a gift to some child $y$ and
there are $n-1$ ways to choose child $y$. Then there are two cases:

* Case 1: Child $y$ also gives a gift to child $x$. In this case we can remove
  children $x$ and $y$ and there are $d(n-2)$ ways to distribute gifts to the
  remaining $n-2$ children.
* Case 2: Child $y$ gives a gift to some other child. Now let us look at any
  gift distribution to $n-1$ children without child $x$. There are $d(n-1)$
  such distributions, and there is a single way to modify each distribution so
  that child $x$ is included: child $x$ gives a gift to child $y$ and then the
  child who originally gave a gift to child $y$ gives it to child $x$.

```cpp
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const int M = 1000000007;

int main() {
    int n;
    cin >> n;

    vector<ll> count(n + 1);
    count[1] = 0;
    count[2] = 1;
    for (int i = 3; i <= n; i++) {
        count[i] = (i - 1) * (count[i - 2] + count[i - 1]) % M;
    }
    cout << count[n] << "\n";
}
```

## References

* [Derangement (Wikipedia)](https://en.wikipedia.org/wiki/Derangement)