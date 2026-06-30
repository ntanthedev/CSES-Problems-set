# 2210 - Đếm Lưới

Chúng ta giải bài toán bằng bổ đề Burnside, phát biểu rằng số tổ hợp phân biệt là

$$\frac{1}{n} \sum\_{i=1}^n c(i)$$

khi có $n$ cách thay đổi vị trí của một tổ hợp và có $c(i)$ tổ hợp không đổi khi áp dụng cách thứ $i$.

Trong bài toán này có $4$ cách xoay lưới: $0^{\circ}$, $90^{\circ}$, $180^{\circ}$ và $270^{\circ}$. Nhiệm vụ của chúng ta là đếm các tổ hợp không đổi sau mỗi phép xoay. Trong mỗi trường hợp, ta đếm số ô vuông mà ta có thể chọn màu.

Khi $n$ chẵn, các số như sau:

* $0^{\circ}$: $n^2$
* $90^{\circ}$: $\frac{n^2}{4}$
* $180^{\circ}$: $\frac{n^2}{2}$
* $270^{\circ}$: $\frac{n^2}{4}$

Khi $n$ lẻ, các số như sau:

* $0^{\circ}$: $n^2$
* $90^{\circ}$: $\lfloor \frac{n}{2} \rfloor \lfloor \frac{n}{2} + 1 \rfloor + 1$
* $180^{\circ}$: $n \lfloor \frac{n}{2} \rfloor + \lfloor \frac{n}{2} + 1 \rfloor$
* $270^{\circ}$: $\lfloor \frac{n}{2} \rfloor \lfloor \frac{n}{2} + 1 \rfloor + 1$

```cpp
#include <iostream>
using namespace std;
using ll = long long;
const int M = 1000000007;

int power(int a, ll b) {
    if (b == 0) return 1;
    ll p = power(a, b / 2);
    p = p * p % M;
    if (b % 2 == 1) p = p * a % M;
    return p;
}

int inv(int x) {
    return power(x, M - 2);
}

int main() {
    ll n;
    cin >> n;

    ll sum = 0;
    if (n % 2 == 0) {
        sum += power(2, n * n);
        sum += power(2, n * n / 4);
        sum += power(2, n * n / 2);
        sum += power(2, n * n / 4);
    } else {
        sum += power(2, n * n);
        sum += power(2, (n / 2) * (n / 2 + 1) + 1);
        sum += power(2, n * (n / 2) + (n / 2 + 1));
        sum += power(2, (n / 2) * (n / 2 + 1) + 1);
    }
    ll answer = sum * inv(4) % M;
    cout << answer << "\n";
}
```

## Tài liệu tham khảo

* [Bổ đề Burnside (Wikipedia)](https://en.wikipedia.org/wiki/Burnside%27s_lemma)
