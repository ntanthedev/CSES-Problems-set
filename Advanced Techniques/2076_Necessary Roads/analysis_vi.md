# 2076 - Necessary Roads

Cần lưu ý rằng *necessary roads* (con đường cần thiết) thường được biết đến với tên gọi là *cầu* (bridges). Để tìm các cầu của đồ thị đã cho, hãy hình dung đồ thị dưới dạng cây DFS của nó. Cây DFS biểu diễn thứ tự chúng ta thăm các đỉnh khi thực hiện tìm kiếm theo chiều sâu (depth-first search). Gốc của cây là đỉnh đầu tiên của quá trình duyệt và các đỉnh tiếp theo được đặt làm nút con của các đỉnh mà từ đó chúng được thăm.

Dưới đây là một ví dụ về đồ thị và một trong các cây DFS của nó khi quá trình duyệt bắt đầu từ đỉnh 1.

![](725ee9e085b0ca93fe59b5f4b206a05b8d551c5b51378a107f1f04b12bc72b26)

Các cầu của đồ thị là $(3, 6), (1, 3)$ và $(1, 4)$.

Lưu ý rằng có thể có nhiều hơn một cách để thăm các đỉnh và do đó, có thể có nhiều hơn một cây DFS. Tuy nhiên, các tính chất chúng ta quan tâm đều áp dụng cho mọi cây DFS. Các cạnh của cây DFS tạo thành một tập con của các cạnh của đồ thị ban đầu. Các cạnh không thuộc cây được gọi là *cạnh ngược* (back-edges). Có thể chứng minh rằng các cạnh ngược luôn đi từ một đỉnh đến tổ tiên của nó.

Lưu ý rằng các cạnh cầu luôn là *cạnh của cây* (tree edges), nghĩa là chúng luôn là một phần của cây DFS vì nếu không, nếu một cạnh ngược là cầu, việc xóa cạnh đó sẽ không làm đồ thị tách thành hai thành phần riêng biệt. Cầu cũng có một tính chất quan trọng khác. Một cạnh của cây $a\rightarrow b$ là cầu nếu không có cạnh ngược nào từ cây con của $b$ đến $a$ hoặc bất kỳ tổ tiên nào của $a$. Trong ví dụ, cạnh $(1, 3)$ là cầu vì không có cạnh ngược nào từ cây con của 3 đến 1.

Chi tiết cài đặt của thuật toán tương tự như thuật toán Tarjan để tìm các thành phần liên thông mạnh của đồ thị có hướng. Chúng ta sẽ bắt đầu bằng cách gán cho mỗi đỉnh một giá trị độ sâu (depth) cho biết khoảng cách từ nó đến đỉnh gốc trong cây DFS. Sau đó, với mỗi đỉnh, chúng ta tìm độ sâu nhỏ nhất của một đỉnh có thể đến được bằng một cạnh ngược từ cây con của đỉnh đó. Độ sâu nhỏ nhất có thể đến được xác định cạnh nào là cầu. Cài đặt có độ phức tạp thời gian là $O(n)$.

```cpp
#include <iostream>
#include <vector>
using namespace std;

const int N = 1e5 + 1;
vector<int> g[N];
vector<pair<int, int>> bridges;
bool visited[N];
int depth[N], min_depth[N];

void dfs(int node, int prev) {
    visited[node] = true;
    min_depth[node] = depth[node];
    for (int nxt : g[node]) {
        if (nxt == prev) continue;
        if (visited[nxt]) {
            min_depth[node] = min(min_depth[node], depth[nxt]);
        } else {
            depth[nxt] = depth[node] + 1;
            dfs(nxt, node);
            min_depth[node] = min(min_depth[node], min_depth[nxt]);
            if (min_depth[nxt] > depth[node]) {
                bridges.emplace_back(node, nxt);
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= m; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    dfs(1, 0);

    cout << bridges.size() << '\n';
    for (auto [a, b] : bridges) {
        cout << a << ' ' << b << '\n';
    }
}
```

## Tài liệu tham khảo

* [Bridge (Wikipedia)](https://en.wikipedia.org/wiki/Bridge_(graph_theory))
