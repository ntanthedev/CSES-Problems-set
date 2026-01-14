# 1662 - Subarray Divisibility

Let $s(i)$ denote the prefix sum $a\_1+a\_2+\dots+a\_i$. The sum of a subarray $a\_l,a\_{l+1},\dots,a\_r$ is divisible by $n$ exactly when
$$s(r) \bmod n = s(l-1) \bmod n,$$
so we can solve the problem by counting how many times we have seen each prefix sum modulo $n$.

Since each prefix sum modulo $n$ is between $0$ and $n-1$, we can use a vector to store the counters. Note that some care is needed in modulo calculation because the sum can be negative. The algorithm works in $O(n)$ time.

```cpp
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

int main() {
    int n;
    cin >> n;

    vector<int> sums(n);
    sums[0] = 1;

    ll sum = 0;
    ll count = 0;
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        sum += a;
        sum = (sum % n + n) % n;
        count += sums[sum];
        sums[sum]++;
    }

    cout << count << "\n";
}
```