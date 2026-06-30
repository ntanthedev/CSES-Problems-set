# 1139 - Màu sắc phân biệt

Ta sẽ tạo một `set` cho mỗi đỉnh. Tập hợp này sẽ chứa tất cả các giá trị trong cây con của mỗi đỉnh.

Tập hợp của mỗi đỉnh sẽ được xây dựng đệ quy từ các tập hợp của các đỉnh con của nó. Việc hợp nhất các tập hợp một cách ngây thơ sẽ quá chậm. May mắn thay, có một cách để hợp nhất chúng một cách hiệu quả.

Nếu tập hợp của một đỉnh con lớn hơn tập hợp của đỉnh cha, ta hoán đổi các tập hợp trước khi hợp nhất. Ta luôn di chuyển các phần tử từ tập hợp nhỏ hơn sang tập hợp lớn hơn, điều này đảm bảo rằng mỗi giá trị sẽ được di chuyển $O(\log n)$ lần. Độ phức tạp thời gian tổng thể của lời giải là $O(n\log^2 n)$.

Lưu ý rằng ta sử dụng hàm thư viện chuẩn `swap` để hoán đổi các tập hợp. Hàm này được đảm bảo hoạt động trong thời gian $O(1)$ đối với các container của thư viện chuẩn.

```cpp
#include <iostream>
#include <set>
#include <vector>
using namespace std;

const int N = 200001;
vector<int> g[N];
int answer[N], color[N];

set<int> dfs(int node, int parent) {
    set<int> colors{color[node]};
    for (int child : g[node]) {
        if (child == parent) continue;
        auto child_colors = dfs(child, node);
        // `swap` được đảm bảo hoạt động trong O(1) với các container stl.
        if (child_colors.size() > colors.size()) {
            swap(colors, child_colors);
        }
        colors.merge(child_colors);
    }
    answer[node] = colors.size();
    return colors;
}

int main() {
    int n;
    cin >> n;

    for (int i = 1; i <= n; ++i) {
        cin >> color[i];
    }

    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    dfs(1, -1);

    for (int i = 1; i <= n; ++i) {
        cout << answer[i] << ' ';
    }
    cout << '\n';
}
```
