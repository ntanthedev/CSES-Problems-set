# 1689 - Hành trình của quân mã

# Lời giải 1

Ta sử dụng thuật toán quay lui đệ quy để khám phá các hành trình bộ phận khả dĩ
cho đến khi tìm được một hành trình hoàn chỉnh.
Đoạn code sau sử dụng quy tắc Warnsdorf để tăng hiệu quả tìm kiếm.
Quy tắc này xác định thứ tự mà ta xét các nước đi khả dĩ của quân mã
trong quá trình tìm kiếm.

Gọi *bậc* của một ô là số ô trống mà quân mã có thể di chuyển đến từ ô đó.
Sử dụng quy tắc Warnsdorf, ta duyệt các nước đi theo thứ tự tăng dần
của bậc của ô đích.

```cpp
#include <algorithm>
#include <array>
#include <iostream>
#include <vector>
using namespace std;

#define N 8

vector<vector<int>> grid(N, vector<int>(N));

vector<int> dy = {1, 1, -1, -1, 2, 2, -2, -2};
vector<int> dx = {2, -2, 2, -2, 1, -1, 1, -1};

int degree(int y, int x) {
    int count = 0;
    for (int d = 0; d < N; d++) {
        int new_y = y + dy[d];
        int new_x = x + dx[d];
        if (new_y < 0 || new_y >= N || new_x < 0 || new_x >= N) continue;
        if (grid[new_y][new_x]) continue;
        count++;
    }
    return count;
}

void print() {
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            cout << grid[y][x] << " ";
        }
        cout << "\n";
    }
}

void search(int y, int x, int c) {
    if (grid[y][x]) return;
    grid[y][x] = c;

    if (c == N * N) {
        print();
        exit(0);
    }

    vector<array<int, 3>> choices;
    for (int d = 0; d < 8; d++) {
        int new_y = y + dy[d];
        int new_x = x + dx[d];
        if (new_y < 0 || new_y >= N || new_x < 0 || new_x >= N) continue;
        if (grid[new_y][new_x]) continue;
        choices.push_back({degree(new_y, new_x), new_y, new_x});
    }

    sort(choices.begin(), choices.end());
    for (auto [_, new_y, new_x] : choices) {
        search(new_y, new_x, c + 1);
    }

    grid[y][x] = 0;
}

int main() {
    int x, y;
    cin >> x >> y;

    search(y - 1, x - 1, 1);
}
```

# Lời giải 2

Có một lời giải đơn giản hơn nếu ta đã có sẵn một hành trình quân mã được tính trước
với yêu cầu bổ sung rằng quân mã có thể đi từ ô cuối cùng trở về ô đầu tiên.
Sau khi tìm được hành trình như vậy, ta có thể dễ dàng thay đổi ô bắt đầu
bằng cách dịch chuyển tất cả các phần tử trong lưới.

Để tìm hành trình, ta có thể sử dụng thuật toán từ lời giải thứ nhất
với một sửa đổi nhỏ.

```cpp
#include <iostream>
#include <vector>
using namespace std;

#define N 8

vector<vector<int>> grid = {
    {1, 62, 59, 42, 37, 46, 49, 44}, {60, 41, 64, 53, 58, 43, 36, 47},
    {63, 2, 61, 38, 23, 48, 45, 50}, {40, 19, 54, 57, 52, 7, 24, 35},
    {3, 56, 39, 20, 25, 22, 51, 8},  {18, 13, 16, 55, 6, 29, 34, 31},
    {15, 4, 11, 26, 21, 32, 9, 28},  {12, 17, 14, 5, 10, 27, 30, 33}};

int main() {
    int x, y;
    cin >> x >> y;

    int shift = grid[y - 1][x - 1] - 1;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int step = grid[i][j] - shift;
            if (step <= 0) step += N * N;
            cout << step << " ";
        }
        cout << "\n";
    }
}
```

# Tài liệu tham khảo

* [Hành trình quân mã (Wikipedia)](https://en.wikipedia.org/wiki/Knight's_tour)
* H. C. von Warnsdorf. Des Rösselsprunges einfachste und allgemeinste Lösung.
  Schmalkalden, 1823.
