# 1727 - Candy Lottery

Gọi $f(i)$ là xác suất mỗi đứa trẻ nhận được tối đa $i$ kẹo. Vì xác suất một đứa trẻ nhận được tối đa $i$ kẹo là $i/k$, ta có thể tính xác suất theo công thức

$$f(i)=(i/k)^n.$$

Khi đó, xác suất số kẹo tối đa bằng $i$ là

$$f(i)-f(i-1)$$

vì ta muốn có ít nhất một đứa trẻ nhận được đúng $i$ kẹo và không đứa trẻ nào nhận được nhiều hơn $i$ kẹo. Ta tính xác suất này cho mỗi giá trị tối đa có thể để tìm số kẹo tối đa kỳ vọng.

```cpp
#include <cmath>
#include <iostream>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    auto f = [&](int i) {
        return pow(1.0 * i / k, n);
    };

    double answer = 0;
    for (int i = k; i >= 1; i--) {
        answer += i * (f(i) - f(i - 1));
    }
    cout.precision(6);
    cout << fixed << answer << "\n";
}
```
