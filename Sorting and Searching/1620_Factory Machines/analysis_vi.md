# 1620 - Máy Móc Trong Nhà Máy

Chúng ta sử dụng một hàm `check` duyệt qua các máy và đếm tổng số sản phẩm chúng có thể sản xuất trong $x$ đơn vị thời gian. Hàm trả về true nếu số lượng sản phẩm ít nhất bằng số lượng sản phẩm yêu cầu.

Chúng ta có thể giải quyết bài toán hiệu quả bằng cách sử dụng tìm kiếm nhị phân và gọi hàm trên. Ta tìm thời gian $k$ lớn nhất mà không thể sản xuất đủ sản phẩm. Khi đó $k+1$ là đáp án của bài toán.

Thuật toán chạy trong $O(n \log M)$ thời gian, trong đó $M$ là đáp án tối đa có thể. Trong đoạn mã dưới đây $M=10^{18}$ hoạt động tốt với các ràng buộc đã cho trong đề bài.

```cpp
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

int main() {
    int n, t;
    cin >> n >> t;

    vector<int> times(n);
    for (int i = 0; i < n; i++) {
        cin >> times[i];
    }

    auto check = [&](ll x) {
        ll total = 0;
        for (int i = 0; i < n; i++) {
            total += x / times[i];
            if (total >= t) return true;
        }
        return false;
    };

    ll k = 0;
    for (ll b = 1e18; b >= 1; b /= 2) {
        while (!check(k + b)) k += b;
    }
    cout << k + 1 << "\n";
}
```
