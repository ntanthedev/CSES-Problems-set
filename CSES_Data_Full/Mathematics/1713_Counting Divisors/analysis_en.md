# 1713 - Counting Divisors

## Solution 1

The following function `count` returns the number of divisors for $x$. It checks
every integer $k$ between $1$ and $\sqrt x$. If $x$ is divisible by $k$, we have
found one divisor. In addition, if $k \neq x/k$, we have found another divisor
$x/k$.

The solution works in $O(n \sqrt N)$ time where $N$ is the upper bound for $x$.

```cpp
#include <iostream>
#include <vector>
using namespace std;

int count(int x) {
    int c = 0;
    for (int k = 1; k * k <= x; k++) {
        if (x % k) continue;
        c++;
        if (k != x / k) c++;
    }
    return c;
}

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        cout << count(x) << "\n";
    }
}
```

## Solution 2

This solution works in a similar manner to the sieve of Eratosthenes. It
creates a vector `count` that will contain the number of divisors for each
number $x$ between $1$ and $N$.

Creating the vector takes $O(N \log N)$ time because the total number of steps
is bounded by the harmonic sum

$$N + N/2 + N/3 + \dots = O(N \log N).$$

Thus, the solution works in $O(N \log N + n)$ time.

```cpp
#include <iostream>
#include <vector>
using namespace std;
const int N = 1000000;

int main() {
    vector<int> count(N + 1);
    for (int i = 1; i <= N; i++) {
        for (int j = i; j <= N; j += i) {
            count[j]++;
        }
    }

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        cout << count[x] << "\n";
    }
}
```