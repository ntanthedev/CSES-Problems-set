# 2422 - Bảng Cửu Chương

Bài toán này có thể được giải hiệu quả bằng tìm kiếm nhị phân. Ta biết rằng đáp án nằm giữa $1$ và $n^2$. Điều này có nghĩa là ta cần $O(\log n^2) = O(\log n)$ lần lặp tìm kiếm nhị phân.

Ta có thể kiểm tra trong $O(n)$ liệu một số có lớn hơn hay nhỏ hơn đáp án hay không bằng cách tính tổng số lượng các số nhỏ hơn hoặc bằng trong mỗi hàng. Do đó, độ phức tạp của thuật toán là $O(n \log n)$.

```cpp
#include <iostream>
using namespace std;
using ll = long long;

int main() {
    ll n;
    cin >> n;

    auto check = [&](ll x) {
        ll amount = 0;
        for (int i = 1; i <= n; ++i) {
            amount += min(n, x / i);
        }
        // There are n * n numbers in the grid.
        // The index of the middle one is n * n / 2 + 1.
        return amount >= n * n / 2 + 1;
    };

    ll l = 1, r = n * n;
    while (l < r) {
        ll mid = (l + r) / 2;
        if (check(mid)) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }

    cout << l << '\n';
}
```
