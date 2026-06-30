# 1750 - Truy vấn Hành tinh I

Chúng ta bắt đầu giải bài toán bằng cách tiền xử lý đích đến cho mọi hành tinh
khi số lần dịch chuyển là một lũy thừa của hai. Ta sẽ lưu đích đến
đạt được từ hành tinh $x$ sau khi đi qua $2^l$ cổng dịch chuyển trong
$\mathrm{succ}[l][x]$. Ta điền mảng từng lớp theo thứ tự
$l$ tăng dần. Với $l = 0$ ta đơn giản đặt $\mathrm{succ}[0][x]$ là hành tinh
đến được từ $x$ bằng cách đi qua một cổng dịch chuyển. Với $l > 0$ ta đặt
$\mathrm{succ}[l][x] = \mathrm{succ}[l-1][\mathrm{succ}[l-1][x]]$.

Để giải trường hợp số lần dịch chuyển $k$ không phải là lũy thừa của hai,
ta sẽ sử dụng biểu diễn nhị phân của $k$ để tìm các lũy thừa của hai
$s\_1, \dots, s\_m$ sao cho $\sum\_i s\_i = k$. Sau đó ta có thể tìm đích đến
cuối cùng bằng cách sử dụng mảng $\mathrm{succ}$ để đi $s\_1$ bước, $s\_2$
bước, v.v.

Gọi giá trị lớn nhất của $k$ là $K$ ($K = 10^9$ trong đề bài).
Xây dựng mảng $\mathrm{succ}$ mất $O(n \log K)$ thời gian và trả lời các
truy vấn mất $O(q \log K)$. Do đó tổng độ phức tạp thời gian của
lời giải là $O((n + q) \log K)$.

```cpp
#include <iostream>
using namespace std;

const int N = 200001;
const int M = 30;

int succ[M][N];

int main() {
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; ++i) {
        cin >> succ[0][i];
    }

    for (int i = 1; i < M; ++i) {
        for (int j = 1; j <= n; ++j) {
            succ[i][j] = succ[i - 1][succ[i - 1][j]];
        }
    }

    for (int i = 0; i < q; ++i) {
        int x, k;
        cin >> x >> k;
        for (int j = 0; j < M; ++j) {
            if (k & (1 << j)) {
                x = succ[j][x];
            }
        }
        std::cout << x << '\n';
    }
}
```

## Tài liệu tham khảo

* [CPHB (Sổ tay Lập trình viên)](http://cses.fi/book),
  Chương 16.3
