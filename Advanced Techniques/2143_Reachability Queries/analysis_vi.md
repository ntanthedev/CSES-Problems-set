# 2143 - Truy vấn khả năng đến

Sẽ hữu ích khi nghĩ về bài toán dưới góc nhìn của các thành phần liên thông mạnh.
Cụ thể, nếu hai đỉnh nằm trong cùng một thành phần, thì cả hai đều có thể đến được
với nhau.

Các thành phần liên thông mạnh của đồ thị cũng tạo thành một đồ thị có hướng không
chu trình (DAG) riêng. Không thể có chu trình trong đồ thị được rút gọn từ các
thành phần bởi vì nếu nó chứa một chu trình gồm nhiều thành phần, thì các đỉnh của
chu trình đó, theo định nghĩa, sẽ chỉ tạo thành một thành phần duy nhất.

Sau khi tìm các thành phần liên thông mạnh bằng thuật toán Tarjan,
chúng ta đã quy bài toán về một DAG. Vì không có chu trình trong DAG, chúng ta
có thể xây dựng một lời giải quy hoạch động. Cụ thể, chúng ta có thể lưu, với mỗi
đỉnh, thông tin về các đỉnh khác có thể đến được từ nó. Thông tin
về khả năng đến có thể được sao chép sang mỗi *cha* của một đỉnh, sau khi tất cả
các con của đỉnh đó đã được xử lý xong.

Nếu chúng ta lưu thông tin về khả năng đến trong một mảng boolean, thì
lời giải sẽ quá chậm. Tuy nhiên, chúng ta có thể sử dụng bitset để tăng tốc
quá trình truyền thông tin vì bitset cho phép chúng ta cập nhật 64 phần tử cùng
một lúc.

```cpp
#include <bitset>
#include <iostream>
#include <vector>
using namespace std;

const int N = 5e4 + 1;
vector<int> g[N];
int cur_depth, comp_cnt;
int comp[N], depth[N], low[N];
vector<int> stack;
bool in_stack[N];

// Thuật toán tìm thành phần liên thông mạnh Tarjan
void scc_dfs(int node) {
    low[node] = depth[node] = ++cur_depth;
    stack.push_back(node);
    in_stack[node] = true;
    for (int nxt : g[node]) {
        if (!depth[nxt]) {
            scc_dfs(nxt);
            low[node] = min(low[node], low[nxt]);
        } else if (in_stack[nxt]) {
            low[node] = min(low[node], depth[nxt]);
        }
    }
    if (depth[node] == low[node]) {
        int i = -1;
        ++comp_cnt;
        while (i != node) {
            i = stack.back();
            stack.pop_back();
            in_stack[i] = false;
            comp[i] = comp_cnt;
        }
    }
}

using B = bitset<N>;
// `cg` là đồ thị rút gọn được xây dựng từ các SCC.
vector<int> cg[N];
B reach[N];
bool visited[N];

void dfs(int node) {
    if (visited[node]) return;
    visited[node] = true;
    reach[node][node] = true;
    for (int nxt : cg[node]) {
        dfs(nxt);
        reach[node] |= reach[nxt];
    }
}

int main() {
    int n, m, q;
    cin >> n >> m >> q;

    for (int i = 1; i <= m; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
    }

    for (int i = 1; i <= n; ++i) {
        if (!depth[i]) scc_dfs(i);
    }

    for (int i = 1; i <= n; ++i) {
        for (int j : g[i]) {
            if (comp[i] != comp[j]) {
                cg[comp[i]].push_back(comp[j]);
            }
        }
    }

    for (int i = 1; i <= comp_cnt; ++i) {
        dfs(i);
    }

    for (int qi = 1; qi <= q; ++qi) {
        int a, b;
        cin >> a >> b;
        cout << (reach[comp[a]][comp[b]] ? "YES" : "NO") << '\n';
    }
}
```
