# 1142 - Advertisement

An important observation is that an optimal advertisement will always be bounded
from above, by at least one fence. We may loop through the fences and consider
each one as this bounding fence. The height of the corresponding advertisement
will equal to the height of the current fence. Sideways we will make the ad as
large as possible, and it will span each adjacent fence that is not lower than
the current one.

We will compute two positions for each fence: the indices of the previous and
next fences that are lower in height. This may be done in linear time, making
the time complexity of the solution $O(n)$.

```cpp
#include <iostream>
using namespace std;
using ll = long long;

const int N = 200002;
int k[N];
int prev_lower[N], next_lower[N];

int main() {
    int n;
    cin >> n;

    for (int i = 1; i <= n; ++i) {
        cin >> k[i];
    }

    for (int i = 1; i <= n; ++i) {
        prev_lower[i] = i - 1;
        while (prev_lower[i] >= 0 && k[prev_lower[i]] >= k[i]) {
            prev_lower[i] = prev_lower[prev_lower[i]];
        }
    }

    for (int i = n; i >= 1; --i) {
        next_lower[i] = i + 1;
        while (next_lower[i] <= n && k[next_lower[i]] >= k[i]) {
            next_lower[i] = next_lower[next_lower[i]];
        }
    }

    ll ans = 0;
    for (int i = 1; i <= n; ++i) {
        ans = max(ans, 1ll * (next_lower[i] - prev_lower[i] - 1) * k[i]);
    }

    cout << ans << '\n';
}
```