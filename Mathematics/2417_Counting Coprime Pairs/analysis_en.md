# 2417 - Counting Coprime Pairs

## Solution 1

Instead of calculating the number of coprime pairs, we calculate the number of
pairs that are *not* coprime, i.e., they have a common divisor.

We go through the numbers and create a vector `factors` for each number. This
vector consists of all distinct prime factors of the number. After that we go
through all subsets of the vector, which correspond to all distinct numbers
that can be created using the factors.

We use the inclusion-exclusion technique to calculate the answer. At position
$i$, we calculate the number of pairs where $j<i$ and $\gcd(x[i],x[j]) > 1$.
For this, we create a vector `total` that contains the number of times each
factor combination has appeared in previous numbers.

Finally, we subtract the answer from $n(n-1)/2$ which is the number of all
pairs that can be created using the numbers.

The solution works in $O(n (\sqrt N + 2^K K))$ time where $N$ is the upper bound
for input numbers and $K$ is the upper bound for the number of distinct prime
factors. Here $N=10^6$ and $K=7$ because
$2 \cdot 3 \cdot 5 \cdot 7 \cdot 11 \cdot 13 \cdot 15 = 450450$.

```cpp
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const int N = 1000000;

int main() {
    vector<int> total(N + 1);

    int n;
    cin >> n;
    ll answer = 0;

    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;

        vector<int> factors;
        for (int f = 2; f * f <= x; f++) {
            if (x % f == 0) {
                factors.push_back(f);
                while (x % f == 0) x /= f;
            }
        }
        if (x != 1) factors.push_back(x);

        int k = factors.size();
        for (int b = 1; b < (1 << k); b++) {
            int prod = 1;
            for (int i = 0; i < k; i++) {
                if (b & (1 << i)) prod *= factors[i];
            }

            int add = total[prod];
            if (__builtin_parity(b) == 0) add = -add;
            answer += add;
            total[prod]++;
        }
    }

    cout << (n * ll(n - 1) / 2) - answer << "\n";
}
```

## Solution 2

Another way to solve the problem is to use the Möbius inversion technique. We
want to calculate the sum

$$\sum\_{i=1}^n \sum\_{j=1}^n [\gcd(x\_i,x\_j) = 1]$$

where the indicator notation $[\dots]$ means that the value of the expression is
$1$ if the condition holds and $0$ otherwise. This sum corresponds to

$$\sum\_{i=1}^n \sum\_{j=1}^n \sum\_{d \mid \gcd(x\_i,x\_j)} \mu(d)$$

where $\mu(d)$ denotes the Möbius function. Since we want that $d$ divides
$\gcd(x\_i,x\_j)$, this means that $d$ must divide both $x\_i$ and $x\_j$ and we can
use the indicator notation to choose the $d$ values that are counted:

$$\sum\_{i=1}^n \sum\_{j=1}^n \sum\_{d=1}^N \mu(d) [d \mid x\_i] [d \mid x\_j]$$

Here $N$ is the upper bound for the input values.

After that, we reorder the summation as follows:

$$\sum\_{d=1}^N (\mu(d) (\sum\_{i=1}^n [d \mid x\_i]) (\sum\_{i=1}^n [d \mid x\_i]))$$

Note that the last two sums are independent of each other so we can use the
variable $i$ in both sums and calculate them separately.

We precalculate all values of $\mu(d)$ and $\sum\_{i=1}^n [d \mid x\_i]$ using
a sieve of Eratosthenes style technique, after which we can efficiently
calculate the answer. Finally, we remove the number of pairs whose elements are
at the same position and divide the answer by two to count each pair only once.

The solution works in $O(n + N \log N)$ time.

```cpp
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const int N = 1000000;

int main() {
    vector<int> mu(N + 1, 1);
    vector<int> skip(N + 1);
    for (int d = 2; d <= N; d++) {
        if (skip[d]) continue;
        for (int i = d; i <= N; i += d) {
            skip[i] = 1;
            if (i % (d * d) == 0) mu[i] = 0;
            mu[i] = -mu[i];
        }
    }

    int n;
    cin >> n;
    vector<int> count(N + 1);
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        count[x]++;
    }

    vector<int> div(N + 1);
    for (int d = 1; d <= N; d++) {
        for (int i = d; i <= N; i += d) {
            div[d] += count[i];
        }
    }

    ll answer = 0;
    for (int d = 1; d <= N; d++) {
        answer += mu[d] * (ll)div[d] * div[d];
    }
    cout << (answer - count[1]) / 2 << "\n";
}
```