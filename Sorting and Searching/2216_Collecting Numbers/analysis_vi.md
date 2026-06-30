# 2216 - Thu Thập Số

Nếu số $x$ đứng trước số $x-1$ trong mảng, ta phải bắt đầu một lượt mới sau khi thu thập số $x-1$.

Dựa vào nhận xét này, ta có thể kiểm tra tất cả các cặp số liên tiếp và đếm số lượt mới cần thêm. Điều này có thể thực hiện hiệu quả bằng cách lưu vị trí của mỗi số trong một mảng.

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> pos(n + 1);
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        pos[x] = i;
    }

    int rounds = 1;
    for (int i = 2; i <= n; i++) {
        if (pos[i] < pos[i - 1]) rounds++;
    }
    cout << rounds << "\n";
}
```
