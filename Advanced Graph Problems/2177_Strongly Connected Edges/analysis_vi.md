# 2177 - Cạnh Liên Thông Mạnh

Có thể giải bài toán này bằng cách tập trung vào cây DFS của đồ thị vô hướng.
DFS tạo ra các *cạnh cây* và *cạnh ngược*.

Ta sẽ định hướng mỗi cạnh cây từ cha xuống con. Tiếp theo, mỗi *cạnh ngược*
sẽ hướng lên trên về phía gốc. Hóa ra cách xây dựng này luôn đúng nếu có thể
làm cho đồ thị liên thông mạnh về tổng thể.

Có hai trường hợp không thể làm cho đồ thị liên thông mạnh. Thứ nhất, không thể
nếu đồ thị đã cho không liên thông. Thứ hai, nếu có một cây con trong cây DFS
mà từ đó không có một cạnh ngược nào đi ra ngoài cây con đó, thì cũng không thể,
vì không có cách nào để đến được các đỉnh khác từ cây con đó.

```cpp
#include <iostream>
#include <vector>
using namespace std;

void fail() {
    cout << "IMPOSSIBLE" << '\n';
    exit(0);
}

const int N = 100001;
vector<int> g[N];
vector<pair<int, int>> ans;
bool visited[N];
int depth[N], min_depth[N];

void dfs(int node, int prev) {
    visited[node] = true;
    min_depth[node] = depth[node];
    for (int nxt : g[node]) {
        if (nxt == prev) continue;
        if (visited[nxt]) {
            if (depth[nxt] < depth[node]) {
                ans.emplace_back(node, nxt);
            }
            min_depth[node] = min(min_depth[node], depth[nxt]);
        } else {
            depth[nxt] = depth[node] + 1;
            dfs(nxt, node);
            min_depth[node] = min(min_depth[node], min_depth[nxt]);
            ans.emplace_back(node, nxt);
            if (min_depth[nxt] > depth[node]) fail();
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    dfs(1, -1);

    if (ans.size() != m) fail();

    for (auto [a, b] : ans) {
        cout << a << ' ' << b << '\n';
    }
}
```
