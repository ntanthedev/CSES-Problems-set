# 2183 - Tổng Thiếu của Các Đồng Xu

Giả sử ta có thể tạo mọi tổng $1,2,\dots,k$ bằng một tập con các đồng xu. Khi đó, nếu ta thêm một đồng xu mới có giá trị $x$ không vượt quá $k+1$, ta có thể tạo mọi tổng $1,2,\dots,k+x$, nhưng nếu giá trị lớn hơn $k+1$, ta không thể tạo tổng $k+1$ sau khi thêm đồng xu đó.

Ta có thể bắt đầu với tập rỗng, duyệt qua các đồng xu theo thứ tự tăng dần giá trị và cố gắng mở rộng tập tại mỗi đồng xu. Hoặc ta có thể thêm đồng xu vào tập và tăng tổng lên, hoặc phát hiện rằng không thể thêm đồng xu nào nữa và đã tìm ra lời giải.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

int main() {
    int n;
    cin >> n;

    vector<int> values(n);
    for (int i = 0; i < n; i++) {
        cin >> values[i];
    }
    sort(values.begin(), values.end());

    ll largest = 0;
    for (int i = 0; i < n; i++) {
        if (values[i] > largest + 1) {
            break;
        }
        largest += values[i];
    }
    cout << largest + 1 << "\n";
}
```
