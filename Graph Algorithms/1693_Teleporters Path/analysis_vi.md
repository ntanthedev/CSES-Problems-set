# 1693 - Đường đi của các Cổng dịch chuyển

Nhiệm vụ của chúng ta là tìm một đường đi Euler trong một đồ thị có hướng.
Có hai điều kiện phải thỏa mãn để đồ thị có đường đi Euler.

Đầu tiên, nếu ta thêm một cạnh mới từ đỉnh $n$ đến đỉnh $1$,
thì bậc vào và bậc ra của mỗi đỉnh phải bằng nhau.

Thứ hai, tất cả các cạnh phải nằm trong cùng một thành phần liên thông.

Đoạn mã sau sử dụng quay lui để xây dựng một chu trình Euler.
Nó đệ quy tạo ra các chu trình bắt đầu và kết thúc tại cùng một đỉnh,
và kết hợp các chu trình đó để tạo thành một chu trình Euler.
Đoạn mã chạy trong thời gian $O(n+m)$.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> graph;
vector<int> cycle;

void fail() {
    cout << "IMPOSSIBLE\n";
    exit(0);
}

void find_cycle(int node) {
    while (!graph[node].empty()) {
        int next_node = graph[node].back();
        graph[node].pop_back();
        find_cycle(next_node);
    }
    cycle.push_back(node);
}

int main() {
    int n, m;
    cin >> n >> m;

    graph.resize(n + 1);
    vector<int> in_degree(n + 1);
    vector<int> out_degree(n + 1);
    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        out_degree[a]++;
        in_degree[b]++;
    }

    in_degree[1]++;
    out_degree[n]++;
    for (int i = 1; i <= n; i++) {
        if (in_degree[i] != out_degree[i]) fail();
    }

    find_cycle(1);
    if (cycle.size() != m + 1) fail();

    reverse(cycle.begin(), cycle.end());
    for (auto node : cycle) {
        cout << node << " ";
    }
    cout << "\n";
}
```

# Tài liệu tham khảo

* [CPHB (Sổ tay Lập trình viên)](http://cses.fi/book), Chương 19
