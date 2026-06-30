# 1691 - Phát thư

Nhiệm vụ của ta là tìm một chu trình Euler trong đồ thị.
Tồn tại một chu trình nếu mọi đỉnh đều có bậc chẵn và
tất cả các cạnh đều thuộc cùng một thành phần liên thông.

Đoạn code sau sử dụng quay lui để xây dựng một chu trình Euler.
Nó đệ quy tạo ra các chu trình bắt đầu và kết thúc tại cùng một đỉnh,
và kết hợp các chu trình đó để tạo thành một chu trình Euler.

Đoạn code chạy trong thời gian $O(n+m \log n)$ vì sử dụng tập (set) để
lưu danh sách kề.
Có thể cài đặt cùng một thuật toán trong thời gian $O(n+m)$
một cách phức tạp hơn bằng cách dùng vector thay vì tập.

```cpp
#include <iostream>
#include <set>
#include <vector>
using namespace std;

vector<set<int>> graph;
vector<int> cycle;

void fail() {
    cout << "IMPOSSIBLE\n";
    exit(0);
}

void find_cycle(int node) {
    while (!graph[node].empty()) {
        int next_node = *graph[node].begin();
        graph[node].erase(next_node);
        graph[next_node].erase(node);
        find_cycle(next_node);
    }
    cycle.push_back(node);
}

int main() {
    int n, m;
    cin >> n >> m;

    graph.resize(n + 1);
    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].insert(b);
        graph[b].insert(a);
    }

    for (int i = 1; i <= n; i++) {
        if (graph[i].size() % 2 != 0) fail();
    }

    find_cycle(1);
    if (cycle.size() != m + 1) fail();

    for (auto node : cycle) {
        cout << node << " ";
    }
    cout << "\n";
}
```

# Tài liệu tham khảo

* [CPHB (Competitive Programmer's Handbook)](http://cses.fi/book), Chương 19
