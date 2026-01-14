# 1639 - Edit Distance

Edit distance can be computed with dynamic programming. We will denote the input
strings by $a$ and $b$.

Let $\gdef \d {{\mathrm{distance}}} \d(i, j)$ describe the edit distance between
the prefix of $a$ with length $i$ and the prefix of $b$ with length $j$.

As base cases, $\d(0, x) = \d(x, 0) = x$ because all $x$ characters have to be
inserted or removed, as the other string is empty.

Otherwise we have

$$\d(i, j) = \min
\begin{cases}
\d(i, j-1) + 1 \\
\d(i-1, j) + 1 \\
\d(i-1, j-1) + [a[i-1] \ne b[j-1]],
\end{cases}$$

where $[a[i-1] \ne b[j-1]]$ is $0$ if the 0-indexed characters are equal, and
$1$ otherwise. The options correspond to, respectively, inserting the character
$b[j-1]$, removing the character $a[i-1]$, and reusing or replacing $a[i-1]$
with $b[j-1]$ in one operation.

The correctness of this recurrence is justified by the fact that there exists an
optimal sequence of edit operations, where all edits are applied in
left-to-right order. Paths in the dynamic programming array that follow the
transitions in the recurrence correspond to such edit sequences.

The time complexity of this solution is $O(nm)$.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    string a, b;
    cin >> a >> b;
    int n = a.size(), m = b.size();

    vector<vector<int>> distance(n + 1, vector<int>(m + 1));
    for (int i = 0; i <= n; ++i) {
        distance[i][0] = i;
    }
    for (int j = 0; j <= m; ++j) {
        distance[0][j] = j;
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            distance[i][j] = min({
                distance[i][j - 1] + 1,
                distance[i - 1][j] + 1,
                distance[i - 1][j - 1] + (a[i - 1] != b[j - 1]),
            });
        }
    }

    cout << distance[n][m] << "\n";
}
```

## References

* [CPHB (Competitive Programmer's Handbook)](https://cses.fi/book), Chapter 7.5,
  Edit distance
* [Edit distance (Wikipedia)](https://en.wikipedia.org/wiki/Edit_distance)