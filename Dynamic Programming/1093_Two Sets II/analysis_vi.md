# 1093 - Two Sets II

Bài toán có thể được phát biểu tương đương là tìm số tập con của
$\{1, \dots, n\}$ có tổng bằng một nửa tổng tất cả, tức là $\frac
{n(n+1)}{4}$. Tuy nhiên, các tập bù không được tính hai lần.

Nếu một nửa tổng không phải là số nguyên, thì không có nghiệm nào. Ngược lại,
ta sử dụng quy hoạch động để tìm đáp án.

Định nghĩa hàm $\mathrm{sets}(x, s)$ là số tập con của $\{1,
\dots, x\}$ có tổng bằng $s$.

Khi xét số $x$, ta có thể chọn nó vào tập con, khi đó các số nhỏ hơn phải
tạo thành tổng $s-x$, hoặc không chọn, do đó các số nhỏ hơn phải tạo thành
toàn bộ tổng $s$.

$$\mathrm{sets}(x, s) = \mathrm{sets}(x-1, s) + \mathrm{sets}(x-1, s-x)$$

Với trường hợp cơ sở, ta đặt chỉ có tổng $0$ có thể được tạo thành từ một tập
rỗng.

$$\mathrm{sets}(0, s) = \begin{cases}
1 & \text{if } s = 0
0 & \text{otherwise}
\end{cases}$$

Đáp án được tìm tại $\mathrm{sets}(n-1, h)$, với $h$ là một nửa tổng tất cả.
Phần tử $n$ không được xét nhằm phân biệt các tập bù với nhau và tránh đếm
chúng hai lần. Một mảng quy hoạch động một chiều là đủ vì công thức đệ quy chỉ
tham chiếu $\mathrm{sets}$ tại $x-1$, số đã được xét trước đó.

Độ phức tạp thời gian của lời giải này là $O(n^3)$. Một nửa tổng tất cả là
$O(n^2)$ và $O(n)$ số khác nhau được xét.

```cpp
#include <iostream>
using namespace std;
const int N = 500 * 501 / 4;
const int M = 1000000007;

int sets[N + 1];

int main() {
    int n;
    cin >> n;

    int total = n * (n + 1) / 2;
    if (total % 2 != 0) {
        cout << 0 << endl;
        return 0;
    }
    int half = total / 2;

    sets[0] = 1;
    for (int x = 1; x < n; ++x) {
        for (int s = half; s - x >= 0; --s) {
            sets[s] = (sets[s] + sets[s - x]) % M;
        }
    }

    cout << sets[half] << endl;
}
```
