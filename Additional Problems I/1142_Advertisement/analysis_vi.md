# 1142 - Quảng Cáo

Một nhận xét quan trọng là một tấm biển quảng cáo tối ưu sẽ luôn được chặn từ phía trên bởi ít nhất một tấm ván. Chúng ta có thể duyệt qua các tấm ván và coi mỗi tấm là tấm ván chặn trên này. Chiều cao của tấm biển quảng cáo tương ứng sẽ bằng chiều cao của tấm ván hiện tại. Về chiều ngang, chúng ta sẽ mở rộng tấm biển quảng cáo càng lớn càng tốt, và nó sẽ trải dài qua mỗi tấm ván liền kề không thấp hơn tấm ván hiện tại.

Chúng ta sẽ tính hai vị trí cho mỗi tấm ván: chỉ số của tấm ván trước đó và tiếp theo có chiều cao thấp hơn. Điều này có thể được thực hiện trong thời gian tuyến tính, làm cho độ phức tạp thời gian của giải pháp là $O(n)$.

```cpp
#include <iostream>
using namespace std;
using ll = long long;

const int N = 200002;
int k[N];
int prev_lower[N], next_lower[N];

int main() {
    int n;
    cin >> n;

    for (int i = 1; i <= n; ++i) {
        cin >> k[i];
    }

    for (int i = 1; i <= n; ++i) {
        prev_lower[i] = i - 1;
        while (prev_lower[i] >= 0 && k[prev_lower[i]] >= k[i]) {
            prev_lower[i] = prev_lower[prev_lower[i]];
        }
    }

    for (int i = n; i >= 1; --i) {
        next_lower[i] = i + 1;
        while (next_lower[i] <= n && k[next_lower[i]] >= k[i]) {
            next_lower[i] = next_lower[next_lower[i]];
        }
    }

    ll ans = 0;
    for (int i = 1; i <= n; ++i) {
        ans = max(ans, 1ll * (next_lower[i] - prev_lower[i] - 1) * k[i]);
    }

    cout << ans << '\n';
}
```
