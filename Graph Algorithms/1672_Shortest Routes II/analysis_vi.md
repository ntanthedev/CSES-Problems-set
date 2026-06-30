# 1672 - Shortest Routes II

Để giải bài toán, chúng ta sử dụng thuật toán Floyd-Warshall.
Chúng ta tìm khoảng cách ngắn nhất giữa tất cả các cặp thành phố và lưu
chúng vào mảng `dist`. Sau đó, chúng ta có thể trả lời các truy vấn
bằng cách in các giá trị tương ứng trong mảng `dist`.

Độ phức tạp thời gian của thuật toán Floyd-Warshall là $O(n^3)$ và
trả lời các truy vấn tốn $O(q)$ thời gian.

```cpp
#include <iostream>
using namespace std;
using ll = long long;
const int N = 501;
const ll INF = 1e18;
ll dist[N][N];

int main() {
    int n, m, q;
    cin >> n >> m >> q;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            dist[i][j] = i == j ? 0 : INF;
        }
    }
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        dist[a][b] = min(dist[a][b], (ll)c);
        dist[b][a] = min(dist[b][a], (ll)c);
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            for (int k = 1; k <= n; ++k) {
                dist[j][k] = min(dist[j][k], dist[j][i] + dist[i][k]);
            }
        }
    }

    for (int i = 0; i < q; ++i) {
        int a, b;
        cin >> a >> b;
        if (dist[a][b] == INF) {
            cout << -1 << '\n';
        } else {
            cout << dist[a][b] << '\n';
        }
    }
}
```

## Tài liệu tham khảo

* [CPHB (Competitive Programmer's Handbook)](https://cses.fi/book), Chương 7.3.3, Thuật toán Floyd-Warshall
