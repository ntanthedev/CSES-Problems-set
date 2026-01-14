# 1158 - Book Shop

This problem is a type of knapsack problem which can be solved efficiently
with dynamic programming because of the limits.

Let $\mathrm{total}(i, j)$ equal the maximum total amount of pages obtainable
by spending at most $j$ money buying only books with indices $1 \dots i$.

As the base case, $\mathrm{total}(0, j) = 0$ for all $j$. No books can be
bought, so zero pages can be obtained.

Otherwise, we can either choose to buy book $i$ or not. If it is bought, $j -
h\_i$ money will remain.

$$\mathrm{total}(i, j) =
\max \{ \mathrm{total}(i-1, j), s\_i + \mathrm{total}(i-1, j - h\_i) \}$$

Since the recursion only references the previous $i$, the whole function does
not need to be stored in an array. To prevent buying the same book multiple
times, however, the inner for loop has to run in reverse. Referencing
`total[j - h[i]]` gives the old value from iteration $i-1$, because smaller
indices $j$ have not yet been processed.

The time complexity of the solution is $O(nx)$.

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, x;
    cin >> n >> x;

    vector<int> h(n), s(n);
    for (int i = 0; i < n; ++i) cin >> h[i];
    for (int i = 0; i < n; ++i) cin >> s[i];

    vector<int> total(x + 1);
    for (int i = 0; i < n; ++i) {
        for (int j = x; j >= h[i]; --j) {
            total[j] = max(total[j], s[i] + total[j - h[i]]);
        }
    }

    cout << total[x] << "\n";
}
```

## References

* [Knapsack problem (Wikipedia)](https://en.wikipedia.org/wiki/Knapsack_problem)
* [CPHB (Competitive Programmer's Handbook)](https://cses.fi/book), Chapter 7.4, Knapsack problems