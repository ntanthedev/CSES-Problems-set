# 1133 - Tree Distances II

Hãy chọn gốc cho cây.
Thay vì giải toàn bộ bài toán, trước tiên ta hãy tìm cách
tính đáp án cho đỉnh gốc.

Ta sẽ thực hiện một cách đệ quy bằng một lượt DFS duy nhất.
Với mỗi đỉnh $x$, ta lưu kích thước của cây con gốc $x$, $\texttt{subtree}\_x$, và tổng khoảng cách từ $x$ đến
mỗi đỉnh trong cây con của nó.

Tổng khoảng cách tăng lên bao nhiêu khi ta di chuyển từ một đỉnh lên đỉnh cha của nó?
Rõ ràng, khoảng cách đến mỗi đỉnh trong cây con tăng lên đúng một đơn vị. Do đó, chỉ cần lấy tổng
các tổng khoảng cách của các đỉnh con cộng với mức tăng, tức là số lượng đỉnh trong cây con.

Bây giờ ta đã biết, với mỗi đỉnh, tổng khoảng cách đến tất cả các đỉnh trong cây con của nó.
Trong trường hợp đỉnh gốc, đây chính là đáp án cuối cùng.

Tiếp theo, ta thực hiện một lượt DFS khác từ gốc và đồng thời theo dõi
đáp án cho đỉnh hiện tại.
Điều cuối cùng cần tìm ra là đáp án thay đổi bao nhiêu
khi ta di chuyển từ một đỉnh đến một trong các đỉnh con của nó (trong trường hợp của hình vẽ, từ $a$ đến $b$).

![](0a80aa6a59f73d8e22b0773be762940c37b854360a4baa1d733073a49fdec369)

Gọi đáp án cho $a$ là $\texttt{ans}\_a$. Có $\texttt{subtree}\_b$ đỉnh trong cây con của $b$.
Cạnh màu đỏ, từ $a$ đến $b$, chia đồ thị thành hai phần: phần của $a$ và phần của $b$.

Rõ ràng, khoảng cách đến mỗi đỉnh trong phần của $b$ giảm đi một đơn vị.
Có $\texttt{subtree}\_b$ đỉnh như vậy.

Tương tự, khoảng cách đến mỗi đỉnh trong phần của $a$ tăng lên một đơn vị.
Có $\left(n - \texttt{subtree}\_b\right)$ đỉnh như vậy.

Do đó, đáp án của $b$ bằng
$\texttt{ans}\_a - \texttt{subtree}\_b + \left(n - \texttt{subtree}\_b\right)$.

```cpp
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const int N = 200001;

int n;
vector<int> g[N];
int subtree[N];  // kích thước cây con

ll dfs(int node, int parent) {
    subtree[node] = 1;
    ll distance_sum = 0;
    for (int child : g[node]) {
        if (child == parent) continue;
        distance_sum += dfs(child, node);
        subtree[node] += subtree[child];
    }
    distance_sum += subtree[node] - 1;
    return distance_sum;
}

ll ans[N];

void calc(int node, int parent) {
    for (int child : g[node]) {
        if (child == parent) continue;
        ans[child] = ans[node] - subtree[child] + (n - subtree[child]);
        calc(child, node);
    }
}

int main() {
    cin >> n;

    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    ans[1] = dfs(1, 1);
    calc(1, 1);

    for (int i = 1; i <= n; ++i) {
        cout << ans[i] << ' ';
    }
    cout << '\n';
}
```
