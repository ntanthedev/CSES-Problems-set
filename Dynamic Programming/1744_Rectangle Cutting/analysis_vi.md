# 1744 - Cắt hình chữ nhật

Một giải pháp tham lam cho bài toán này là luôn cắt một hình vuông từ hình chữ nhật, bằng cách chọn cạnh ngắn hơn của hình chữ nhật. Tuy nhiên, cách này không nhất thiết tối ưu:

![phản ví dụ](6e005441ab10fe7fca636271212d8f858064580a87e78a0bef552eed4c7656db)

Thay vào đó, ta sử dụng quy hoạch động để kiểm tra toàn diện mọi cách cắt có thể và chọn cách tối ưu nhất.

Hàm $\gdef \m {{\mathrm{moves}}} \m(i, j)$ biểu diễn số bước tối thiểu để cắt một hình chữ nhật $i \times j$ thành các hình vuông.

Nếu hình chữ nhật đã là hình vuông, thì $i=j$ và $\m(i, j)=0$.

Nếu không, tìm cách tối ưu trong tất cả các cách cắt ngang và cắt dọc:

$$\m(i, j) = \min
\begin{cases}
\min\_{x=1}^{i-1} (\m(x, j) + \m(i - x, j) + 1) \\[4pt]
\min\_{y=1}^{j-1} (\m(i, y) + \m(i, j - y) + 1)
\end{cases}$$

Với $n=\max(a, b)$, độ phức tạp thời gian của lời giải này là $O(n^3)$.

```cpp
#include <iostream>
#include <vector>
using namespace std;
const int INF = 1e9;

int main() {
    int a, b;
    cin >> a >> b;

    vector<vector<int>> moves(a + 1, vector<int>(b + 1));
    for (int i = 1; i <= a; ++i) {
        for (int j = 1; j <= b; ++j) {
            if (i == j) {
                moves[i][j] = 0;
            } else {
                moves[i][j] = INF;
                for (int x = 1; x < i; ++x) {
                    moves[i][j] =
                        min(moves[i][j], moves[x][j] + moves[i - x][j] + 1);
                }
                for (int y = 1; y < j; ++y) {
                    moves[i][j] =
                        min(moves[i][j], moves[i][y] + moves[i][j - y] + 1);
                }
            }
        }
    }

    cout << moves[a][b] << "\n";
}
```
