# 1068 - Thuật toán kỳ lạ

Đoạn mã dưới đây cài đặt thuật toán này. Lưu ý rằng các số trong dãy có thể lớn hơn nhiều so với giá trị $n$ ban đầu. Với $n \le 10^6$, việc sử dụng kiểu số nguyên 64-bit là đủ.

```cpp
#include <iostream>
using namespace std;
using ll = long long;

int main() {
    ll n;
    cin >> n;
    while (true) {
        cout << n << " ";
        if (n == 1) break;
        if (n % 2 == 0) {
            n = n / 2;
        } else {
            n = 3 * n + 1;
        }
    }
    cout << "\n";
}
```

## Tài liệu tham khảo

* [Giả thuyết Collatz (Wikipedia)](https://en.wikipedia.org/wiki/Collatz_conjecture)