# 1675 - Sửa chữa đường giao thông

Bài toán có thể được giải bằng cách tìm cây khung nhỏ nhất (MST) của đồ thị. Có nhiều thuật toán để tìm cây khung nhỏ nhất, trong đó chúng tôi sẽ trình bày các lời giải sử dụng thuật toán Kruskal và Prim.

Lời giải đầu tiên sử dụng thuật toán Kruskal. Trong cài đặt, chúng tôi sử dụng cấu trúc union-find. Khởi tạo cấu trúc union-find mất $O(n)$ thời gian và sắp xếp các cạnh mất $O(m \log m)$. Vòng lặp for cuối cùng mất $O(m \alpha(n))$, trong đó $\alpha(n)$ là hàm Ackermann ngược. Do đó, tổng độ phức tạp thời gian của lời giải là $O(n + m (\alpha(n) + \log m))$.

```cpp
#include <algorithm>
#include <iostream>
#include <numeric>
#include <tuple>
#include <vector>

using namespace std;
using ll = long long;

const int N = 100001;

int sz[N];
int link[N];

int find(int x) {
    if (link[x] == x) {
        return x;
    }
    return link[x] = find(link[x]);
}

bool same(int x, int y) {
    return find(x) == find(y);
}

void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (sz[x] < sz[y]) {
        swap(x, y);
    }
    sz[x] += sz[y];
    link[y] = x;
}

int main() {
    int n, m;
    cin >> n >> m;

    fill(sz, sz + n + 1, 1);
    iota(link, link + n + 1, 0);

    vector<tuple<int, int, int>> edges;
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        edges.emplace_back(a, b, c);
    }

    sort(edges.begin(), edges.end(),
         [](auto x, auto y) { return get<2>(x) < get<2>(y); });

    ll cost = 0;
    for (auto [a, b, c] : edges) {
        if (!same(a, b)) {
            unite(a, b);
            cost += c;
        }
    }

    if (sz[find(1)] != n) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    cout << cost << '\n';
}
```

Một cách khác để giải bài toán là sử dụng thuật toán Prim. Độ phức tạp thời gian của lời giải là $O(n + m \log m)$.

```cpp
#include <iostream>
#include <queue>
#include <vector>

using namespace std;
template <typename T>
using reverse_queue = priority_queue<T, vector<T>, greater<T>>;
using ll = long long;

const int N = 100001;

vector<pair<int, int>> g[N];
bool visited[N];

int main() {
    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].emplace_back(b, c);
        g[b].emplace_back(a, c);
    }

    reverse_queue<pair<ll, int>> queue;
    queue.emplace(0ll, 1);

    ll cost = 0;
    int n_visited = 0;
    while (!queue.empty()) {
        auto [len, x] = queue.top();
        queue.pop();
        if (visited[x]) {
            continue;
        }
        visited[x] = true;
        ++n_visited;
        cost += len;
        for (auto [y, new_len] : g[x]) {
            if (!visited[y]) {
                queue.emplace(new_len, y);
            }
        }
    }

    if (n_visited != n) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }
    cout << cost << '\n';
}
```

## Tài liệu tham khảo

* [CPHB (Sổ tay lập trình viên thi đấu)](http://cses.fi/book),
  Chương 15
* [CP-Algorithms, Disjoint Set Union / Union Find](https://cp-algorithms.com/data_structures/disjoint_set_union.html)
