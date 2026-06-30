# 1745 - Tổng tiền

Để giải bài toán bằng quy hoạch động, ta định nghĩa hàm
$\mathrm{possible}(i, s)$ mô tả liệu có thể tạo thành tổng tiền
$s$ bằng cách dùng một số đồng xu trong số $i$ đồng xu đầu tiên hay không.

Khi xét đồng xu tiếp theo, ta có thể chọn nó và cộng mệnh giá của nó vào
tổng, hoặc không chọn và chỉ dùng các đồng xu trước đó.

$$\mathrm{possible}(i, s) = \mathrm{possible}(i-1, s) \vee
\mathrm{possible}(i-1, s - x\_i)$$

Ký hiệu $\vee$ là phép OR (hoặc) trong logic.

Khi chưa xét đồng xu nào, tổng duy nhất có thể là $0$. Tuy nhiên tổng này
không được in ra trong bài toán này.

$$\mathrm{possible}(0, s) =
\begin{cases}
\text{true} & \text{nếu } s = 0 \\
\text{false} & \text{ngược lại}
\end{cases}$$

Vì công thức truy hồi chỉ tham chiếu đến các giá trị đã tính của đồng xu trước đó,
ta chỉ cần dùng một mảng một chiều nếu duyệt theo thứ tự phù hợp.

Độ phức tạp thời gian của lời giải này là $O(n^2 x)$, trong đó $x$ là mệnh giá
tối đa của mỗi đồng xu, vì mọi tổng $s \le nx$.

```cpp
#include <iostream>
using namespace std;
const int X = 100000;

bool possible[X + 1];

int main() {
    int n;
    cin >> n;

    possible[0] = true;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        for (int s = X; s >= x; --s) {
            possible[s] |= possible[s - x];
        }
    }

    int k = 0;
    for (int s = 1; s <= X; ++s) {
        k += possible[s];
    }
    cout << k << "\n";
    for (int s = 1; s <= X; ++s) {
        if (possible[s]) cout << s << " ";
    }
    cout << "\n";
}
```

## Tài liệu tham khảo

* [CPHB (Competitive Programmer's Handbook)](http://cses.fi/book), Chương 7,
  Bài toán xếp ba lô (Knapsack)
