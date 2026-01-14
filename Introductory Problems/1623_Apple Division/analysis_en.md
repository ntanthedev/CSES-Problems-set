# 1623 - Apple Division

The total number of divisions is $2^n$. Since $n$ is at most $20$, we can efficiently go through all divisions and select the optimal division where the difference of weight sums is minimum.

Each division of $n$ apples corresponds to a bit string of length $n$ where each bit determines the group an apple belongs to. For example, if the weights are $[3, 2, 7, 4, 1]$, the bit string $00101$ means that the first group has weights $[3, 2, 4]$ and the second group has weights $[7, 1]$.

```cpp
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

int main() {
    int n;
    cin >> n;
    vector<int> p(n);
    for (int i = 0; i < n; i++) cin >> p[i];

    ll diff = 1e9;
    for (int b = 0; b < (1 << n); b++) {
        ll sum1 = 0, sum2 = 0;
        for (int i = 0; i < n; i++) {
            if (b & (1 << i)) {
                sum1 += p[i];
            } else {
                sum2 += p[i];
            }
        }
        diff = min(diff, abs(sum1 - sum2));
    }

    cout << diff << "\n";
}
```