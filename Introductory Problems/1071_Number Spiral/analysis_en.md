# 1071 - Number Spiral

The following function $f(y, x)$ calculates the number in row $y$ and column $x$.

A useful observation is that the spiral consists of layers. We first calculate the current layer $m=\max(y,x)$. There are $(m-1)^2$ numbers in previous layers, and then we can calculate the numbers in the current layer. There are two cases: if $m$ is even, we go from upper-right corner to lower-left corner, and if $m$ is odd, we go from lower-left corner to upper-right corner.

```cpp
#include <iostream>
using namespace std;
using ll = long long;

ll f(ll y, ll x) {
    ll m = max(y, x);
    ll r = (m - 1) * (m - 1);
    if (m % 2 == 0) {
        r += y + m - x;
    } else {
        r += x + m - y;
    }
    return r;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        ll y, x;
        cin >> y >> x;
        cout << f(y, x) << "\n";
    }
}
```