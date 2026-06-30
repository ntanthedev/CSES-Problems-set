# 1618 - Chữ số 0 ở cuối

Số chữ số 0 ở cuối của một số bằng số lần ta có thể chia nó cho $10$. Vì $10=2 \cdot 5$, ta cần tập trung vào các thừa số $2$ và $5$.

Trong một giai thừa, số lượng thừa số $5$ luôn nhỏ hơn số lượng thừa số $2$, và số chữ số 0 ở cuối bằng số lượng thừa số $5$. Ví dụ, $20! = 2^{18} \cdot 3^8 \cdot 5^4 \cdot 7^2 \cdot 11 \cdot 13 \cdot 17 \cdot 19$, do đó thừa số $2$ xuất hiện $18$ lần và thừa số $5$ xuất hiện $4$ lần. Vậy $20!$ có $4$ chữ số 0 ở cuối.

Đoạn mã sau tính số lượng thừa số $5$ trong $n!$ bằng cách chia $n$ cho $5,5^2,5^3$ v.v.

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;

    int ans = 0;
    for (int i = 5; i <= n; i *= 5) {
        ans += n / i;
    }
    cout << ans << "\n";
}
```
