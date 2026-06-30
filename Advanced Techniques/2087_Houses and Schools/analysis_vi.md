# 2087 - Houses and Schools

Có một số cách tiếp cận khác nhau cho bài toán này. Hầu hết chúng đều có
bảng quy hoạch động tương tự như sau:

$$\mathrm{dp}[j][i], 1 \le j \le k, 1 \le i \le n$$

ký hiệu tổng khoảng cách đi lại nhỏ nhất có thể cho $i$ ngôi nhà đầu tiên với
$j$ trường học và trường học cuối cùng ở chỉ số $i$.

Ta sẽ dùng $\mathrm{cost}(i, j)$ để ký hiệu tổng khoảng cách đi lại cho các
đứa trẻ ở các ngôi nhà từ $i$ đến $j$, với giả định có trường học ở các ngôi nhà
$i$ và $j$. Đơn giản là điền bảng này theo công thức truy hồi

$$\mathrm{dp}[j][i] = \min\_{p < i} \mathrm{dp}[j - 1][p] + \mathrm{cost}(p, i)$$

sẽ cho ra thuật toán với độ phức tạp thời gian $O(n^2k)$. Điều này có thể
được tăng tốc với một tối ưu hóa quy hoạch động gọi là *chia để trị*. Nó có thể
được áp dụng chỉ khi hàm $\mathrm{cost}$ thỏa mãn *bất đẳng thức hình tứ giác*

$$\mathrm{cost}(a, c) + \mathrm{cost}(b, d)
\le
\mathrm{cost}(a, d) + \mathrm{cost}(b, c)$$

với mọi $a \le b \le c \le d$. Có thể chứng minh rằng hàm $\mathrm{cost}$
của chúng ta (tổng khoảng cách đi lại giữa các trường học) thỏa mãn
bất đẳng thức này.

Gọi $\mathrm{pos}\_j(i)$ là vị trí $p$ nhỏ nhất mà tại đó giá trị của

$$\min\_{p < i} \mathrm{dp}[j - 1][p] + \mathrm{cost}(p, i)$$

đạt giá trị nhỏ nhất. Có thể chứng minh rằng nếu bất đẳng thức hình tứ giác
đúng, thì $\mathrm{pos}\_j(i)$ tạo thành một dãy tăng dần với mọi $i$, tức là
$\mathrm{pos}\_j(i) \le \mathrm{pos}\_j(i + 1)$. Điều này cho phép chúng ta tạo
một hàm đệ quy để điền một lớp của bảng quy hoạch động, với $j$ cố định.

Ý tưởng là bắt đầu với một phạm vi tìm kiếm $[0, n)$, và tại mỗi bước, chia
đôi phạm vi và xử lý đệ quy hai phần. Phạm vi $[i, j)$ trở thành $[i, m)$ và
$[m, r)$, trong đó $m$ là điểm giữa của phạm vi $m=\lfloor \frac {l+r} {2} \rfloor$.
Sau đó, nếu ta có thể tìm $\mathrm{dp}[j][m]$ và do đó $\mathrm{pos}\_j(m)$,
ta biết rằng $\mathrm{pos}\_j(i) \le \mathrm{pos}\_j(m)$, với mọi $i < m$ và
$\mathrm{pos}\_j(m) \le \mathrm{pos}\_j(i)$, với mọi $m < i$. Điều này cho phép
ta thu hẹp không gian tìm kiếm cho $p$ trong các lời gọi tiếp theo, làm cho độ
phức tạp thời gian của việc điền một lớp quy hoạch động là $O(n\log n)$ và tổng
độ phức tạp thời gian là $O(nk\log n)$.

Có những giải pháp nâng cao hơn cho bài toán này, ví dụ, sử dụng kỹ thuật gọi là
*kỹ thuật Aliens* kết hợp với *kỹ thuật bao lồi*.

```cpp
#include <iostream>
using namespace std;
using ll = long long;

const ll INF = 1e18;
const int N = 3000;

int c[N];
ll lcost[N][N];
ll rcost[N][N];

ll left_cost(int l, int r) {
    return l <= r ? lcost[l][r] : 0;
}
ll right_cost(int l, int r) {
    return l <= r ? rcost[l][r] : 0;
}

ll cost(int l, int r) {
    int mid = (l + r) / 2;
    return left_cost(l, mid) + right_cost(mid + 1, r);
}

ll dp[N][N];

void recurse(int lvl, int l, int r, int pos_l, int pos_r) {
    if (l > r) return;

    int mid = (l + r) / 2;
    ll best = INF;
    int pos = l;

    for (int k = pos_l; k <= min(mid, pos_r); k++) {
        ll offer = dp[lvl - 1][k] + cost(k, mid);
        if (offer < best) {
            best = offer;
            pos = k;
        }
    }

    dp[lvl][mid] = best;

    recurse(lvl, l, mid - 1, pos_l, pos);
    recurse(lvl, mid + 1, r, pos, pos_r);
}

int main() {
    int n, k;
    cin >> n >> k;

    for (int i = 0; i < n; ++i) {
        cin >> c[i];
    }

    for (int i = 0; i < n; ++i) {
        ll s = 0;
        for (int j = i; j < n; ++j) {
            s += ll(j - i) * c[j];
            lcost[i][j] = s;
        }
    }

    for (int i = 0; i < n; ++i) {
        ll s = 0;
        for (int j = i; j >= 0; --j) {
            s += ll(i - j) * c[j];
            rcost[j][i] = s;
        }
    }

    for (int i = 0; i < n; ++i) {
        dp[0][i] = right_cost(0, i);
    }

    for (int i = 1; i < k; ++i) {
        recurse(i, 0, n, 0, n);
    }

    ll ans = INF;
    for (int i = 0; i < n; ++i) {
        ans = min(ans, dp[k - 1][i] + left_cost(i, n - 1));
    }

    cout << ans << '\n';
}
```
