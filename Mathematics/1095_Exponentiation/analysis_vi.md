# 1095 - Lũy thừa

Một cách đơn giản để tính giá trị $a^b \bmod m$ là dùng một vòng lặp gồm $b$ bước:

```cpp
for (int i = 0; i < b; i++) {
    p = p * a % m;
}
```

Giải pháp như vậy cần $O(b)$ thời gian và sẽ quá chậm. Tuy nhiên, ta có thể tạo ra một giải pháp hiệu quả hơn với $O(\log b)$ thời gian bằng cách sử dụng tính chất $a^b = a^{b/2} a^{b/2}$ khi $b$ chẵn. Sử dụng công thức này, ta chỉ cần tính $a^{b/2}$ một lần và tái sử dụng kết quả.

## Cách giải 1 (đệ quy)

Gọi $\textrm{power}(a,b,m) = a^b \bmod m$. Nếu $b=0$, đáp án là $1 \bmod m$. Ngược lại, đầu tiên ta tính $p = \textrm{power}(a,\lfloor b/2 \rfloor,m)$. Nếu $b$ chẵn, đáp án là $p^2 \bmod m$, và nếu $b$ lẻ, đáp án là $p^2 a \bmod m$.

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
        int a, b;
        cin >> a >> b;
        cout << power(a, b, 1e9 + 7) << "\n";
    }
}
```

## Cách giải 2 (lặp)

Ta cũng có thể cài đặt thuật toán một cách lặp, hiệu quả hơn trong thực tế. Đoạn code sau duyệt qua biểu diễn nhị phân của $b$ và lưu lũy thừa tương ứng của $a$ trong $f$, nghĩa là, với mỗi lũy thừa của $2^k$, $f$ bằng $a^{2^k}$.

```cpp
#include <iostream>
using namespace std;
using ll = long long;

int power(int a, int b, int m) {
    ll p = 1 % m;
    ll f = a;
    while (b) {
        if (b & 1) p = p * f % m;
        f = f * f % m;
        b /= 2;
    }
    return p;
}

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int a, b;
        cin >> a >> b;
        cout << power(a, b, 1e9 + 7) << "\n";
    }
}
```

## Tài liệu tham khảo

* [Binary Exponentiation (CP-algorithms)](https://cp-algorithms.com/algebra/binary-exp.html)
