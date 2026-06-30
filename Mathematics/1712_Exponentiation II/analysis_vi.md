# 1712 - Luỹ thừa II

Nhiệm vụ của chúng ta là tính giá trị của $a^{b^c}$ với số mũ $b^c$ có thể
rất lớn. Để giải quyết bài toán, ta sử dụng định lý nhỏ Fermat:

$$a^{m-1} \bmod m = 1$$

khi $m$ là số nguyên tố và $a$ không chia hết cho $m$. Do đó,

$$a^{b^c} \bmod m = a^{b^c \, \bmod \, (m-1)} \bmod m$$

điều này cho phép ta tính kết quả một cách hiệu quả.

```cpp
#include <iostream>
using namespace std;
using ll = long long;

int power(int a, int b, int m) {
    if (b == 0) return 1 % m;
    ll p = power(a, b / 2, m);
    p = p * p % m;
    if (b % 2 == 1) p = p * a % m;
    return p;
}

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        cout << power(a, power(b, c, 1e9 + 6), 1e9 + 7) << "\n";
    }
}
```

## Tài liệu tham khảo

* [Định lý nhỏ Fermat (Wikipedia)](https://en.wikipedia.org/wiki/Fermat%27s_little_theorem)
