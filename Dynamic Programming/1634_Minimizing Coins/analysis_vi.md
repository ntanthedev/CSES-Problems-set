# 1634 - Minimizing Coins

Hàm $\mathrm{amount}(x)$ trả lời câu hỏi "cần tối thiểu bao nhiêu đồng xu để
tạo thành tổng $n$?"

$\mathrm{amount}(0) = 0$ vì không cần đồng xu nào.

Với $x$ lớn hơn, chọn đồng xu mà mang lại tổng số lượng ít nhất cho phần còn
lại của tổng. Đồng xu được chọn này được tính bằng cách cộng thêm một vào giá
trị tối thiểu.

$$\mathrm{amount}(x) = 1 + \min\_{c\in\mathrm{coins}} \mathrm{amount}(x - c)$$

Nếu không có đồng xu hợp lệ nào $c \le x$, giá trị được đặt thành $\infty$.

Với cách cài đặt quy hoạch động lặp, độ phức tạp thời gian là $O(nx)$,
vì mỗi đồng xu phải được kiểm tra cho mọi tổng số tiền đến $x$. Có vẻ như
điều này quá chậm, nhưng $10^8$ phép tính vẫn nằm trong giới hạn thời gian,
tùy thuộc vào ngôn ngữ bạn chọn.

```cpp
#include <iostream>
#include <vector>
using namespace std;
const int INF = 1e9;

int main() {
    int n, x;
    cin >> n >> x;

    vector<int> c(n);
    for (int j = 0; j < n; ++j) {
        cin >> c[j];
    }

    vector<int> amount(x + 1);
    amount[0] = 0;
    for (int i = 1; i <= x; ++i) {
        amount[i] = INF;
        for (int j = 0; j < n; ++j) {
            if (i - c[j] >= 0) {
                amount[i] = min(amount[i], amount[i - c[j]] + 1);
            }
        }
    }

    int answer = amount[x];
    if (answer == INF) answer = -1;
    cout << answer << "\n";
}
```

## Tài liệu tham khảo

* [CPHB (Competitive Programmer's Handbook)](https://cses.fi/book), Chương 7
