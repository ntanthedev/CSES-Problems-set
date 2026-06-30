# 1679 - Lịch học

Bài toán yêu cầu tạo một thứ tự tô pô (topological sort) của các khóa học. Sắp xếp tô pô của một đồ thị có hướng được định nghĩa là một thứ tự các đỉnh sao cho nếu có đường đi từ đỉnh $a$ đến $b$, thì $a$ xuất hiện trước $b$ trong thứ tự đó.

Đầu tiên chúng tôi giải bài toán bằng thuật toán Kahn. Trong thuật toán Kahn, ta xây dựng một thứ tự tô pô bằng cách lần lượt loại bỏ các đỉnh khỏi đồ thị, luôn chọn một đỉnh không có cạnh vào. Nếu ta có thể loại bỏ tất cả các đỉnh khỏi đồ thị thì thứ tự thu được là một thứ tự tô pô, bởi vì nếu có đường đi $x\_1, \dots, x\_k$, thì để loại bỏ $x\_k$ ta phải đã loại bỏ $x\_{k-1},$ $x\_{k-2}, \dots$ và cuối cùng là $x\_1$.

Giả sử ta không thể loại bỏ tất cả các đỉnh khỏi đồ thị ban đầu $G$ và gọi tập các đỉnh còn lại là $R = \{r\_1, \dots, r\_k\}$. Khi đó với mọi $x \in R$ phải tồn tại một đỉnh $y\in R$ sao cho có cạnh từ $y$ đến $x$. Giả sử vẫn tồn tại một thứ tự tô pô của các đỉnh trong $G$. Trong thứ tự tô pô đó, một trong các đỉnh $z \in R$ phải là đỉnh đầu tiên trong số $R$. Điều này là không thể vì ta đã giả sử rằng luôn tồn tại một đỉnh $y\in R$ sao cho có cạnh đến $z$. Do đó, nếu ta không thể loại bỏ tất cả các đỉnh khỏi đồ thị, thì không tồn tại thứ tự tô pô nào cho đồ thị đó.

Độ phức tạp thời gian của lời giải là $O(n + m)$.

```cpp
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> in_degree(n + 1);
    vector<vector<int>> g(n + 1);

    for (int i = 1; i <= m; ++i) {
        int a, b;
        cin >> a >> b;
        ++in_degree[b];
        g[a].push_back(b);
    }

    vector<int> no_incoming;

    for (int i = 1; i <= n; ++i) {
        if (in_degree[i] == 0) {
            no_incoming.push_back(i);
        }
    }

    for (int i = 0; i < no_incoming.size(); ++i) {
        int x = no_incoming[i];
        for (int y : g[x]) {
            --in_degree[y];
            if (in_degree[y] == 0) {
                no_incoming.push_back(y);
            }
        }
    }

    if (no_incoming.size() < n) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    for (int x : no_incoming) {
        cout << x << ' ';
    }
    cout << '\n';
}
```

Tiếp theo, chúng tôi trình bày một lời giải khác cho bài toán. Chúng tôi giải bài toán bằng cách chạy tìm kiếm theo chiều sâu (DFS) từ mỗi đỉnh chưa được ghé thăm trong đồ thị. Mỗi lần ta đã xử lý xong một đỉnh và chuẩn bị lấy nó ra khỏi ngăn xếp DFS, ta sẽ thêm nó vào cuối vector `reverse_answer`. Với mỗi đỉnh, ta cũng kiểm tra xem có đỉnh kề nào của nó đã nằm trong ngăn xếp DFS hay không. Nếu có, ta đã tìm thấy một chu trình, đồng nghĩa với việc không tồn tại thứ tự tô pô nào cho đồ thị.

Hãy chứng minh rằng nếu không tìm thấy chu trình nào, thì `reverse_answer` sẽ chứa một thứ tự tô pô theo thứ tự ngược. Với mọi cặp đỉnh $x$ và $y$, trong đó $y$ có thể đến được từ $x$, ta cần xét hai trường hợp. Hoặc $x$ và $y$ được xử lý bởi cùng một lượt tìm kiếm hoặc bởi các lượt tìm kiếm khác nhau. Trong cả hai trường hợp, $y$ phải được thêm vào `reverse_answer` trước $x$. Do đó, `reverse_answer` sau khi đảo ngược là một thứ tự tô pô.

Độ phức tạp thời gian của lời giải là $O(n + m)$.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
const int N = 100001;

vector<int> g[N];
bool visited[N];
bool active[N];
vector<int> reverse_answer;

bool dfs(int x) {
    if (active[x]) return false;
    if (visited[x]) return true;
    active[x] = true;
    visited[x] = true;
    for (int y : g[x]) {
        if (!dfs(y)) return false;
    }
    active[x] = false;
    reverse_answer.push_back(x);
    return true;
}

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
    }

    for (int i = 1; i <= n; ++i) {
        if (!dfs(i)) {
            cout << "IMPOSSIBLE\n";
        }
    }
    reverse(reverse_answer.begin(), reverse_answer.end());

    for (int x : reverse_answer) {
        cout << x << ' ';
    }
    cout << '\n';
}
```

## Tài liệu tham khảo

* [Sắp xếp tô pô (Wikipedia)](https://en.wikipedia.org/wiki/Topological_sorting)
* [CPHB (Sổ tay lập trình viên thi đấu)](http://cses.fi/book),
  Chương 7.4.1
