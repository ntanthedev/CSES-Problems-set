# 1669 - Round Trip

Nhiệm vụ của chúng ta là tìm một chu trình trong đồ thị vô hướng.
Đoạn mã sau sử dụng tìm kiếm theo chiều sâu được sửa đổi để
duy trì một đường đi từ đỉnh bắt đầu đến đỉnh hiện tại
trong cây tìm kiếm theo chiều sâu.
Khi chúng ta ghé thăm một đỉnh đã được thăm trước đó,
chúng ta xây dựng một chu trình bao gồm đỉnh đó.

Xét một đỉnh $x$ là đỉnh đầu tiên trong một chu trình
mà chúng ta ghé thăm trong quá trình tìm kiếm.
Vì có một đường đi từ đỉnh $x$ đến chính nó đi qua
các đỉnh chưa được thăm, đường đi trong cây tìm kiếm theo chiều sâu sẽ
cuối cùng chứa đỉnh $x$ hai lần.
Điều này cho phép chúng ta xây dựng một chu trình.

Chúng ta duyệt qua tất cả các đỉnh trong đồ thị
và bắt đầu tìm kiếm từ mọi đỉnh chưa được thăm.
Nếu chúng ta không tìm thấy chu trình, thì không có chu trình nào trong đồ thị.

Đoạn mã chạy trong thời gian $O(n + m)$.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> graph;
vector<bool> visited;
vector<int> path;

void cycle_search(int node, int parent) {
    path.push_back(node);

    if (visited[node]) {
        auto it = find(path.begin(), path.end(), node);
        cout << path.end() - it << "\n";

        auto cycle = vector<int>(it, path.end());
        for (auto node : cycle) {
            cout << node << " ";
        }
        cout << "\n";

        exit(0);
    }

    visited[node] = true;

    for (auto next_node : graph[node]) {
        if (next_node != parent) {
            cycle_search(next_node, node);
        }
    }

    path.pop_back();
}

int main() {
    int n, m;
    cin >> n >> m;

    graph.resize(n + 1);
    for (int i = 1; i <= m; ++i) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    visited.resize(n + 1);
    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            cycle_search(i, 0);
        }
    }

    cout << "IMPOSSIBLE\n";
}
```
