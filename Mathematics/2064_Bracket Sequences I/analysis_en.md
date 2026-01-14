# 2064 - Bracket Sequences I

If $n$ is odd, we can't create any valid bracket sequence, so we assume that $n$
is even. We focus on bracket sequences that consist of $\frac{n}{2}$ left
brackets and $\frac{n}{2}$ right brackets. The total number of such sequences is

$${n \choose \frac{n}{2}}.$$

Then, let us calculate the number of invalid bracket sequences that consist of
$\frac{n}{2}$ left brackets and $\frac{n}{2}$ right brackets. A sequence is
invalid if some prefix of it contains more right brackets than left brackets.

If we reverse each bracket in the minimal invalid prefix, we get another bracket
sequence that consists of $n+1$ left brackets and $n-1$ right brackets.
Moreover, there is a one-to-one mapping between invalid bracket sequences and
bracket sequences that consist of $n+1$ left brackets and $n-1$ right brackets.
Thus, the number of invalid bracket sequences is

$${n \choose \frac{n}{2}+1}.$$

We can now calculate the answer using the formula

$${n \choose \frac{n}{2}} - {n \choose \frac{n}{2} + 1}
= \frac{2}{n+2} {n \choose \frac{n}{2}}$$

where we subtract the number of invalid bracket sequences from the number of all
bracket sequences.

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
    if (n % 2 == 0) {
        ll answer = 2LL * ncr(n, n / 2) * inv(n + 2) % M;
        cout << answer << "\n";
    } else {
        cout << "0\n";
    }
}
```