# 1673 - Điểm số cao nhất

Đầu tiên ta biến đổi nhẹ bài toán: Thay vì tối đa hóa điểm số, ta lấy đối số (negate) của điểm số và tìm cách tối thiểu hóa tổng điểm số. Ta cũng loại bỏ tất cả các phòng không thể đến được từ đỉnh $1$ hoặc không thể đi từ đó đến đỉnh $n$. Điều này được thực hiện bằng cách chạy tìm kiếm theo chiều rộng (BFS) hai lần, từ đỉnh $1$ và từ đỉnh $n$, và lưu các đỉnh còn lại vào bitset `included`.

Sau đó, ta chạy thuật toán Bellman-Ford trong $n$ vòng lặp để tìm đường đi ngắn nhất từ đỉnh $1$ đến đỉnh $n$. Nếu không có khoảng cách nào giảm ở vòng lặp thứ $n$, ta lấy đối số của khoảng cách từ đỉnh $1$ đến đỉnh $n$, in ra và kết thúc. Ngược lại, đồ thị chứa một chu trình âm.

Do cách ta biến đổi đồ thị ở đầu, ta biết rằng có thể đến được chu trình âm từ đỉnh $1$, dùng chu trình để làm điểm số nhỏ tùy ý, và sau đó tiếp tục đến đỉnh $n$. Vì vậy, phát hiện một chu trình âm đồng nghĩa với việc ta có thể làm điểm số nhỏ tùy ý.

Tiền xử lý mất $O(n + m)$ thời gian và độ phức tạp thời gian của thuật toán Bellman-Ford là $O(nm)$.

```cpp
#include <bitset>
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>
using namespace std;
using ll = long long;
const ll INF = 1e18;
const int N = 2501;

bitset<N> bfs(int s, vector<vector<int>>& g) {
    bitset<N> visited;
    queue<int> q;
    q.push(s);
    visited[s] = true;
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int y : g[x]) {
            if (!visited[y]) {
                visited[y] = true;
                q.push(y);
            }
        }
    }
    return visited;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<tuple<int, int, int>> edges;
    vector<vector<int>> g(n + 1);
    vector<vector<int>> rev_g(n + 1);

    for (int i = 1; i <= m; ++i) {
        int a, b, x;
        cin >> a >> b >> x;
        edges.emplace_back(a, b, -x);
        g[a].push_back(b);
        rev_g[b].push_back(a);
    }

    auto included = bfs(1, g) & bfs(n, rev_g);

    vector<ll> distance(n + 1, INF);
    distance[1] = 0;

    for (int i = 1; i <= n; ++i) {
        for (auto [from, to, score] : edges) {
            if (!included[from] || !included[to]) continue;
            ll new_distance = min(distance[to], distance[from] + score);
            if (i == n && new_distance < distance[to]) {
                cout << -1 << '\n';
                return 0;
            }
            distance[to] = new_distance;
        }
    }
    cout << -distance[n] << '\n';
}
```

## Tài liệu tham khảo

* [CPHB (Sổ tay lập trình viên thi đấu)](https://cses.fi/book), Chương 7.3.1, Thuật toán Bellman-Ford
