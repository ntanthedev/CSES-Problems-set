# 1625 - Mô tả đường đi trên lưới

Ta có thể sử dụng thuật toán quay lui đệ quy để giải bài toán. Tuy nhiên, vì số lượng đường đi có thể là rất lớn, ta phải tỉa nhánh để thuật toán đủ hiệu quả.

Ta duy trì một mảng `grid` chứa trạng thái của mỗi ô. Nếu trạng thái là 0, ô đó trống và ta có thể đi vào. Nếu trạng thái là 1, ô đó là tường hoặc ta đã đi qua. Lưu ý rằng mảng có một đường viền các ô tường giúp việc cài đặt tìm kiếm dễ dàng hơn.

Có hai tối ưu trong quá trình tìm kiếm. Thứ nhất, ta luôn kết thúc tìm kiếm sau khi đi đến ô dưới cùng bên trái. Nếu ta đã đi qua tất cả các ô khác trước đó, ta đã tìm được một nghiệm hợp lệ. Nếu không, rõ ràng ta không thể tạo được nghiệm hợp lệ vì đã đi đến ô cuối cùng quá sớm.

Thứ hai, nếu ta đang ở một ô mà cả hai ô kề theo một hướng đều có trạng thái 0 và cả hai ô kề theo hướng khác đều có trạng thái 1, ta kết thúc tìm kiếm. Trong trường hợp này, lưới có ít nhất hai thành phần riêng biệt gồm các ô trống, và không thể đi qua tất cả các ô được nữa.

```cpp
#include <iostream>
using namespace std;

const int N = 7;

int grid[N + 2][N + 2];
string path;
int total;

void search(int y, int x, int c) {
    if (grid[y][x]) return;

    if (y == N && x == 1) {
        if (c == N * N) total++;
        return;
    }

    bool down = grid[y + 1][x];
    bool up = grid[y - 1][x];
    bool left = grid[y][x - 1];
    bool right = grid[y][x + 1];
    if (down && up && !left && !right) return;
    if (!down && !up && left && right) return;

    char d = path[c - 1];
    grid[y][x] = 1;
    if (d == '?' || d == 'D') search(y + 1, x, c + 1);
    if (d == '?' || d == 'U') search(y - 1, x, c + 1);
    if (d == '?' || d == 'L') search(y, x - 1, c + 1);
    if (d == '?' || d == 'R') search(y, x + 1, c + 1);
    grid[y][x] = 0;
}

int main() {
    for (int i = 0; i <= N + 1; i++) {
        grid[0][i] = grid[N + 1][i] = 1;
        grid[i][0] = grid[i][N + 1] = 1;
    }

    cin >> path;
    search(1, 1, 1);
    cout << total << "\n";
}
```
