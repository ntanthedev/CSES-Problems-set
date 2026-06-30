# 1099 - Trò chơi cầu thang

Trò chơi này tương ứng với nim trong đó ta chỉ lấy mỗi giá trị ở vị trí chẵn vào tổng xor. Chính xác hơn, ta chỉ xét các bậc có chỉ số chẵn.

Nếu một người chơi di chuyển $c$ đồng xu từ bậc $k$ xuống bậc $k-1$ với $k$ lẻ, đối thủ luôn có thể hủy nước đi đó bằng cách di chuyển $c$ đồng xu từ bậc $k-1$ xuống $k-2$ ngay sau đó. Do đó, ta có thể bỏ qua các bậc có chỉ số lẻ và chơi nim chỉ với các bậc có chỉ số chẵn.

```cpp
#include <iostream>
using namespace std;

int main() {
    int t;
    cin >> t;

    for (int ti = 1; ti <= t; ti++) {
        int n;
        cin >> n;
        int sum = 0;
        for (int i = 1; i <= n; i++) {
            int x;
            cin >> x;
            if (i % 2 == 0) sum ^= x;
        }
        cout << (sum != 0 ? "first" : "second") << "\n";
    }
}
```
