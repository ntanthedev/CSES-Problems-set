# 1642 - Sum of Four Values

We maintain a set that initially has all sums of the form $a\_i+a\_j$ where $i < j$. Then we go through positions $i=1,2,\dots,n$. At each position we first remove from the set all sums whose first element is $a\_i$. After that we check if we can create the sum $x$ so that the first two elements are $a\_i$ and $a\_j$ where $j < i$ and two other elements come from the set.

The algorithm works in $O(n^2 \log n)$ time because there are $O(n^2)$ set operations and each operation takes $O(\log n)$ time.

```cpp
#include <iostream>
#include <set>
#include <tuple>
#include <vector>
using namespace std;

int main() {
    int n, x;
    cin >> n >> x;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    set<tuple<int, int, int>> sums;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            sums.emplace(a[i] + a[j], i, j);
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            sums.erase({a[i] + a[j], i, j});
        }
        for (int j = i - 1; j >= 1; j--) {
            int diff = x - a[i] - a[j];
            auto it = sums.lower_bound({diff, 0, 0});
            if (it == sums.end()) continue;
            auto [sum, a, b] = *it;
            if (sum != diff) continue;
            cout << i << " " << j << " " << a << " " << b << "\n";
            return 0;
        }
    }
    cout << "IMPOSSIBLE\n";
}
```