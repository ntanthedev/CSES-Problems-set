# 1624 - Bàn cờ và Quân hậu

Đoạn mã sau cài đặt một thuật toán quay lui để đếm số nghiệm. Hàm `search` thêm một quân hậu vào hàng $y$ và sau đó thêm quân hậu tiếp theo một cách đệ quy. Khi tất cả các quân hậu đã được đặt lên bàn cờ, một nghiệm mới đã được tìm thấy.

Để đảm bảo không có hai quân hậu nào tấn công nhau, mã sử dụng ba mảng:

* `col` theo dõi các cột có quân hậu
* `diag1` theo dõi các đường chéo (hướng thứ nhất) có quân hậu
* `diag2` theo dõi các đường chéo (hướng thứ hai) có quân hậu

```cpp
#include <iostream>
using namespace std;

const int N = 8;

string grid[N];
int total;
bool col[N], diag1[2 * N], diag2[2 * N];

void search(int y) {
    if (y == N) {
        total++;
        return;
    }
    for (int x = 0; x < N; x++) {
        if (grid[y][x] == '*') {
            continue;
        }
        if (col[x] || diag1[x + y] || diag2[y - x + N]) {
            continue;
        }
        col[x] = diag1[x + y] = diag2[y - x + N] = true;
        search(y + 1);
        col[x] = diag1[x + y] = diag2[y - x + N] = false;
    }
}

int main() {
    for (auto &row : grid) {
        cin >> row;
    }
    search(0);
    cout << total << "\n";
}
```

## Tài liệu tham khảo

* [Eight queens puzzle (Wikipedia)](https://en.wikipedia.org/wiki/Eight_queens_puzzle)
