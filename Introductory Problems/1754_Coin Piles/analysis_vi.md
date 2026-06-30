# 1754 - Hai đống xu

Vì mỗi lượt lấy đi ba đồng xu, tổng số đồng xu phải chia hết cho ba.

Mỗi lượt lấy ít nhất một đồng xu từ mỗi đống, do đó số đồng xu trong một đống không được vượt quá hai lần số đồng xu trong đống kia.

Nếu các điều kiện trên được thỏa mãn, ta luôn có thể làm rỗng các đống bằng thuật toán tham lam lấy hai đồng xu từ đống có nhiều xu hơn. Nếu cả hai đống có cùng số xu, ta có thể chọn tùy ý.

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int t;
    cin >> t;

    while (t--) {
        int a, b;
        cin >> a >> b;
        if ((a + b) % 3 == 0 && a <= 2 * b && b <= 2 * a) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}
```
