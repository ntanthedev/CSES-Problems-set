# 1193 - Mê Cung

Ta bắt đầu bằng cách xây dựng một đồ thị tương ứng với mê cung. Trong đồ thị này, mỗi đỉnh tương ứng với một ô trong mê cung. Hai đỉnh được nối với nhau bởi một cạnh nếu và chỉ nếu các ô tương ứng có chung một cạnh và không có ô nào là tường. Tất cả các cạnh đều có độ dài đơn vị.

Độ dài đường đi ngắn nhất trong đồ thị như vậy có thể được tìm bằng thuật toán tìm kiếm theo chiều rộng (BFS). Ta cũng được yêu cầu xây dựng đường đi ngắn nhất. Để làm điều này, ta sửa đổi BFS một chút.

Khi xử lý một đỉnh $x$ và thêm một đỉnh mới $y$ vào hàng đợi BFS, ta cũng lưu trữ một số thông tin bổ sung mà ta gán với đỉnh $y$:

* Vị trí của $x$. Thông tin này được lưu trong mảng `previous` và tương ứng với vị trí áp chót trong đường đi ngắn nhất từ `A` đến $y$.
* Hướng di chuyển đến $y$. Thông tin này được lưu trong mảng `last_letter` và tương ứng với bước di chuyển cuối cùng trong đường đi ngắn nhất từ `A` đến $y$.

Sau khi hoàn thành BFS, ta xây dựng đường đi ngắn nhất theo thứ tự ngược lại. Để làm điều này, ta bắt đầu từ `B` và lần theo các vị trí trong `previous` cho đến khi đến được `A`. Điều này có nghĩa là ta đi theo đường đi ngắn nhất từ điểm kết thúc đến điểm bắt đầu. Với mỗi vị trí đã thăm (ngoại trừ `A`), ta thêm ký tự trong `last_letter` vào xâu `ans`.

Khi hoàn thành việc này, ta đảo ngược `ans` và in ra.

Số cạnh trong đồ thị và độ dài đường đi ngắn nhất đều là $O(nm)$ nên độ phức tạp thời gian tổng thể cũng là $O(nm)$.

```cpp
#include <algorithm>
#include <iostream>
#include <queue>
#include <tuple>
using namespace std;
const int N = 1001;
string grid[N];
bool visited[N][N];
pair<int, int> previous[N][N];
char last_letter[N][N];

tuple<int, int, char> moves[]{
    {0, 1, 'R'}, {1, 0, 'D'}, {0, -1, 'L'}, {-1, 0, 'U'}};

int main() {
    int n, m;
    cin >> n >> m;

    pair<int, int> a;
    pair<int, int> b;
    for (int i = 0; i < n; ++i) {
        cin >> grid[i];
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == 'A') a = {i, j};
            if (grid[i][j] == 'B') b = {i, j};
        }
    }

    queue<pair<int, int>> queue;
    queue.push(a);
    visited[a.first][a.second] = true;

    while (!queue.empty()) {
        auto [r, c] = queue.front();
        queue.pop();
        for (auto [delta_r, delta_c, letter] : moves) {
            int new_r = r + delta_r;
            int new_c = c + delta_c;
            if (new_r >= 0 && new_r < n && new_c >= 0 && new_c < m) {
                if (grid[new_r][new_c] == '#') continue;
                if (visited[new_r][new_c]) continue;
                visited[new_r][new_c] = true;
                previous[new_r][new_c] = {r, c};
                last_letter[new_r][new_c] = letter;
                queue.emplace(new_r, new_c);
            }
        }
    }

    if (!visited[b.first][b.second]) {
        cout << "NO\n";
        return 0;
    }
    string ans;
    auto pos = b;
    while (pos != a) {
        auto [r, c] = pos;
        ans += last_letter[r][c];
        pos = previous[r][c];
    }
    reverse(ans.begin(), ans.end());
    cout << "YES\n";
    cout << ans.size() << '\n';
    cout << ans << '\n';
}
```
