# 1725 - Dice Probability

Chúng ta giải bài toán bằng quy hoạch động: $p[i][j]$ là xác suất có tổng bằng $j$ sau khi gieo xúc xắc $i$ lần.

Cơ sở $p[0][0]=1$, vì tổng chắc chắn là $0$ nếu không có lần gieo nào. Sau đó, khi biết giá trị $p[i][j]$, ta xét tất cả các kết quả có thể của một lần gieo $k=1,2,\dots,6$. Với mỗi kết quả như vậy, ta tăng $p[i+1][j+k]$ thêm $p[i][j]/6$. Cuối cùng, ta tính tổng các xác suất $p[n][i]$ với $i$ nằm giữa $a$ và $b$.

Lời giải có độ phức tạp $O(n^2)$.

```cpp
#include <iostream>
using namespace std;

const int N = 100;
double p[N + 1][6 * N + 1];

int main() {
    int n, a, b;
    cin >> n >> a >> b;

    p[0][0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = i; j <= 6 * i; j++) {
            for (int k = 1; k <= 6; k++) {
                p[i + 1][j + k] += p[i][j] / 6;
            }
        }
    }

    double answer = 0;
    for (int i = a; i <= b; i++) {
        answer += p[n][i];
    }
    cout.precision(6);
    cout << fixed << answer << "\n";
}
```
