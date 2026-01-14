# 1745 - Money Sums

To solve the problem using dynamic programming, define the function
$\mathrm{possible}(i, s)$ to describe whether it is possible to form the money sum
$s$ using some of the first $i$ coins.

When considering the next coin, we can either choose it and add its value to the
sum, or not and use only previous coins.

$$\mathrm{possible}(i, s) = \mathrm{possible}(i-1, s) \vee
\mathrm{possible}(i-1, s - x\_i)$$

The symbol $\vee$ denotes the boolean OR operation.

When no coins have yet been considered, the only possible sum is $0$. This
shouldn't be printed in this problem though.

$$\mathrm{possible}(0, s) =
\begin{cases}
\text{true} & \text{if } s = 0 \\
\text{false} & \text{otherwise}
\end{cases}$$

Since the recurrence only references computed values of the previous coin, it
is enough to share a one-dimensional array as long as it is iterated in a
suitable order.

The time complexity of this solution is $O(n^2 x)$, where $x$ is the maximum
value of each coin, as any sum of coins $s \le nx$.

```cpp
#include <iostream>
using namespace std;
const int X = 100000;

bool possible[X + 1];

int main() {
    int n;
    cin >> n;

    possible[0] = true;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        for (int s = X; s >= x; --s) {
            possible[s] |= possible[s - x];
        }
    }

    int k = 0;
    for (int s = 1; s <= X; ++s) {
        k += possible[s];
    }
    cout << k << "\n";
    for (int s = 1; s <= X; ++s) {
        if (possible[s]) cout << s << " ";
    }
    cout << "\n";
}
```

## References

* [CPHB (Competitive Programmer's Handbook)](http://cses.fi/book), Chapter 7,
  Knapsack problems