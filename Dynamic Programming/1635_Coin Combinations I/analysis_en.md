# 1635 - Coin Combinations I

Define a function $\mathrm{ways}(x)$ to answer the question in the task
statement: "in how many ways can a sum $x$ be produced in the given money
system?"

As can be seen from the example, any coin may be chosen multiple times and
different orders are counted separately.

Base case: $\mathrm{ways}(0) = 1$.

Larger $x$: Choose any available coin with value $c$. The remaining sum is
$x - c$.

$$\mathrm{ways}(x) = \sum\_{c\in\mathrm{coins}} \mathrm{ways}(x - c)$$

Time complexity is $O(nx)$ since each coin has to be iterated over for each
sum $x$.

Care should be taken to apply the modulus after each addition to avoid
overflows, especially if using `int` instead of `long long`.

```cpp
#include <iostream>
#include <vector>
using namespace std;
const int M = 1000000007;

int main() {
    int n, x;
    cin >> n >> x;

    vector<int> c(n);
    for (int j = 0; j < n; ++j) {
        cin >> c[j];
    }

    vector<int> ways(x + 1);
    ways[0] = 1;
    for (int i = 1; i <= x; ++i) {
        ways[i] = 0;
        for (int j = 0; j < n; ++j) {
            if (i - c[j] >= 0) {
                ways[i] = (ways[i] + ways[i - c[j]]) % M;
            }
        }
    }

    cout << ways[x] << "\n";
}
```

## References

* [CPHB (Competitive Programmer's Handbook)](https://cses.fi/book), Chapter 7