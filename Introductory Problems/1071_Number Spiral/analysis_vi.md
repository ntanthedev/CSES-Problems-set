# 1071 - Xoắn ốc số

Hàm $f(y, x)$ sau đây tính số ở hàng $y$ và cột $x$.

Một nhận xét hữu ích là xoắn ốc bao gồm các lớp. Đầu tiên ta tính lớp hiện tại $m=\max(y,x)$. Có $(m-1)^2$ số trong các lớp trước đó, và sau đó ta có thể tính các số trong lớp hiện tại. Có hai trường hợp: nếu $m$ là chẵn, ta đi từ góc trên bên phải xuống góc dưới bên trái, và nếu $m$ là lẻ, ta đi từ góc dưới bên trái lên góc trên bên phải.

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
