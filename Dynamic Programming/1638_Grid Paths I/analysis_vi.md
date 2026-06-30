# 1638 - Đường đi trên lưới I

Để sử dụng quy hoạch động, ta chia bài toán này thành các bài toán con, trong đó thay vì đếm số đường đi đến ô dưới cùng bên phải, đại lượng này được tính cho mọi ô trong lưới.

Hàm $\mathrm{paths}(i, j)$ biểu diễn số đường đi hợp lệ từ ô trên cùng bên trái đến ô ở hàng $i$ và cột $j$. Chỉ số bắt đầu từ 0 được sử dụng trong lời giải này.

Đáp án là $\mathrm{paths}(n-1, n-1)$.

Nếu ô $(i, j)$ có bẫy, không có đường đi hợp lệ nào vào nó. Điều này cũng áp dụng cho ô trên cùng bên trái, nếu không thì ô đó mặc nhiên có một đường đi.

Mọi đường đi kết thúc tại ô $(i, j) \neq (0, 0)$ phải đến từ hoặc ô $(i-1, j)$ ở phía trên, hoặc ô $(i, j-1)$ ở bên trái.

$$\mathrm{paths}(i, j) =
\begin{cases}
0 & \text{nếu có bẫy} \\
1 & \text{nếu } i=j=0 \\
\mathrm{paths}(i-1, j) + \mathrm{paths}(i, j-1) & \text{trường hợp còn lại}
\end{cases}$$

Một thứ tự phù hợp để tính hàm này một cách lặp là duyệt qua các hàng từ trên xuống dưới và mỗi hàng từ trái sang phải.

```cpp
#include <iostream>
#include <vector>
using namespace std;
const int M = 1000000007;

int main() {
    int n;
    cin >> n;

    vector<string> grid(n);
    for (int i = 0; i < n; ++i) {
        cin >> grid[i];
    }

    vector<vector<int>> paths(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == '*') {
                paths[i][j] = 0;
            } else {
                paths[i][j] = i == 0 && j == 0;
                if (i) paths[i][j] += paths[i - 1][j];
                if (j) paths[i][j] += paths[i][j - 1];
                paths[i][j] %= M;
            }
        }
    }

    cout << paths[n - 1][n - 1] << "\n";
}
```

## Tài liệu tham khảo

* [CPHB (Sổ tay lập trình viên)](https://cses.fi/book), Chương 7.3, Đường đi trong lưới
