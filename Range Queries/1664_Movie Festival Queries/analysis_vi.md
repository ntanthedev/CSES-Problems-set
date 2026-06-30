# 1664 - Truy vấn liên hoan phim

Trong số tất cả các bộ phim có sẵn, việc chọn bộ phim kết thúc sớm nhất luôn là tối ưu.
Sử dụng nhận xét này, chúng ta có thể tìm bộ phim tối ưu tiếp theo cho mỗi
mốc thời gian. Sau đó, chúng ta lại tìm bộ phim tối ưu tiếp theo sau
thời điểm kết thúc, và cứ tiếp tục như vậy.

Lưu ý rằng tất cả các thời gian đều nằm trong khoảng $1\dots 10^6$, dẫn đến một giải pháp
sử dụng bảng nhảy. Trong bảng, chúng ta sẽ lưu thời gian kết thúc nếu chúng ta xem
$2^k$ bộ phim tối ưu tiếp theo bắt đầu từ một vị trí, với mọi $2^k \le M$. Việc
xây dựng bảng mất $O(M \log M)$ thời gian, trong đó $M$ là thời gian lớn nhất
có thể. Trả lời một truy vấn mất $O(\log M)$ thời gian, dẫn đến một
giải thuật với độ phức tạp thời gian là $O(n + M \log M + q\log M)$.

```cpp
#include <iostream>
using namespace std;

const int M = 1000002;
const int LOG_M = __lg(M);

int nxt[M][LOG_M + 1];

int main() {
    int n, q;
    cin >> n >> q;

    for (int i = 1; i <= M + 1; ++i) {
        nxt[i][0] = M + 1;
    }

    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        nxt[a][0] = min(nxt[a][0], b);
    }

    for (int i = M - 1; i > 0; --i) {
        nxt[i][0] = min(nxt[i][0], nxt[i + 1][0]);
    }

    for (int j = 1; j <= LOG_M; ++j) {
        for (int i = 1; i <= M + 1; ++i) {
            nxt[i][j] = nxt[nxt[i][j - 1]][j - 1];
        }
    }

    for (int qi = 0; qi < q; ++qi) {
        int a, b;
        cin >> a >> b;
        int ans = 0;
        for (int j = LOG_M; j >= 0; --j) {
            if (nxt[a][j] <= b) {
                ans += 1 << j;
                a = nxt[a][j];
            }
        }
        cout << ans << '\n';
    }
}
```
