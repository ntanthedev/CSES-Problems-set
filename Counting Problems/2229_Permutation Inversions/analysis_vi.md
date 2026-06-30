# 2229 - Permutation Inversions

## Cách 1: Tiếp cận $O(n ^ 4)$

Trước tiên chúng ta sẽ trình bày cách tiếp cận $O(n^4)$. Cách này hơi chậm nhưng có thể dễ dàng được tối ưu. Chúng ta sử dụng quy hoạch động để tính kết quả. Gọi $\mathrm{dp}[i][j]$ là số hoán vị của các số $1\ldots i$ với chính xác $j$ nghịch thế.

Khi đặt số $i+1$, ta có $i+1$ vị trí cho nó. Nếu ta đặt số này ở cuối hoán vị, không có nghịch thế mới nào được tạo thành. Mỗi vị trí ở bên trái vị trí này sẽ thêm một nghịch thế mới vì tất cả các số đều nhỏ hơn số mới.

Những quan sát này dẫn đến một lời giải trong đó ta duyệt qua các số, vị trí cho mỗi số và số nghịch thế trước đó. Điều này dẫn đến công thức truy hồi

$$\mathrm{dp}[i+1][j]=
\sum\_{0 \le \mathrm{pos} \le i}
\mathrm{dp}[i][j-\mathrm{pos}].$$

Bảng có thể được điền với công thức truy hồi này trong thời gian $O(n^4)$.

```cpp
#include <iostream>
using namespace std;

const int M = 1e9 + 7;
const int N = 501;
const int K = 124751;
int dp[N][K];

int main() {
    int n, k;
    cin >> n >> k;

    dp[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int h = 0; h <= k; ++h) {
            for (int j = 0; j <= min(h, i - 1); ++j) {
                dp[i][h] += dp[i - 1][h - j];
                dp[i][h] %= M;
            }
        }
    }

    cout << dp[n][k] << '\n';
}
```

## Cách 2: Tiếp cận $O(n ^ 3)$

Chú ý rằng giá trị của mỗi vị trí trong dp tương ứng với tổng của một đoạn các giá trị từ lớp trước đó. Hơn nữa, các đoạn này có cùng độ dài và vị trí bắt đầu của chúng chênh lệch nhau một đơn vị. Do đó, ta có thể duy trì tổng trong khi điền lớp dp. Điều này dẫn đến một lời giải với độ phức tạp thời gian $O(n^3)$.

```cpp
#include <iostream>
using namespace std;

const int M = 1e9 + 7;
const int N = 501;
const int K = 124751;
int dp[N][K];

int main() {
    int n, k;
    cin >> n >> k;

    dp[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        int sum = 0;
        for (int h = 0; h <= k; ++h) {
            sum += dp[i - 1][h];
            sum %= M;
            if (h >= i) {
                sum -= dp[i - 1][h - i];
                sum += M;
                sum %= M;
            }
            dp[i][h] = sum;
        }
    }

    cout << dp[n][k] << '\n';
}
```
