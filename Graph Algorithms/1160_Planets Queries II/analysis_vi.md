# 1160 - Truy vấn Hành tinh II

Trước tiên, ta nhận thấy rằng các hành tinh và cổng dịch chuyển tạo thành một đồ thị mà mỗi thành phần liên thông được hình thành từ một chu trình và các cây (có thể chỉ gồm một hành tinh) bắt đầu từ mỗi hành tinh trong chu trình.

Thay vì trả lời các truy vấn theo thứ tự xuất hiện trong dữ liệu vào, trước tiên ta sẽ đọc tất cả các truy vấn, duyệt qua tất cả các hành tinh và với mỗi hành tinh $x$, tìm câu trả lời cho các truy vấn có $x$ là hành tinh xuất phát.

Ta sẽ xử lý từng thành phần riêng biệt. Ta bắt đầu xử lý một thành phần bằng cách tìm chu trình (trong code ví dụ, sử dụng thuật toán rùa và thỏ của Floyd). Gọi các đỉnh trong chu trình là $c\_1, \dots, c\_k$ trong đó $c\_{i + 1}$ có thể đến được từ $c\_{i}$ bằng một lần dịch chuyển. Sau đó ta sẽ chạy duyệt theo chiều sâu (DFS) từ $c\_1$ trên đồ thị mà ta đã đảo ngược tất cả các cổng dịch chuyển.

Ta tổng quát hóa khái niệm độ sâu trong DFS bằng cách gán $c\_2$ với độ sâu $-1$, $c\_3$ với độ sâu $-2$, và cứ thế cho tất cả các đỉnh trong chu trình. Trong DFS ta duy trì một mảng $\mathrm{depth}$ chứa, với mỗi đỉnh, độ sâu lớn nhất được gán cho đỉnh đó (xét cả cây DFS và chu trình). Nếu một đỉnh $x$ không nằm trong chu trình cũng không nằm trong cây DFS, ta đặt $\mathrm{depth}[x] = -\infty$.

Để trả lời một truy vấn $a,b$ trong khi xử lý đỉnh $a$, ta chỉ cần kiểm tra nếu $\mathrm{depth}[b]$ đã được đặt thành âm vô cùng hay không, và nếu không, tính hiệu $\mathrm{depth}[a] - \mathrm{depth}[b]$.

Độ phức tạp thời gian của lời giải là $O(n + q)$.

```cpp
#include <iostream>
#include <vector>

using namespace std;

const int N = 200001;
const int INF = 1e9;
int teleport[N];
vector<int> rev_graph[N];
int answer[N];
// pairs of b, id
vector<pair<int, int>> queries[N];
int depth[N];
bool visited[N];

vector<int> extract_cycle(int x) {
    int a = x;
    int b = teleport[x];
    while (a != b) {
        a = teleport[a];
        b = teleport[teleport[b]];
    }
    vector<int> cycle;
    do {
        a = teleport[a];
        cycle.push_back(a);
    } while (a != b);
    return cycle;
}

void dfs(int x, int d) {
    visited[x] = true;
    int previous_depth = depth[x];
    depth[x] = d;
    for (auto [b, id] : queries[x]) {
        if (depth[b] > -INF) {
            answer[id] = d - depth[b];
        } else {
            answer[id] = -1;
        }
    }
    for (int y : rev_graph[x]) {
        if (!visited[y]) {
            dfs(y, d + 1);
        }
    }
    depth[x] = previous_depth;
}

int main() {
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; ++i) {
        int t;
        cin >> t;
        teleport[i] = t;
        rev_graph[t].push_back(i);
        depth[i] = -INF;
    }
    for (int i = 1; i <= q; ++i) {
        int a, b;
        cin >> a >> b;
        queries[a].emplace_back(b, i);
    }

    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            auto cycle = extract_cycle(i);
            for (int j = 1; j < cycle.size(); ++j) {
                depth[cycle[j]] = -j;
            }
            dfs(cycle[0], 0);
            for (int j = 1; j < cycle.size(); ++j) {
                depth[cycle[j]] = -INF;
            }
        }
    }

    for (int i = 1; i <= q; ++i) {
        cout << answer[i] << '\n';
    }
}
```
