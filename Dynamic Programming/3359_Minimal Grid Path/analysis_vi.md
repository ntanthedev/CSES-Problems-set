# 3359 - Đường đi lưới nhỏ nhất

Thuật toán gồm $2n-2$ vòng để xây dựng xâu nhỏ nhất tương ứng với một đường đi từ ô trên cùng bên trái đến ô dưới cùng bên phải. Nó duy trì một tiền tố của xâu nhỏ nhất này trong suốt quá trình.

Trong mỗi vòng, ta xét tất cả các vị trí kết thúc có thể của các đường đi tương ứng với tiền tố hiện tại. Tiền tố được mở rộng bằng cách thêm một chữ cái mới. Từ mỗi vị trí kết thúc, ta xét việc di chuyển một bước sang phải và một bước xuống dưới để xác định chữ cái tiếp theo cần thêm vào đường đi.

Điều quan trọng là phải đảm bảo danh sách các vị trí kết thúc chỉ chứa các vị trí phân biệt sau mỗi vòng. Nếu không, thuật toán có thể xử lý cùng một vị trí kết thúc nhiều lần, làm giảm hiệu quả.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<string> grid(n);
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }

    cout << grid[0][0];

    vector<pair<int, int>> level;
    level.emplace_back(0, 0);

    for (int i = 0; i < 2 * n - 2; i++) {
        vector<pair<int, int>> next_level;
        char min_letter = 'Z' + 1;

        auto update_next_level = [&](int y, int x) {
            if (y < n && x < n) {
                char letter = grid[y][x];
                if (letter < min_letter) {
                    next_level.clear();
                    min_letter = letter;
                }
                if (letter == min_letter) {
                    next_level.emplace_back(y, x);
                }
            }
        };

        for (auto [y, x] : level) {
            update_next_level(y + 1, x);
            update_next_level(y, x + 1);
        }

        cout << min_letter;

        level = next_level;
        level.erase(unique(level.begin(), level.end()), level.end());
    }
    cout << "\n";
}
```
