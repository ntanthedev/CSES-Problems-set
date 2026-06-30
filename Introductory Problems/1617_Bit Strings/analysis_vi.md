# 1617 - Xâu nhị phân

Đáp án có thể được tính bằng công thức $2^n$ vì có hai cách để chọn mỗi bit.

```cpp
#include <iostream>
#include <vector>
using namespace std;
const int M = 1000000007;

int main() {
    int n;
    cin >> n;

    int ans = 1;
    for (int i = 1; i <= n; i++) {
        ans = ans * 2 % M;
    }
    cout << ans << "\n";
}
```
