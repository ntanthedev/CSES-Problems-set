# 2077 - Necessary Cities

*Necessary cities* (thành phố cần thiết) thường được gọi là các *điểm khớp* (articulation points) của đồ thị. Sẽ rất hữu ích khi hình dung đồ thị dưới dạng cây DFS của nó. Cây DFS biểu diễn thứ tự chúng ta thăm các đỉnh khi thực hiện tìm kiếm theo chiều sâu (depth-first search). Gốc của cây là đỉnh đầu tiên của quá trình duyệt và các đỉnh tiếp theo được đặt làm nút con của các đỉnh mà từ đó chúng được thăm.

Dưới đây là một ví dụ về đồ thị và một trong các cây DFS của nó khi quá trình duyệt bắt đầu từ đỉnh 1.

![](725ee9e085b0ca93fe59b5f4b206a05b8d551c5b51378a107f1f04b12bc72b26)

Từ cây DFS, có thể thấy rằng các đỉnh $1$ và $3$ là các điểm khớp của đồ thị.

Các cạnh của cây DFS tạo thành một tập con của các cạnh của đồ thị ban đầu. Hãy gọi các cạnh thuộc cây là *cạnh của cây* (tree edges) và phần còn lại là *cạnh ngược* (back-edges). Có một điều kiện đơn giản để kiểm tra một đỉnh có phải là điểm khớp hay không, áp dụng cho tất cả các đỉnh ngoại trừ gốc của cây DFS: Đỉnh $x$ là điểm khớp của đồ thị nếu nó có một nút con mà từ cây con của nút con đó không có *cạnh ngược* nào đến bất kỳ tổ tiên thực sự nào của $x$. Trong đồ thị ví dụ, $3$ là điểm khớp vì không có cây con nào của các nút con của nó chứa *cạnh ngược* đến tổ tiên của $3$. Cuối cùng, gốc của cây DFS là điểm khớp nếu nó có nhiều hơn một nút con.

Chi tiết cài đặt của thuật toán tương tự như thuật toán Tarjan để tìm các thành phần liên thông mạnh của đồ thị có hướng. Chúng ta sẽ bắt đầu bằng cách gán cho mỗi đỉnh một giá trị độ sâu (depth) cho biết khoảng cách từ nó đến đỉnh gốc trong cây DFS. Sau đó, với mỗi đỉnh, chúng ta tìm độ sâu nhỏ nhất của một đỉnh có thể đến được bằng một cạnh ngược từ cây con của đỉnh đó. Thuật toán có thể được cài đặt trong thời gian tuyến tính.

```cpp
#include <iostream>
#include <vector>
using namespace std;

const int N = 1e5 + 1;
vector<int> g[N];
vector<int> answer;
bool visited[N];
int depth[N], min_depth[N];

void dfs(int node, int prev) {
    bool is_root = prev == 0;
    bool found = false;
    int children = 0;
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
            children++;
            if (min_depth[nxt] >= depth[node]) found = true;
        }
    }
    if ((is_root && children > 1) || (!is_root && found)) {
        answer.push_back(node);
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

    cout << answer.size() << '\n';
    for (int node : answer) {
        cout << node << ' ';
    }
    cout << '\n';
}
```
