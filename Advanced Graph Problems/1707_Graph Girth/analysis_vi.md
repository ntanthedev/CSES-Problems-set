# 1707 - Chu Trình Nhỏ Nhất

Chúng ta sẽ tìm, với mỗi đỉnh riêng biệt, chu trình ngắn nhất đi qua nó.
Điều này có thể được thực hiện bằng cách bắt đầu tìm kiếm theo chiều rộng (BFS) từ mỗi đỉnh.

Chúng ta có thể coi các đỉnh kề trực tiếp của đỉnh bắt đầu là các *cây* riêng biệt.
Bất cứ khi nào một đỉnh được thêm vào hàng đợi, chúng ta sẽ thêm một cạnh vào cây từ đỉnh
trước đó đến nó. Lưu ý rằng một cây duy nhất sẽ không chứa các chu trình có
chứa đỉnh bắt đầu. Thay vào đó, các chu trình chứa đỉnh bắt đầu được
hình thành bởi các cạnh nối từ một *cây* này sang một *cây* khác.

Sử dụng các nhận xét này, chúng ta có thể tìm chu trình ngắn nhất chứa một đỉnh
cụ thể trong thời gian $O(n+m)$, dẫn đến một thuật toán với độ phức tạp thời gian là
$O(n(n+m))$.

```cpp
#include <iostream>
#include <vector>
using namespace std;

const int INF = 1e9;
const int N = 2501;
vector<int> g[N];

int dist[N], tree[N];

int main() {
    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    int ans = INF;
    for (int i = 1; i <= n; i++) {
        fill(dist, dist + N, -1);
        dist[i] = 0;
        vector<int> q;
        for (int j = 0; j < g[i].size(); ++j) {
            q.push_back(g[i][j]);
            tree[g[i][j]] = j;
            dist[g[i][j]] = 1;
        }
        for (int qi = 0; qi < q.size(); qi++) {
            int s = q[qi];
            for (int nxt : g[s]) {
                if (dist[nxt] == -1) {
                    dist[nxt] = dist[s] + 1;
                    tree[nxt] = tree[s];
                    q.push_back(nxt);
                } else if (tree[nxt] != tree[s] && nxt != i) {
                    ans = min(ans, dist[nxt] + dist[s] + 1);
                }
            }
        }
    }
    if (ans == INF) ans = -1;
    cout << ans << '\n';
}
```
