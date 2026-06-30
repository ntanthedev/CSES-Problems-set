# 2088 - Knuth Division

Chúng ta sẽ giải bài toán này bằng quy hoạch động. Nếu $\mathrm{dp}[l][r]$
là chi phí để chia đoạn con $[l, r]$, ta có công thức truy hồi sau

$$\mathrm{dp}[i][j]=
\min\_{i \le k < j}
\mathrm{dp}[i][k]
+\mathrm{dp}[k + 1][j]
+\mathrm{cost}(i, j),$$

trong đó $\mathrm{cost}(i, j)$ là chi phí để tách đoạn con $[i, j]$, trong
trường hợp này là tổng của đoạn con. Điền bảng quy hoạch động theo quy tắc
này sẽ cho ra thuật toán với độ phức tạp thời gian $O(n ^ 3)$, quá chậm.

Để tăng tốc giải pháp, chúng ta sẽ sử dụng một tối ưu hóa quy hoạch động gọi là
*tối ưu hóa Knuth*. Tối ưu hóa này áp dụng được cho bất kỳ công thức truy hồi
nào tương tự như trên nếu hàm chi phí thỏa mãn hai bất đẳng thức sau:

$$\begin{align\*}
\mathrm{cost}(b, c) &\le
\mathrm{cost}(a, d) \\
\mathrm{cost}(a, c)
+\mathrm{cost}(b, d)
&\le
\mathrm{cost}(a, d)
+\mathrm{cost}(b, c)
\end{align\*}$$

với mọi $a \le b \le c \le d$.

Gọi $\mathrm{pos}(i, j)$ là $k$ làm tối thiểu công thức truy hồi ban đầu, với
$i$ và $j$. Ta biết rằng, nếu các bất đẳng thức trên đúng, thì

$$\mathrm{pos}(i, j - 1) \le \mathrm{pos}(i, j) \le \mathrm{pos}(i + 1, j).$$

Điều này cho phép chúng ta điền bảng quy hoạch động một cách hiệu quả. Hãy xử
lý các đoạn con theo thứ tự tăng dần của độ dài. Khi đang xử lý đoạn con $[i,
j]$, ta đã tính được câu trả lời cho các đoạn $[i, j - 1]$ và $[i + 1, j]$ và
do đó biết được giá trị $\mathrm{pos}$ của chúng. Các giá trị $\mathrm{pos}$
của độ dài trước đó tăng dần khi được sắp xếp theo chỉ số bắt đầu. Điều này
có nghĩa là chúng chia không gian tìm kiếm cho các giá trị $\mathrm{pos}$ tiếp
theo thành các khoảng rời rạc, cho phép chúng ta điền mỗi lớp trong thời gian
$O(n)$, làm cho tổng độ phức tạp thời gian của giải pháp là $O(n^2)$.

```cpp
#include <iostream>
using namespace std;
using ll = long long;
const ll INF = 1e18;

const int N = 5000;
int x[N], pos[N][N];
ll s[N + 1], dp[N][N];

int main() {
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> x[i];
        s[i + 1] = s[i] + x[i];
        dp[i][i] = 0;
        pos[i][i] = i + 1;
    }

    for (int len = 2; len <= n; ++len) {
        for (int l = 0; l <= n - len; ++l) {
            int r = l + len - 1;
            dp[l][r] = INF;
            for (int p = pos[l][r - 1]; p <= pos[l + 1][r]; ++p) {
                ll off = dp[l][p - 1] + dp[p][r] + (s[r + 1] - s[l]);
                if (off < dp[l][r]) {
                    dp[l][r] = off;
                    pos[l][r] = p;
                }
            }
        }
    }

    cout << dp[0][n - 1] << endl;
}
```
