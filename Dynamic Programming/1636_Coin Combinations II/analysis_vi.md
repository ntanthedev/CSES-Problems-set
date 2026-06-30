# 1636 - Tổ hợp xu II

Đối với bài toán này, ta xét một hàm hai biến để đếm số *dãy* xu có thể.

Lưu ý rằng các đồng xu không nhất thiết phải được sắp xếp theo thứ tự số. Thứ tự xuất hiện trong dữ liệu vào là đủ. Nói cách khác, ta có thể giả sử $c\_1 < c\_2 < \cdots < c\_n$.

Gọi $\mathrm{ways}(x, j)$ là số lượng dãy không giảm phân biệt có tổng bằng $x$, chỉ chứa các đồng xu từ $j$ đồng xu đầu tiên $c\_1, c\_2, \ldots, c\_j$.

Đáp án của bài toán có thể lấy từ $\mathrm{ways}(x, n)$, khi tất cả các đồng xu đều có sẵn.

Khi không có đồng xu nào có thể dùng, tổng duy nhất có thể là $0$:

$$\mathrm{ways}(x, 0) =
\begin{cases}
1 & \text{nếu } x=0 \\
0 & \text{trường hợp còn lại}
\end{cases}$$

Trong trường hợp tổng quát của $\mathrm{ways}(x, j)$, xét đồng xu cuối cùng trong dãy. Các đồng xu có giá trị $c\_j$ nên được sắp xếp ở cuối, do đó hoặc đồng xu cuối cùng là $c\_j$ hoặc dãy không chứa đồng xu nào trong số chúng.

Trong trường hợp sau, số lượng dãy cần tìm là $\mathrm{ways}(x, j-1)$.

$$\mathrm{ways}(x, j) = \mathrm{ways}(x-c\_j, j) + \mathrm{ways}(x, j-1)$$

Mặc dù mảng hai chiều với kích thước $n \times (x+1)$ có thể vừa vặn với giới hạn bộ nhớ, nhưng thực tế không cần thiết. Bằng cách duyệt qua các đồng xu khác nhau trong vòng lặp ngoài, các kết quả trung gian có thể được lưu trữ trong cùng một mảng kích thước $x+1$.

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
    for (int j = 0; j < n; ++j) {
        for (int i = c[j]; i <= x; ++i) {
            ways[i] = (ways[i - c[j]] + ways[i]) % M;
        }
    }

    cout << ways[x] << "\n";
}
```
