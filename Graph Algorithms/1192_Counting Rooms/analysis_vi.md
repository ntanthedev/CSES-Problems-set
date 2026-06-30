# 1192 - Đếm Phòng

Ta giải bài toán bằng cách duyệt qua từng ô trên bản đồ đồng thời ghi nhớ số lượng phòng riêng biệt đã gặp. Nếu ô đó là tường hoặc ô phòng đã được thăm, ta tiếp tục đến vị trí tiếp theo. Ngược lại, ta đang ở một ô thuộc một phòng chưa được thăm. Ta tăng bộ đếm số phòng riêng biệt và đánh dấu tất cả các vị trí trong phòng này đã được thăm bằng cách sử dụng duyệt theo chiều sâu (DFS).

Điều này tương ứng với việc tìm số lượng thành phần liên thông trong một đồ thị được xác định bởi bản đồ.

Độ phức tạp thời gian của lời giải là $O(nm)$ vì ta duyệt qua $nm$ ô trong vòng lặp chính và tổng số ô được duyệt bởi DFS là $nm$.

```cpp
#include <iostream>
using namespace std;
const int MN = 1001;
string building[MN];
int n, m;

void dfs(int r, int c) {
    if (building[r][c] != '.') return;
    building[r][c] = '#';
    pair<int, int> deltas[]{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    for (auto [dr, dc] : deltas) {
        int new_r = r + dr;
        int new_c = c + dc;
        if (new_r >= 0 && new_r < n && new_c >= 0 && new_c < m) {
            dfs(new_r, new_c);
        }
    }
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        cin >> building[i];
    }

    int n_rooms = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (building[i][j] == '.') {
                ++n_rooms;
                dfs(i, j);
            }
        }
    }
    cout << n_rooms << endl;
}
```
