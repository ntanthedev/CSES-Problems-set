# 1623 - Chia táo

Tổng số cách chia là $2^n$. Vì $n$ tối đa là $20$, ta có thể duyệt qua tất cả các cách chia một cách hiệu quả và chọn cách chia có chênh lệch tổng khối lượng nhỏ nhất.

Mỗi cách chia $n$ quả táo tương ứng với một xâu nhị phân độ dài $n$ trong đó mỗi bit xác định nhóm của một quả táo. Ví dụ, nếu khối lượng là $[3, 2, 7, 4, 1]$, xâu nhị phân $00101$ có nghĩa là nhóm thứ nhất có khối lượng $[3, 2, 4]$ và nhóm thứ hai có khối lượng $[7, 1]$.

```cpp
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

int main() {
    int n;
    cin >> n;
    vector<int> p(n);
    for (int i = 0; i < n; i++) cin >> p[i];

    ll diff = 1e9;
    for (int b = 0; b < (1 << n); b++) {
        ll sum1 = 0, sum2 = 0;
        for (int i = 0; i < n; i++) {
            if (b & (1 << i)) {
                sum1 += p[i];
            } else {
                sum2 += p[i];
            }
        }
        diff = min(diff, abs(sum1 - sum2));
    }

    cout << diff << "\n";
}
```
