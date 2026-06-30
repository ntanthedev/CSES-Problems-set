# 1756 - Đồ Thị Vô Hướng Định Hướng Phi Chu Trình

Có một lời giải đơn giản một cách bất ngờ cho bài toán này. Nếu chúng ta định hướng mỗi cạnh từ
đỉnh có chỉ số nhỏ hơn đến đỉnh có chỉ số lớn hơn, đồ thị thu được sẽ là phi chu trình.
Sẽ không có chu trình vì mỗi cạnh đều đi đến một đỉnh có chỉ số lớn hơn và không
có cạnh nào đi đến đỉnh có chỉ số nhỏ hơn.

```cpp
#include <iostream>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= m; ++i) {
        int a, b;
        cin >> a >> b;
        cout << min(a, b) << ' ' << max(a, b) << '\n';
    }
}
```
