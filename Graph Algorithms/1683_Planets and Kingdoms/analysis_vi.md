# 1683 - Các hành tinh và vương quốc

Nhiệm vụ của ta là xác định các thành phần liên thông mạnh trong một đồ thị.
Ta sử dụng thuật toán Kosaraju để tìm các thành phần trong thời gian $O(n+m)$.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> graph;
vector<vector<int>> graph_rev;

vector<int> order;
vector<int> seen;

void find_order(int node) {
    if (seen[node]) return;
    seen[node] = 1;
    for (auto next_node : graph[node]) {
        find_order(next_node);
    }
    order.push_back(node);
}

vector<int> component;

void find_component(int node, int id) {
    if (component[node]) return;
    component[node] = id;
    for (auto next_node : graph_rev[node]) {
        find_component(next_node, id);
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    graph.resize(n + 1);
    graph_rev.resize(n + 1);

    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph_rev[b].push_back(a);
    }

    seen.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        find_order(i);
    }

    reverse(order.begin(), order.end());
    int count = 0;
    component.resize(n + 1);
    for (auto node : order) {
        if (component[node]) continue;
        count++;
        find_component(node, count);
    }

    cout << count << "\n";
    for (int i = 1; i <= n; i++) {
        cout << component[i] << " ";
    }
    cout << "\n";
}
```

# Tài liệu tham khảo

* [CPHB (Competitive Programmer's Handbook)](http://cses.fi/book), Chương 17
