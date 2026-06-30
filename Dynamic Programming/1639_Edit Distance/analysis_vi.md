# 1639 - Khoảng cách sửa đổi

Khoảng cách sửa đổi có thể được tính bằng quy hoạch động. Ta ký hiệu hai xâu đầu vào là $a$ và $b$.

Gọi $\gdef \d {{\mathrm{distance}}} \d(i, j)$ là khoảng cách sửa đổi giữa tiền tố độ dài $i$ của $a$ và tiền tố độ dài $j$ của $b$.

Trường hợp cơ sở: $\d(0, x) = \d(x, 0) = x$ vì tất cả $x$ ký tự đều phải được chèn hoặc xóa do xâu kia rỗng.

Trường hợp còn lại, ta có

$$\d(i, j) = \min
\begin{cases}
\d(i, j-1) + 1 \\
\d(i-1, j) + 1 \\
\d(i-1, j-1) + [a[i-1] \ne b[j-1]],
\end{cases}$$

trong đó $[a[i-1] \ne b[j-1]]$ bằng $0$ nếu hai ký tự ở chỉ số 0 bằng nhau và bằng $1$ nếu ngược lại. Các phương án lần lượt tương ứng với: chèn ký tự $b[j-1]$, xóa ký tự $a[i-1]$, và tái sử dụng hoặc thay thế $a[i-1]$ bằng $b[j-1]$ trong một phép toán.

Tính đúng đắn của công thức truy hồi này được đảm bảo bởi thực tế là luôn tồn tại một dãy thao tác sửa đổi tối ưu, trong đó mọi thao tác được thực hiện theo thứ tự từ trái sang phải. Các đường đi trong mảng quy hoạch động tuân theo các chuyển tiếp trong công thức truy hồi tương ứng với các dãy thao tác như vậy.

Độ phức tạp thời gian của lời giải này là $O(nm)$.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    string a, b;
    cin >> a >> b;
    int n = a.size(), m = b.size();

    vector<vector<int>> distance(n + 1, vector<int>(m + 1));
    for (int i = 0; i <= n; ++i) {
        distance[i][0] = i;
    }
    for (int j = 0; j <= m; ++j) {
        distance[0][j] = j;
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            distance[i][j] = min({
                distance[i][j - 1] + 1,
                distance[i - 1][j] + 1,
                distance[i - 1][j - 1] + (a[i - 1] != b[j - 1]),
            });
        }
    }

    cout << distance[n][m] << "\n";
}
```

## Tài liệu tham khảo

* [CPHB (Sổ tay lập trình viên)](https://cses.fi/book), Chương 7.5, Khoảng cách sửa đổi
* [Khoảng cách sửa đổi (Wikipedia)](https://en.wikipedia.org/wiki/Edit_distance)
