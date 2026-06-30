# 1667 - Message Route

Mạng máy tính định nghĩa một đồ thị vô hướng với các cạnh có độ dài đơn vị.
Trong đồ thị như vậy, độ dài đường đi ngắn nhất có thể được tìm bằng
thuật toán tìm kiếm theo chiều rộng (BFS).

Chúng ta cũng được yêu cầu xây dựng đường đi ngắn nhất. Để làm điều này,
chúng ta sửa đổi BFS một chút.
Khi xử lý một máy tính $x$ và thêm một máy tính mới $y$ vào
hàng đợi BFS, chúng ta cũng lưu chỉ số của $x$ cùng với $y$. Giá trị này được lưu trong
mảng `parent` và tương ứng với máy tính áp chót
trong đường đi ngắn nhất từ $A$ đến $y$.

Sau đó, chúng ta xây dựng đường đi ngắn nhất theo thứ tự ngược bằng cách đi theo
đường đi được định nghĩa bởi mảng `parent` từ `B` đến `A`.

Độ phức tạp thời gian của lời giải là $O(n + m)$.

```cpp
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
const int N = 100001;

vector<int> graph[N];
bool visited[N];
int parent[N];

int main() {
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    queue<int> queue;
    queue.push(1);
    visited[1] = true;

    while (!queue.empty()) {
        int x = queue.front();
        queue.pop();
        for (int y : graph[x]) {
            if (visited[y]) continue;
            visited[y] = true;
            parent[y] = x;
            queue.push(y);
        }
    }

    if (!visited[n]) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    vector<int> ans;
    int x = n;
    while (x != 0) {
        ans.push_back(x);
        x = parent[x];
    }
    reverse(ans.begin(), ans.end());

    cout << ans.size() << '\n';
    for (int x : ans) {
        cout << x << ' ';
    }
    cout << '\n';
}
```
