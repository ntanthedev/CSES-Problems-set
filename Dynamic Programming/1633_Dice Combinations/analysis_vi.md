# 1633 - Dice Combinations

Bài toán này có thể được giải bằng *quy hoạch động*.

Gọi $\mathrm{ways}(n)$ là hàm trả lời câu hỏi "có bao nhiêu cách để đạt được
tổng $n$ bằng cách gieo xúc xắc không hoặc nhiều lần?"

Điều này hơi khác so với đề bài, vì đề bài nói "một hoặc nhiều lần". Tuy
nhiên, hai cách phát biểu này tương đương với nhau khi $n \ge 1$.

Trong trường hợp cơ sở, ta có $\mathrm{ways}(0) = 1$. Có đúng một cách để đạt
được tổng $0$, đó là không gieo xúc xắc lần nào.

Với $n$ lớn hơn, ta có thể suy ra công thức truy hồi:

Giả sử lần gieo đầu tiên cho kết quả là $v$ (từ 1 đến 6). Sau đó, quá trình
tiếp tục như khi bắt đầu, ngoại trừ $v$ được thêm vào tổng số. Do đó tổng mục
tiêu bây giờ là $n-v$, và số lượng tổ hợp được cho bởi $\mathrm{ways}(n-v)$.

Tính đến mọi giá trị $v$ khả dĩ đầu tiên, ta có

$$\mathrm{ways}(n) = \sum\_{v=1}^{6} \mathrm{ways}(n-v).$$

Lưu ý rằng các số hạng với $n-v<0$ được bỏ qua vì các trường hợp này là không
thể.

Trong lời giải dưới đây, các giá trị của hàm này được tính lặp theo thứ tự
tăng dần. Mỗi giá trị được tính trong thời gian hằng số bằng cách cộng sáu
giá trị khác, do đó độ phức tạp thời gian là $O(n)$.

```cpp
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const int M = 1000000007;

int main() {
    int n;
    cin >> n;

    vector<ll> ways(n + 1);
    ways[0] = 1;
    for (int i = 1; i <= n; ++i) {
        ways[i] = 0;
        for (int v = 1; v <= 6; ++v) {
            if (i - v >= 0) ways[i] += ways[i - v];
        }
        ways[i] %= M;
    }

    cout << ways[n] << "\n";
}
```

## Tài liệu tham khảo

* [CPHB (Competitive Programmer's Handbook)](https://cses.fi/book), Chương 7
