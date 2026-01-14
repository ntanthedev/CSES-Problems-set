# 1085 - Array Division

The following function `check` is given a value $s$ and it checks if we can divide the array into $k$ subarrays so that the sum of each subarray is at most $s$. The function goes through the array from left to right and greedily maximizes the size of each subarray.

We can efficiently solve the problem by combining binary search and the above function. We find the maximum value $s$ such that it is not possible to create the subarrays. Then the answer to the problem is $s+1$.

The algorithm works in $O(n \log M)$ time where $M$ is the maximum possible answer. In the following code $M=10^{18}$ which works for the bounds given in the problem statement.

```cpp
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> x(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }

    auto check = [&](ll s) {
        int p = 1;
        ll c = 0;
        for (int i = 0; i < n; i++) {
            if (x[i] > s) return false;
            c += x[i];
            if (c > s) {
                p++;
                c = x[i];
            }
        }
        return p <= k;
    };

    ll s = 0;
    for (ll b = 1e18; b >= 1; b /= 2) {
        while (!check(s + b)) s += b;
    }
    cout << s + 1 << "\n";
}
```