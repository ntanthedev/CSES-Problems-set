# 1158 - Book Shop

Bài toán này là một dạng bài toán cái túi (knapsack) có thể giải hiệu quả
bằng quy hoạch động nhờ vào các giới hạn.

Gọi $\mathrm{total}(i, j)$ là tổng số trang tối đa có thể đạt được bằng cách
chi tối đa $j$ tiền để mua các cuốn sách với chỉ số từ $1$ đến $i$.

Trong trường hợp cơ sở, $\mathrm{total}(0, j) = 0$ với mọi $j$. Không có cuốn
sách nào được mua, do đó không có trang nào có thể thu được.

Ngược lại, ta có thể chọn mua sách $i$ hoặc không. Nếu mua, sẽ còn $j -
h\_i$ tiền.

$$\mathrm{total}(i, j) =
\max \{ \mathrm{total}(i-1, j), s\_i + \mathrm{total}(i-1, j - h\_i) \}$$

Vì công thức đệ quy chỉ tham chiếu đến $i-1$ trước đó, toàn bộ hàm không cần
lưu trữ trong một mảng. Tuy nhiên, để tránh mua cùng một cuốn sách nhiều lần,
vòng lặp trong phải chạy theo chiều giảm dần. Truy cập `total[j - h[i]]` sẽ
cho giá trị cũ từ lần lặp $i-1$, vì các chỉ số $j$ nhỏ hơn chưa được xử lý.

Độ phức tạp thời gian của lời giải là $O(nx)$.

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, x;
    cin >> n >> x;

    vector<int> h(n), s(n);
    for (int i = 0; i < n; ++i) cin >> h[i];
    for (int i = 0; i < n; ++i) cin >> s[i];

    vector<int> total(x + 1);
    for (int i = 0; i < n; ++i) {
        for (int j = x; j >= h[i]; --j) {
            total[j] = max(total[j], s[i] + total[j - h[i]]);
        }
    }

    cout << total[x] << "\n";
}
```

## Tài liệu tham khảo

* [Bài toán cái túi (Wikipedia)](https://en.wikipedia.org/wiki/Knapsack_problem)
* [CPHB (Competitive Programmer's Handbook)](https://cses.fi/book), Chương 7.4, Các bài toán cái túi
