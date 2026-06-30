# 1070 - Hoán vị

Trường hợp $n=1$ rất đơn giản và không có lời giải cho $n=2$ và $n=3$. Nếu $n \ge 4$, luôn tồn tại lời giải. Đoạn mã sau sử dụng một cách xây dựng cũng hoạt động với $n=4$. Một số cách xây dựng khác yêu cầu xử lý riêng trường hợp $n=4$.

```cpp
#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    if (n == 1) {
        cout << "1\n";
        return 0;
    }
    if (n == 2 || n == 3) {
        cout << "NO SOLUTION\n";
        return 0;
    }
    for (int i = n / 2; i >= 1; i--) {
        cout << i << " " << i + n / 2 << " ";
    }
    if (n % 2 == 1) cout << n << " ";
    cout << "\n";
}
```
