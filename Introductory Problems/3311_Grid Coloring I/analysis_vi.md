# 3311 - Grid Coloring I

Ta có thể giải bài toán một cách tham lam bằng cách duyệt qua lưới từ trên xuống dưới và từ trái sang phải.

Với mỗi ô, ta chọn ký tự đầu tiên không phải là ký tự ban đầu của ô đó
và cũng không trùng với ký tự bên trái hoặc ký tự phía trên.
Vì có bốn ký tự khả dĩ, ta luôn có thể tìm được một ký tự hợp lệ.

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<string> grid(n);
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }

    for (int y = 0; y < n; y++) {
        for (int x = 0; x < m; x++) {
            for (int c = 'A'; c <= 'D'; c++) {
                bool fail = false;
                if (grid[y][x] == c) fail = true;
                if (y > 0 && grid[y - 1][x] == c) fail = true;
                if (x > 0 && grid[y][x - 1] == c) fail = true;
                if (!fail) {
                    grid[y][x] = c;
                    break;
                }
            }
            cout << grid[y][x];
        }
        cout << "\n";
    }
}
```
