# 1638 - Grid Paths I

In order to use dynamic programming, we split this problem into subproblems where instead
of counting the amount of paths to the lower-right square, this quantity is computed for
every square in the grid.

The function $\mathrm{paths}(i, j)$ expresses how many valid paths there are from the upper-left
square to the square at row $i$ and column $j$. 0-indexing is used in this solution.

The answer is $\mathrm{paths}(n-1, n-1)$.

If the square $(i, j)$ has a trap in it, there are no valid paths into it. This also applies
to the upper-left square, which would otherwise implicitly have one path.

Any path ending at square $(i, j) \neq (0, 0)$ must have come from either $(i-1, j)$, the square above, or $(i, j-1)$, the square to the left.

$$\mathrm{paths}(i, j) =
\begin{cases}
0 & \text{if trap} \\
1 & \text{if } i=j=0 \\
\mathrm{paths}(i-1, j) + \mathrm{paths}(i, j-1) & \text{otherwise}
\end{cases}$$

One suitable order for iteratively computing this function is to iterate over
rows from top to bottom and each row from left to right.

```cpp
#include <iostream>
#include <vector>
using namespace std;
const int M = 1000000007;

int main() {
    int n;
    cin >> n;

    vector<string> grid(n);
    for (int i = 0; i < n; ++i) {
        cin >> grid[i];
    }

    vector<vector<int>> paths(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == '*') {
                paths[i][j] = 0;
            } else {
                paths[i][j] = i == 0 && j == 0;
                if (i) paths[i][j] += paths[i - 1][j];
                if (j) paths[i][j] += paths[i][j - 1];
                paths[i][j] %= M;
            }
        }
    }

    cout << paths[n - 1][n - 1] << "\n";
}
```

## References

* [CPHB (Competitive Programmer's Handbook)](https://cses.fi/book), Chapter 7.3, Paths in a grid