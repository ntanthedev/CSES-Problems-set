# 3396 - Số Nguyên Tố Tiếp Theo

Gọi $\pi(n)$ là số lượng số nguyên tố từ $1$ đến $n$. Ta biết rằng
$$\pi(n) \approx \frac{n}{\log n}$$
và trong thực tế, khoảng cách giữa hai số nguyên tố liên tiếp không quá lớn. Vì lý do này, ta có thể giải bài toán chỉ bằng cách duyệt qua các số lớn hơn $n$ cho đến khi tìm được số nguyên tố đầu tiên.

Khoảng cách nguyên tố lớn nhất từ $1$ đến $10^{12}$ là $540$, xảy ra giữa hai số nguyên tố $738832927927$ và $738832928467$.

```cpp
#include <iostream>
using namespace std;
using ll = long long;

bool prime(ll n) {
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (ll x = 3; x * x <= n; x += 2) {
        if (n % x == 0) return false;
    }
    return true;
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        ll n;
        cin >> n;
        n++;
        while (!prime(n)) n++;
        cout << n << "\n";
    }
}
```
