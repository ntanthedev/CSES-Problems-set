# 1650 - Truy vấn Xor trên đoạn

Một mảng tổng tiền tố (xor) đơn giản là đủ cho bài toán này.

Lưu ý, phép xor có một tính chất thú vị:
Xor là nghịch đảo của chính nó. Nghĩa là,
với mọi $x$ ta luôn có $x \oplus x = 0$, trong đó
$\oplus$ ký hiệu phép xor.
Điều này trái ngược với, ví dụ, phép cộng
mà phép nghịch đảo của nó là phép trừ.

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;

    vector<int> x(n);
    for (int &t : x) {
        cin >> t;
    }

    vector<int> prefix_sums(n + 1);
    for (int i = 0; i < n; ++i) {
        prefix_sums[i + 1] = prefix_sums[i] ^ x[i];
    }

    for (int qi = 0; qi < q; ++qi) {
        int l, r;
        cin >> l >> r;
        l--;
        // In ra tổng xor cho đoạn [l, r)
        cout << (prefix_sums[r] ^ prefix_sums[l]) << '\n';
    }
}
```
