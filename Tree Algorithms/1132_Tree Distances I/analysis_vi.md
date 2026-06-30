# 1132 - Tree Distances I

Bài toán này có thể được giải bằng quy hoạch động.
Với mỗi đỉnh, ta sẽ tính và lưu hai giá trị:

1. $\texttt{max\\_dist}\_0$ — khoảng cách dài nhất từ đỉnh này đến một đỉnh khác
2. $\texttt{max\\_dist}\_1$ — khoảng cách dài nhất từ đỉnh này đến một đỉnh khác
   với điều kiện đường đi đến đỉnh đó đi qua một láng giềng khác
   với đường đi tương ứng với $\texttt{max\\_dist}\_0$.

Hãy chọn gốc cho cây.
Đầu tiên, ta sẽ tính các khoảng cách lớn nhất đi xuống (không đi qua
đỉnh cha). Sau đó, ta thực hiện một lượt duyệt theo chiều sâu khác để
cung cấp các đường đi qua đỉnh cha.

Tại mỗi đỉnh, ta sẽ đề xuất cho đỉnh con một giá trị ứng cử cho khoảng cách lớn nhất.
Nếu đường đi tương ứng với $\texttt{max\\_dist}\_0$ đi qua đỉnh con đó,
ta sẽ đề xuất cho nó khoảng cách $\texttt{max\\_dist}\_1+1$, nếu không
ta sẽ đề xuất $\texttt{max\\_dist}\_0+1$.

```cpp
#include <iostream>
#include <vector>
using namespace std;

const int N = 200001;
vector<int> g[N];
int max_dist[N][2];

void update(int node, int offer) {
    if (offer > max_dist[node][0]) {
        max_dist[node][1] = max_dist[node][0];
        max_dist[node][0] = offer;
    } else if (offer > max_dist[node][1]) {
        max_dist[node][1] = offer;
    }
}

void dfs1(int node, int parent) {
    for (int child : g[node]) {
        if (child == parent) continue;
        dfs1(child, node);
        update(node, max_dist[child][0] + 1);
    }
}

void dfs2(int node, int parent) {
    for (int child : g[node]) {
        if (child == parent) continue;
        if (max_dist[node][0] == max_dist[child][0] + 1) {
            update(child, max_dist[node][1] + 1);
        } else {
            update(child, max_dist[node][0] + 1);
        }
        dfs2(child, node);
    }
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

    dfs1(1, 1);

    dfs2(1, 1);

    for (int i = 1; i <= n; ++i) {
        cout << max_dist[i][0] << ' ';
    }
    cout << '\n';
}
```

## Tài liệu tham khảo

* [CPHB (Sổ tay Lập trình viên)](http://cses.fi/book), Chương 14
