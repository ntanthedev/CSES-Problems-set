# 2187 - Bracket Sequences II

This analysis assumes that you already know how to count the number of valid
bracket sequences of length $n$ using the reversed prefix technique. We use
almost the same idea to solve this problem.

We go through the given prefix of length $k$ and maintain the depth of the
sequence. Each left bracket increases the depth by one, and each right bracket
decreases the depth by one. If the depth ever becomes negative or the final
depth is more than $n-k$, there are no solutions.

Otherwise, let us calculate the number of valid sequences. Let $d$ denote the
final depth of the prefix. The remaining sequence consists of $n-k$ characters
and the number of left brackets is

$$l = \frac{n - k - d}{2}$$

so the total number of such sequences is

$${n - k \choose l}.$$

Then, the number of invalid sequences equals

$${n - k \choose l + d + 1}$$

because after reversing the minimal invalid prefix, the number of left brackets
increases by $d+1$. Thus, the answer to the problem is

$${n - k \choose l} - {n - k \choose l + d + 1}.$$

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
    string s;
    cin >> s;
    int k = s.size();

    int depth = 0;
    bool fail = false;
    for (auto c : s) {
        if (c == '(') depth++;
        if (c == ')') depth--;
        if (depth < 0) fail = true;
    }
    if (depth > n - k) fail = true;

    if (n % 2 == 0 && !fail) {
        int left = (n - k - depth) / 2;
        ll answer = ncr(n - k, left) - ncr(n - k, left + depth + 1);
        answer = (answer % M + M) % M;
        cout << answer << "\n";
    } else {
        cout << "0\n";
    }
}
```