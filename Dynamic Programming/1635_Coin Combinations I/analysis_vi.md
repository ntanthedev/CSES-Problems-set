# 1635 - Tổ hợp xu I

Định nghĩa hàm $\mathrm{ways}(x)$ để trả lời câu hỏi trong đề bài: "có bao nhiêu cách để tạo ra tổng $x$ trong hệ thống tiền tệ đã cho?"

Như có thể thấy từ ví dụ, mỗi đồng xu có thể được chọn nhiều lần và các thứ tự khác nhau được tính riêng biệt.

Trường hợp cơ sở: $\mathrm{ways}(0) = 1$.

Với $x$ lớn hơn: Chọn một đồng xu bất kỳ có giá trị $c$. Phần còn lại là $x - c$.

$$\mathrm{ways}(x) = \sum\_{c\in\mathrm{coins}} \mathrm{ways}(x - c)$$

Độ phức tạp thời gian là $O(nx)$ vì mỗi đồng xu phải được duyệt qua cho mỗi tổng $x$.

Cần chú ý áp dụng phép modulo sau mỗi lần cộng để tránh tràn số, đặc biệt nếu dùng `int` thay vì `long long`.

```cpp
#include <iostream>
#include <vector>
using namespace std;
const int M = 1000000007;

int main() {
    int n, x;
    cin >> n >> x;

    vector<int> c(n);
    for (int j = 0; j < n; ++j) {
        cin >> c[j];
    }

    vector<int> ways(x + 1);
    ways[0] = 1;
    for (int i = 1; i <= x; ++i) {
        ways[i] = 0;
        for (int j = 0; j < n; ++j) {
            if (i - c[j] >= 0) {
                ways[i] = (ways[i] + ways[i - c[j]]) % M;
            }
        }
    }

    cout << ways[x] << "\n";
}
```

## Tài liệu tham khảo

* [CPHB (Sổ tay lập trình viên)](https://cses.fi/book), Chương 7
