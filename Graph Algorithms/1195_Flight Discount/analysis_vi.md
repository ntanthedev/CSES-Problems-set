# 1195 - Giảm Giá Vé Máy Bay

Ta xây dựng một đồ thị gồm $2n$ đỉnh được sắp xếp trong hai lớp.

Mỗi thành phố được biểu diễn bởi hai đỉnh. Đỉnh $i$ tương ứng với thành phố $i$ trước khi sử dụng phiếu giảm giá, và đỉnh $n+i$ tương ứng với thành phố $i$ sau khi sử dụng phiếu giảm giá.

Với mỗi chuyến bay, ta tạo ba cạnh. Khi có một chuyến bay từ thành phố $a$ đến thành phố $b$ với trọng số $x$, ta tạo các cạnh $(a,b,x)$, $(a,n+b,\lfloor x/2 \rfloor)$ và $(n+a,n+b,x)$. Cạnh thứ hai cho phép ta sử dụng phiếu giảm giá một lần.

Trong đồ thị trên, độ dài đường đi ngắn nhất từ đỉnh $1$ đến đỉnh $2n$ biểu diễn tuyến đường rẻ nhất với phiếu giảm giá.

```cpp
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
using ll = long long;

const ll INF = 1e18;

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> graph(2 * n + 1);

    for (int i = 1; i <= m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        graph[a].emplace_back(b, c);
        graph[n + a].emplace_back(n + b, c);
        graph[a].emplace_back(n + b, c / 2);
    }

    vector<ll> distance(2 * n + 1, INF);
    vector<bool> visited(2 * n + 1);

    priority_queue<pair<ll, int>> queue;
    queue.emplace(0, 1);
    distance[1] = 0;

    while (!queue.empty()) {
        int node = queue.top().second;
        queue.pop();

        if (visited[node]) continue;
        visited[node] = true;

        for (auto [next_node, weight] : graph[node]) {
            ll new_distance = distance[node] + weight;
            if (new_distance < distance[next_node]) {
                distance[next_node] = new_distance;
                queue.emplace(-new_distance, next_node);
            }
        }
    }

    cout << distance[2 * n] << "\n";
}
```
