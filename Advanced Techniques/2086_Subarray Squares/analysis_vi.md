# 2086 - Subarray Squares

Chúng ta sẽ giải bài toán này bằng quy hoạch động. Ta sẽ có một bảng quy hoạch động,
trong đó $\mathrm{dp}[j][i]$ là chi phí tối thiểu để chia $i$ phần tử đầu tiên
thành $j$ đoạn con, với đoạn cuối cùng kết thúc tại $i$.

Ta sẽ điền bảng theo công thức truy hồi

$$\mathrm{dp}[j][i] =
\min\_{k< i}\mathrm{dp}[j-1][k]+(x\_k+x\_{k+1}+\dots+x\_{i-1})^2.$$

Nếu ta xây dựng một mảng tổng tiền tố $\mathrm{sum}$, trong đó $\mathrm{sum}[i]$
là tổng của $i$ phần tử đầu tiên, công thức truy hồi trở thành

$$\mathrm{dp}[j][i] =
\min\_{k < i}\mathrm{dp}[j-1][k]+(\mathrm{sum}[i]-\mathrm{sum}[k-1])^2.$$

Chú ý rằng nếu khai triển biểu thức

$$(\mathrm{sum}[i]-\mathrm{sum}[k-1])^2=
\mathrm{sum}[i]^2
-2\cdot\mathrm{sum}[i]\cdot\mathrm{sum}[k-1]
+\mathrm{sum}[k-1]^2,$$

ta có thể sắp xếp lại công thức truy hồi thành

$$\mathrm{dp}[j][i] =\mathrm{sum}[i]^2+
\min\_{k < i}\mathrm{dp}[j-1][k]
-2\cdot\mathrm{sum}[i]\cdot\mathrm{sum}[k-1]
+\mathrm{sum}[k-1]^2.$$

Bây giờ, mỗi vị trí $k < i$ trước đó có thể được xem như một đường thẳng

$$y\_k=x\cdot
(-2\cdot\mathrm{sum}[k-1])
+\mathrm{dp}[j-1][k]
+\mathrm{sum}[k-1]^2,$$

và chúng ta cần tìm độ cao nhỏ nhất của một đường thẳng tại vị trí
$x = \mathrm{sum}[i]$.

Một kỹ thuật được gọi là *kỹ thuật bao lồi (convex hull trick)* thực hiện chính
xác điều này. Vì dãy các hệ số góc ($-2\cdot\mathrm{sum}[k-1]$) đang giảm dần,
chúng ta chỉ cần duy trì một ngăn xếp các đường thẳng. Hơn nữa, vì dãy các điểm
truy vấn ($\mathrm{sum}[i]$) đang tăng dần, ta có thể duy trì một con trỏ đến
mảng và tìm câu trả lời cho mỗi truy vấn với chi phí khấu hao $O(1)$.

Chú ý rằng, tại mọi thời điểm, chúng ta chỉ sử dụng hai lớp gần nhất của bảng
quy hoạch động. Vì lý do này, chỉ cần lưu trữ hai mảng, đại diện cho hai lớp
cuối cùng.

Cách tiếp cận này điền mỗi lớp trong thời gian tuyến tính và do đó có độ phức
tạp thời gian là $O(nk)$. Có thể giải bài toán nhanh hơn nữa, sử dụng một kỹ
thuật được gọi là *kỹ thuật Aliens* (liên kết bên dưới).

## Tài liệu tham khảo

* [CP-Algorithms, *Convex Hull Trick*](https://cp-algorithms.com/geometry/convex_hull_trick.html)
* [serbanology.com, *The Trick From Aliens*](http://www.serbanology.com/article/The%20Trick%20From%20Aliens)

```cpp
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const ll INF = 1e18;

struct Line {
    ll a, b;  // Biểu diễn đường thẳng y = ax + b
    // Trả về độ cao của đường thẳng tại x.
    ll operator()(ll x) { return a * x + b; }
};

int main() {
    int n, k;
    cin >> n >> k;

    vector<int> x(n);
    vector<ll> sum(n + 1);
    for (int i = 0; i < n; ++i) {
        cin >> x[i];
        sum[i + 1] = sum[i] + x[i];
    }

    vector<ll> dp(n + 1, INF);
    dp[0] = 0;

    for (int i = 0; i < k; ++i) {
        vector<Line> lines;
        int pos = 0;  // Lưu chỉ số của đường thẳng thấp nhất hiện tại.

        // Tìm độ cao của đường thẳng thấp nhất tại vị trí x.
        // Giả sử dãy các x đang tăng dần.
        auto get_best = [&](ll x) {
            while (pos + 1 < size(lines) && lines[pos + 1](x) < lines[pos](x)) {
                pos++;
            }
            return lines[pos](x);
        };

        vector<ll> ndp(n + 1);
        for (int j = i; j <= n; ++j) {
            if (j != i) {
                ndp[j] = sum[j] * sum[j] + get_best(sum[j]);
            }
            Line l = {-2 * sum[j], dp[j] + sum[j] * sum[j]};
            while (lines.size() > 1) {
                auto a = lines[lines.size() - 2];
                auto b = lines[lines.size() - 1];
                if ((l.b - a.b) * (a.a - b.a) <= (b.b - a.b) * (a.a - l.a)) {
                    lines.pop_back();
                } else {
                    break;
                }
            }
            lines.push_back(l);
        }
        swap(dp, ndp);
    }
    cout << dp[n] << '\n';
}
```
