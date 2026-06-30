# 2138 - Các đỉnh có thể đến

Một đồ thị có hướng không chu trình không chứa chu trình, nghĩa là chúng ta có thể sử dụng
phương pháp quy hoạch động để giải bài toán. Chúng ta hãy lưu một mảng boolean
cho mỗi đỉnh, cho biết đỉnh nào có thể đến được từ đỉnh đó. Một
lời giải đơn giản sẽ thực hiện DFS từ mỗi đỉnh và cập nhật các
mảng sau mỗi cạnh. Mỗi cạnh sẽ tương ứng với $O(n)$ phép toán và do đó,
lời giải sẽ có độ phức tạp thời gian là $O(nm)$ và sẽ thực hiện
khoảng $5\cdot10^4\cdot10^5=5\cdot10^9$ phép toán, khiến lời giải hơi chậm.

May mắn thay, cách tiếp cận này có thể được tăng tốc bằng cách sử dụng bitset. Bitset cho phép chúng ta cập nhật
64 vị trí của mảng cùng một lúc và do đó, cung cấp hệ số $1/64$
cho số lượng phép toán, đưa tổng số lượng xuống còn
$5\cdot10^4\cdot10^5\cdot\frac 1 {64}\approx7.8\cdot10^7$.

```cpp
#include <bitset>
#include <iostream>
#include <vector>
using namespace std;

const int N = 5e4 + 1;

vector<int> g[N];
bitset<N> reach[N];
bool visited[N];

void dfs(int node) {
    if (visited[node]) return;
    visited[node] = true;
    reach[node][node] = true;
    for (int nxt : g[node]) {
        dfs(nxt);
        reach[node] |= reach[nxt];
    }
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
        dfs(i);
        cout << reach[i].count() << ' ';
    }
    cout << '\n';
}
```
