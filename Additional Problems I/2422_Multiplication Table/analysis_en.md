# 2422 - Multiplication Table

This problem can be solved efficiently with binary search. We know that the
answer is between $1$ and $n^2$. This means that we need $O(\log n^2)=O(\log n)$
iterations of binary search.

We can check in $O(n)$ time if a number is larger or smaller than the answer by
accumulating the number of smaller or equal numbers in each row. The complexity
of the resulting algorithm is thus $O(n\log n)$.

```cpp
#include <iostream>
using namespace std;
using ll = long long;

int main() {
    ll n;
    cin >> n;

    auto check = [&](ll x) {
        ll amount = 0;
        for (int i = 1; i <= n; ++i) {
            amount += min(n, x / i);
        }
        // There are n * n numbers in the grid.
        // The index of the middle one is n * n / 2 + 1.
        return amount >= n * n / 2 + 1;
    };

    ll l = 1, r = n * n;
    while (l < r) {
        ll mid = (l + r) / 2;
        if (check(mid)) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }

    cout << l << '\n';
}
```