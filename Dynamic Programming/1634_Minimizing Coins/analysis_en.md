# 1634 - Minimizing Coins

The function $\mathrm{amount}(x)$ answers the question "what is the minimum
amount of coins needed to form the sum $n$?"

$\mathrm{amount}(0) = 0$ since no coins are needed.

For larger $x$, choose the coin which results in the smallest total amount for
the rest of the sum. This chosen coin is accounted for by adding one to the minimum.

$$\mathrm{amount}(x) = 1 + \min\_{c\in\mathrm{coins}} \mathrm{amount}(x - c)$$

If there are no valid coins $c \le x$, the value is set to $\infty$ instead.

With an iterative memoizing implementation, the time complexity is $O(nx)$,
since each coin has to be checked for each total sum up to $x$. It may seem
that this is too slow, but an order of $10^8$ operations still fits well in the
time limit, depending on your choice of language.

```cpp
#include <iostream>
#include <vector>
using namespace std;
const int INF = 1e9;

int main() {
    int n, x;
    cin >> n >> x;

    vector<int> c(n);
    for (int j = 0; j < n; ++j) {
        cin >> c[j];
    }

    vector<int> amount(x + 1);
    amount[0] = 0;
    for (int i = 1; i <= x; ++i) {
        amount[i] = INF;
        for (int j = 0; j < n; ++j) {
            if (i - c[j] >= 0) {
                amount[i] = min(amount[i], amount[i - c[j]] + 1);
            }
        }
    }

    int answer = amount[x];
    if (answer == INF) answer = -1;
    cout << answer << "\n";
}
```

## References

* [CPHB (Competitive Programmer's Handbook)](https://cses.fi/book), Chapter 7