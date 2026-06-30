# 1726 - Moving Robots

Chúng ta giả sử các hàng và cột được đánh số từ $0$ đến $N-1$ và các robot được đánh số từ $0$ đến $N^2-1$. Robot bắt đầu tại ô $(i,j)$ có số hiệu là $i \cdot N+j$. Trong bài toán này $N=8$ trong mỗi test.

Chúng ta giải bài toán bằng quy hoạch động: $p[m][r][i][j]$ là xác suất robot $r$ ở ô $(i,j)$ sau $m$ lượt.

Cơ sở: $p[0][i \cdot N+j][i][j]=1$ với mỗi ô $(i,j)$. Sau đó, khi biết giá trị $p[m][r][i][j]$, ta tìm các ô mà robot $r$ có thể di chuyển từ ô $(i,j)$. Với mỗi ô $(i',j')$ như vậy, ta tăng giá trị $p[m+1][r][i'][j']$ thêm $p[m][r][i][j]/c$, trong đó $c$ là tổng số ô mà robot có thể di chuyển.

Sau đó, ta duyệt qua bảng và tính, với mỗi ô $(i,j)$, xác suất ô đó trống sau $k$ lượt. Ta tính xác suất theo công thức

$$\prod\_{r=0}^{N^2-1} (1-p[k][r][i][j])$$

vì yêu cầu không có robot nào ở ô đó sau $k$ lượt. Theo tính tuyến tính của kỳ vọng, tổng của tất cả các xác suất như vậy bằng số ô trống kỳ vọng sau $k$ lượt.

Lời giải có độ phức tạp $O(k N^4)$.

```cpp
#include <iostream>
#include <vector>
using namespace std;

const int N = 8;
const int K = 100;
double p[K + 1][N * N][N][N];

int main() {
    int k;
    cin >> k;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            p[0][i * N + j][i][j] = 1;
        }
    }

    for (int m = 0; m < k; m++) {
        for (int r = 0; r < N * N; r++) {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    vector<pair<int, int>> moves;
                    if (i > 0) moves.emplace_back(i - 1, j);
                    if (j > 0) moves.emplace_back(i, j - 1);
                    if (i + 1 < N) moves.emplace_back(i + 1, j);
                    if (j + 1 < N) moves.emplace_back(i, j + 1);
                    double add = p[m][r][i][j] / moves.size();
                    for (auto d : moves) {
                        p[m + 1][r][d.first][d.second] += add;
                    }
                }
            }
        }
    }

    double answer = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            double e = 1;
            for (int r = 0; r < N * N; r++) {
                e *= (1 - p[k][r][i][j]);
            }
            answer += e;
        }
    }
    cout.precision(6);
    cout << fixed << answer << "\n";
}
```
