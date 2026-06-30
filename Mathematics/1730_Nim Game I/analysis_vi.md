# 1730 - Nim Game I

Trong bài toán này, chúng ta được cho một trạng thái Nim và nhiệm vụ là kiểm tra xem đó là vị thế thắng hay thua. Để làm điều đó, ta tính tổng xor của kích thước các đống.

Nếu tổng khác không, ta đang ở vị thế thắng vì luôn có một nước đi làm cho tổng bằng không.

Nếu tổng bằng không, ta đang ở vị thế thua vì mọi nước đi đều làm thay đổi tổng thành khác không.

```cpp
#include <iostream>
using namespace std;

int main() {
    int t;
    cin >> t;

    for (int ti = 1; ti <= t; ti++) {
        int n;
        cin >> n;
        int sum = 0;
        for (int i = 1; i <= n; i++) {
            int x;
            cin >> x;
            sum ^= x;
        }
        cout << (sum != 0 ? "first" : "second") << "\n";
    }
}
```

## Tài liệu tham khảo

* [Nim (Wikipedia)](https://en.wikipedia.org/wiki/Nim)
