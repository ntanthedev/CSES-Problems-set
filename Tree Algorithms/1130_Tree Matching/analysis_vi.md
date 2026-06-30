# 1130 - Tree Matching

Bài toán này cũng có thể được giải bằng cách sử dụng duyệt theo chiều sâu (DFS).
Việc hiểu sâu về thuật toán DFS là rất quan trọng trong nhiều bài toán liên quan đến cây.

Chúng ta sẽ chọn gốc của cây tại đỉnh 1 và, tại mỗi đỉnh,
xây dựng lời giải từ lời giải của các đỉnh con bằng quy hoạch động.

Với mỗi đỉnh, ta lưu một mảng gồm hai phần tử.
Các phần tử biểu diễn kích thước của bộ ghép lớn nhất phụ thuộc vào việc
đỉnh hiện tại có nằm trong bộ ghép hay không.

Ta nói một đỉnh nằm trong bộ ghép nếu nó là đầu mút của một cạnh nào đó
trong bộ ghép.

Các bước chuyển trạng thái quy hoạch động khá đơn giản. Ta chỉ cần đảm bảo rằng khi thêm một cạnh
thì cả hai đầu mút của cạnh đó đều chưa được dùng trong bộ ghép.

```cpp
#include <algorithm>
#include <array>
#include <iostream>
#include <vector>
using namespace std;

const int N = 200001;
vector<int> g[N];

array<int, 2> dfs(int node, int parent) {
    auto dp = array{0, 0};
    for (int child : g[node]) {
        if (child == parent) continue;
        auto child_dp = dfs(child, node);
        dp[1] = max({dp[0] + child_dp[0] + 1, dp[1] + child_dp[1],
                     dp[1] + child_dp[0]});
        dp[0] += max(child_dp[0], child_dp[1]);
    }
    return dp;
}

int main() {
    int n;
    cin >> n;

    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    auto result = dfs(1, 1);

    cout << max(result[0], result[1]) << '\n';
}
```
