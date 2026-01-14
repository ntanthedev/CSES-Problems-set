# 1618 - Trailing Zeros

The number of trailing zeros in a number equals the number of times we can divide it by $10$. Since $10=2 \cdot 5$, we should focus on factors $2$ and $5$.

In a factorial, the number of factors $5$ is always smaller than the number of factors $2$, and the number of trailing zeros equals the number of factors $5$. For example, $20! = 2^{18} \cdot 3^8 \cdot 5^4 \cdot 7^2 \cdot 11 \cdot 13 \cdot 17 \cdot 19$, so factor $2$ appears $18$ times and factor $5$ appears $4$ times. Thus, $20!$ has $4$ trailing zeros.

The following code calculates the number of factors $5$ in $n!$ by dividing $n$ by $5,5^2,5^3$ etc.

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;

    int ans = 0;
    for (int i = 5; i <= n; i *= 5) {
        ans += n / i;
    }
    cout << ans << "\n";
}
```