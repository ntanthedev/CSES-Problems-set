# 1145 - Increasing Subsequence

A straightforward approach to this problem using dynamic programming is to try
adding one more element to the longest increasing subsequence ending at every
previous element. The function $\mathrm{LIS}(i)$ describes the longest
increasing subsequence ending at position $i$. The recurrence is then

$$\mathrm{LIS}(i) =
\min\_{j < i,\ x\_j < x\_i} \mathrm{LIS}(j) + 1,$$

additionally specifying that $\mathrm{LIS}(i) = 1$ if there are no previous
smaller elements.

Checking each previous element in a loop makes for an $O(n^2)$ algorithm, which
is too slow.

The best candidate could be found faster with some kind of data structure that
stores all previous elements and the respective $\mathrm{LIS}$ values, and
allows querying the maximum $\mathrm{LIS}$ among elements that are smaller than
a given value (i.e. $x\_i$).

Both solutions presented below improve the time complexity to $O(n \log n)$.

## Solution 1 (segment tree)

A segment tree or a Fenwick tree are good options for implementing the mentioned
requiremenents. Coordinate compression is performed first on the values $x\_i$ to
fit a static size tree.

Note that the `get_max` query function always returns zero when there are no
previous smaller elements, even for `get_max(0, -1)`.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int TREE_SIZE = 1 << 18;
int tree[TREE_SIZE * 2];

void update(int i, int x) {
    i += TREE_SIZE;
    tree[i] = max(tree[i], x);
    while (i > 1) {
        i /= 2;
        tree[i] = max(tree[2 * i], tree[2 * i + 1]);
    }
}

int get_max(int l, int r) {
    int res = 0;
    l += TREE_SIZE;
    r += TREE_SIZE;
    while (l <= r) {
        if (l % 2 == 1) res = max(res, tree[l++]);
        if (r % 2 == 0) res = max(res, tree[r--]);
        l /= 2;
        r /= 2;
    }
    return res;
}

int main() {
    int n;
    cin >> n;
    vector<int> x(n);
    vector<int> sorted(n);
    for (int i = 0; i < n; ++i) {
        cin >> x[i];
        sorted[i] = x[i];
    }

    sort(sorted.begin(), sorted.end());

    for (int i = 0; i < n; ++i) {
        x[i] = lower_bound(sorted.begin(), sorted.end(), x[i]) - sorted.begin();
    }

    int result = 0;
    for (int i = 0; i < n; ++i) {
        int len = get_max(0, x[i] - 1) + 1;
        update(x[i], len);
        result = max(result, len);
    }

    cout << result << endl;
}
```

## Solution 2 (increasing array)

Properties of the $\mathrm{LIS}$ values can be utilized to design a simpler
solution using a single array and binary search.

The array $\mathrm{best}$ is maintained such that $\mathrm{best}[v]$ contains
the smallest sequence element $x\_i$ where $\mathrm{LIS}(i) = v$. No
$\mathrm{LIS}$ value is greater than $n$, so this array only needs to have size
$n + 1$.

Up to the largest $\mathrm{LIS}$ value encountered so far, the array
$\mathrm{best}$ is increasing. This is because in order for some element $x\_i$
to have $\mathrm{LIS}(i) = v > 1$, there must exist a previous smaller element
$x\_j$, $j < i$ such that $\mathrm{LIS}(j) = v-1$. Therefore $\mathrm{best}[v-1]$
is at most $x\_j$.

Since the array is increasing, binary search can be used to find the largest
$\mathrm{LIS}$ value $v$ which still has a corresponding element
$\mathrm{best}[v] = x\_j$ smaller than $x\_i$.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> x(n);
    for (int i = 0; i < n; ++i) cin >> x[i];

    vector<int> best(n + 1);
    best[0] = 0;
    int result = 0;
    for (int i = 0; i < n; ++i) {
        int len = lower_bound(best.begin(), best.begin() + result + 1, x[i]) -
                  best.begin();
        if (len > result) {
            result = len;
            best[len] = x[i];
        } else {
            best[len] = min(best[len], x[i]);
        }
    }

    cout << result << endl;
}
```

## References

* [CPHB (Competitive Programmer's Handbook)](https://cses.fi/book), Chapter 7,
  Longest increasing subsequence
* [CP-Algorithms, Longest increasing subsequence](https://cp-algorithms.com/sequences/longest_increasing_subsequence.html)