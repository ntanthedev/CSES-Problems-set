# 1136 - Counting Paths

Hãy chọn gốc của cây một cách tùy ý.
Nhận thấy rằng, trong một cây có gốc, mọi đường đi giữa
hai đỉnh $a$ và $b$ đều có thể được chia thành hai phần:

1. phần từ $a$ đến $\textrm{lca}(a, b)$,
2. phần từ $b$ đến $\textrm{lca}(a, b)$.

Trong bài toán này ta sẽ xử lý các phần này riêng biệt.
Mỗi đỉnh sẽ có hai giá trị:

1. số lượng đường đi bắt đầu tại đỉnh đó (đi lên),
2. số lượng đường đi kết thúc tại đỉnh này.

Ta sẽ sử dụng phương pháp quy hoạch động.
Số đường đi đi qua đỉnh này có thể được tính bằng cách
cộng số lượng đường đi đến từ các đỉnh con
và số lượng đường đi bắt đầu tại đỉnh này.

Ta phải đảm bảo loại bỏ các đường đi kết thúc
tại đỉnh này khỏi bộ đếm.
Lưu ý rằng mỗi đường đi được đếm hai lần tại
đỉnh cao nhất của nó (đỉnh LCA). May mắn thay, số lượng
đường đi bị đếm trùng tại một đỉnh chính là số lượng
đường đi kết thúc tại đỉnh đó.

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

int paths_starting[N];
int paths_ending[N];
int answer[N];

int dfs_paths(int node, int parent) {
    int current_paths = paths_starting[node];
    for (int child : g[node]) {
        if (child == parent) continue;
        current_paths += dfs_paths(child, node);
    }
    // Các đường đi kết thúc tại đỉnh hiện tại bị đếm trùng hai lần.
    current_paths -= paths_ending[node];
    answer[node] = current_paths;
    current_paths -= paths_ending[node];
    return current_paths;
}

int main() {
    int n, m;

    cin >> n >> m;

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

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        int c = lca(a, b);
        paths_starting[a]++;
        paths_starting[b]++;
        paths_ending[c]++;
    }

    dfs_paths(0, 0);

    for (int i = 0; i < n; ++i) {
        cout << answer[i] << ' ';
    }
    cout << '\n';
}
```

### Tài liệu tham khảo

* [CPHB (Sổ tay Lập trình viên)](http://cses.fi/book), Chương 18
