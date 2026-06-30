# 1135 - Distance Queries

Hãy chọn gốc của cây một cách tùy ý.
Trong một cây có gốc, khoảng cách giữa hai đỉnh $a$ và $b$ có thể được tính
bằng công thức
$$\textrm{dist}(a, b) = \textrm{depth}(a)
+\textrm{depth}(b)
-2\cdot\textrm{depth}(\textrm{lca}(a, b)).$$

Mọi cách cài đặt LCA hiệu quả đều đáp ứng được bài toán này.
Trong lời giải đính kèm, kỹ thuật *binary lifting* được sử dụng.

```cpp
#include <iostream>
#include <vector>
using namespace std;

const int N = 200000;
int jmp[N][20];
int depth[N];
vector<int> g[N];

void dfs(int node, int parent) {
    jmp[node][0] = parent;
    for (int child : g[node]) {
        if (child == parent) continue;
        depth[child] = depth[node] + 1;
        dfs(child, node);
    }
}

int lca(int a, int b) {
    if (depth[a] < depth[b]) {
        swap(a, b);
    }
    int depth_difference = depth[a] - depth[b];
    for (int j = 19; j >= 0; --j) {
        if ((1 << j) & depth_difference) {
            a = jmp[a][j];
        }
    }
    if (a == b) {
        return a;
    } else {
        for (int j = 19; j >= 0; --j) {
            if (jmp[a][j] != jmp[b][j]) {
                a = jmp[a][j];
                b = jmp[b][j];
            }
        }
        return jmp[a][0];
    }
}

int main() {
    int n, q;

    cin >> n >> q;

    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    dfs(0, 0);

    for (int j = 0; (1 << j) <= n; ++j) {
        for (int i = 0; i < n; ++i) {
            jmp[i][j + 1] = jmp[jmp[i][j]][j];
        }
    }

    for (int qi = 0; qi < q; ++qi) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        int c = lca(a, b);
        cout << depth[a] + depth[b] - 2 * depth[c] << '\n';
    }
}
```

### Tài liệu tham khảo

* [CPHB (Sổ tay Lập trình viên)](http://cses.fi/book), Chương 18
