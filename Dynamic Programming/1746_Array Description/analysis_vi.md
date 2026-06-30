# 1746 - Mô tả mảng

Bài toán này có thể giải bằng quy hoạch động. Gọi $\mathrm{count}(i, j)$ là
số lượng tổ hợp hợp lệ cho các giá trị trong mảng tại các chỉ số $1,\dots,i$,
sao cho giá trị cuối cùng, tại chỉ số $i$, bằng $j$.

Ta định nghĩa $\mathrm{count}(1, j)$ là trường hợp cơ sở: Nếu $x\_1 = 0$,
thì mọi giá trị $1 \le j \le m$ đều có thể. Ngược lại chỉ có $j = x\_1$ là
có thể.

$$\mathrm{count}(1, j) =
\begin{cases}
1 & \text{nếu } x\_1 = 0 \text{ hoặc } x\_1 = j \\
0 & \text{ngược lại}
\end{cases}$$

Giả sử mảng hợp lệ đến chỉ số $i-1$, ta chỉ cần đảm bảo rằng các giá trị tại
chỉ số $i-1$ và $i$ có chênh lệch tuyệt đối tối đa là một. Số tổ hợp được đặt
bằng không nếu $j$ không khớp với mô tả.

$$\mathrm{count}(i, j) =
\begin{cases}
{ \displaystyle \small \sum\_{k=-1}^{1} } \mathrm{count}(i-1, j+k)
& \text{nếu } x\_i = 0 \text{ hoặc } x\_i = j \\
0 & \text{ngược lại}
\end{cases}$$

Điều này cho độ phức tạp thời gian $O(nm)$.

Trong cài đặt dưới đây, mảng quy hoạch động được đệm thêm các số 0
tại `count[i][0]` và `count[i][m + 1]` để tránh truy cập ngoài phạm vi.

```cpp
#include <iostream>
#include <vector>
using namespace std;
const int M = 1000000007;
const int N = 100001;

int count[N][102];

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> x(n + 1);
    for (int i = 1; i <= n; ++i) cin >> x[i];

    for (int j = 1; j <= m; ++j) {
        if (x[1] == 0 || x[1] == j) {
            count[1][j] = 1;
        }
    }
    for (int i = 2; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (x[i] == 0 || x[i] == j) {
                for (int k = -1; k <= 1; ++k) {
                    count[i][j] = (count[i][j] + count[i - 1][j + k]) % M;
                }
            }
        }
    }

    int result = 0;
    for (int j = 1; j <= m; ++j) {
        result = (result + count[n][j]) % M;
    }
    cout << result << "\n";
}
```
