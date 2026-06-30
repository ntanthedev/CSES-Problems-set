# 1085 - Array Division

Hàm `check` dưới đây nhận một giá trị $s$ và kiểm tra xem ta có thể chia mảng thành $k$ mảng con sao cho tổng mỗi mảng con không vượt quá $s$ hay không. Hàm duyệt mảng từ trái sang phải và tham lam tối đa hóa kích thước của mỗi mảng con.

Ta có thể giải bài toán hiệu quả bằng cách kết hợp tìm kiếm nhị phân và hàm trên. Ta tìm giá trị $s$ lớn nhất sao cho không thể tạo ra các mảng con. Khi đó đáp án của bài toán là $s+1$.

Thuật toán chạy trong $O(n \log M)$ với $M$ là giá trị đáp án lớn nhất có thể. Trong code dưới đây, $M=10^{18}$ hoạt động tốt với các giới hạn đã cho trong đề bài.

```cpp
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> x(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }

    auto check = [&](ll s) {
        int p = 1;
        ll c = 0;
        for (int i = 0; i < n; i++) {
            if (x[i] > s) return false;
            c += x[i];
            if (c > s) {
                p++;
                c = x[i];
            }
        }
        return p <= k;
    };

    ll s = 0;
    for (ll b = 1e18; b >= 1; b /= 2) {
        while (!check(s + b)) s += b;
    }
    cout << s + 1 << "\n";
}
```
