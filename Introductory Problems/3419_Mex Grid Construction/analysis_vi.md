# 3419 - Mex Grid Construction

Một nhận xét hữu ích là mọi số trong lưới đều nhỏ hơn $2n$ vì có ít hơn $n$ số được đặt ở hàng và cột phía trước. Do đó, ta có thể xác định số bằng cách dùng một vector và các vòng lặp for đơn giản. Đoạn mã sau chạy trong thời gian $O(n^3)$.

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<vector<int>> grid(n, vector<int>(n));

    for (int y = 0; y < n; y++) {
        for (int x = 0; x < n; x++) {
            vector<bool> seen(2 * n);
            for (int i = 0; i < y; i++) {
                seen[grid[i][x]] = true;
            }
            for (int i = 0; i < x; i++) {
                seen[grid[y][i]] = true;
            }
            while (seen[grid[y][x]]) {
                grid[y][x]++;
            }
            cout << grid[y][x] << " ";
        }
        cout << "\n";
    }
}
```
