# 3420 - Mảng Con Các Giá Trị Phân Biệt

Ta tính số lượng mảng con hợp lệ kết thúc tại mỗi vị trí trong mảng. Tổng các giá trị này là đáp án của bài toán.

Biến `left_pos` lưu vị trí bên trái của một mảng con hợp lệ. Khi ta gặp một số đã xuất hiện trước đó trong mảng, ta cập nhật biến này nếu cần thiết.

```cpp
#include <iostream>
#include <map>
using namespace std;
using ll = long long;

int main() {
    int n;
    cin >> n;

    map<int, int> last_pos;
    int left_pos = 1;
    ll count = 0;

    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        left_pos = max(left_pos, last_pos[x] + 1);
        count += i - left_pos + 1;
        last_pos[x] = i;
    }

    cout << count << "\n";
}
```
