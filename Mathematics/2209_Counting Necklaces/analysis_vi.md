# 2209 - Đếm Vòng Cổ

Chúng ta giải bài toán bằng bổ đề Burnside, phát biểu rằng số tổ hợp phân biệt là

$$\frac{1}{n} \sum\_{i=1}^n c(i)$$

khi có $n$ cách thay đổi vị trí của một tổ hợp và có $c(i)$ tổ hợp không đổi khi áp dụng cách thứ $i$.

Trong bài toán này có $n$ cách xoay vòng cổ: ta có thể xoay $0,1,\dots,n-1$ bước. Số tổ hợp không đổi là

$$m^{\gcd(i,n)}$$

vì có một khối lặp gồm $\gcd(i,n)$ hạt và có $m$ cách chọn màu cho mỗi hạt trong khối.

```cpp
#include <iostream>
using namespace std;
using ll = long long;
const int M = 1000000007;

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int power(int a, int b) {
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
    int n, m;
    cin >> n >> m;

    ll sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += power(m, gcd(i, n));
        sum %= M;
    }
    ll answer = sum * inv(n) % M;
    cout << answer << "\n";
}
```

## Tài liệu tham khảo

* [Bổ đề Burnside (Wikipedia)](https://en.wikipedia.org/wiki/Burnside%27s_lemma)
