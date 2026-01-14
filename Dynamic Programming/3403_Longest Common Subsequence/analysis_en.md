# 3403 - Longest Common Subsequence

We use dynamic programming to calculate the longest common subsequence length for all prefix pairs of the given arrays.

Let $\textrm{lcs}[i][j]$ denote the longest common subsequence length for the sequences $[a\_1,a\_2,\dots,a\_i]$ and $[b\_1,b\_2,\dots,b\_j]$. If $a\_i=b\_j$, then $\textrm{lcs}[i][j] = \textrm{lcs}[i-1][j-1]+1$ because the last elements of the sequences can be matched. Otherwise, $\textrm{lcs}[i][j] = \max(\textrm{lcs}[i-1][j], \textrm{lcs}[i][j-1])$, which corresponds to removing the last element either from the first or the second sequence.

Finally, $\textrm{lcs}[n][m]$ gives the longest common subsequence length and we can construct an example of such a subsequence by tracking the dynamic programming calculation path.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> a(n + 1), b(m + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= m; i++) {
        cin >> b[i];
    }

    vector<vector<int>> lcs(n + 1, vector<int>(m + 1));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i] == b[j]) {
                lcs[i][j] = lcs[i - 1][j - 1] + 1;
            } else {
                lcs[i][j] = max(lcs[i - 1][j], lcs[i][j - 1]);
            }
        }
    }

    cout << lcs[n][m] << "\n";

    vector<int> result;
    while (lcs[n][m] > 0) {
        if (a[n] == b[m]) {
            result.push_back(a[n]);
            n--;
            m--;
        } else if (lcs[n - 1][m] == lcs[n][m]) {
            n--;
        } else {
            m--;
        }
    }

    reverse(result.begin(), result.end());
    for (auto x : result) {
        cout << x << " ";
    }
    cout << "\n";
}
```

## References

* [Longest common subsequence (Wikipedia)](https://en.wikipedia.org/wiki/Longest_common_subsequence)