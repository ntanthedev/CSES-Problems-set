# 1661 - Subarray Sums II

Let $s(i)$ denote the prefix sum $a\_1+a\_2+\dots+a\_i$. Using this function, we can calculate any subarray sum as follows:
$$a\_l+a\_{l+1}+\dots+a\_r = s(r) - s(l-1)$$
To calculate the number of subarrays that end at position $i$ and have sum $x$, we should find all values $j<i$ for which
$$s(i) - s(j) = x$$
which is equivalent to
$$s(j) = s(i) - x.$$
We can store the number of times we have seen each prefix sum and then efficiently find the number of subarrays. The following code uses a map structure to count the prefix sums and works in $O(n \log n)$ time.

```cpp
#include <iostream>
#include <map>
using namespace std;
using ll = long long;

int main() {
    int n, x;
    cin >> n >> x;

    map<ll, int> sums;
    sums[0] = 1;

    ll sum = 0;
    ll count = 0;
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        sum += a;
        count += sums[sum - x];
        sums[sum]++;
    }

    cout << count << "\n";
}
```