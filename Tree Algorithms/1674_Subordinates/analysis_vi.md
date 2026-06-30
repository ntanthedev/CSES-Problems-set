# 1674 - Cấp dưới

Một cách khác để phát biểu bài toán:
Cho một cây có gốc và
ta cần tìm, với mỗi đỉnh,
số lượng đỉnh con trong cây con của nó.

Bài toán này có thể được giải bằng một lượt duyệt DFS (Depth-First Search).
Số lượng cấp dưới được tính bằng cách cộng dồn câu trả lời của từng đỉnh con với số lượng đỉnh con đó.

```cpp
#include <iostream>
#include <vector>
using namespace std;

const int N = 200001;
vector<int> g[N];
int subordinates[N];

void dfs(int node) {
    for (int child : g[node]) {
        dfs(child);
        subordinates[node] += subordinates[child] + 1;
    }
}

int main() {
    int n;
    cin >> n;

    for (int i = 2; i <= n; ++i) {
        int p;
        cin >> p;
        g[p].push_back(i);
    }

    dfs(1);

    for (int i = 1; i <= n; ++i) {
        cout << subordinates[i] << ' ';
    }
    cout << '\n';
}
```

## Tài liệu tham khảo

* [Depth first search (Wikipedia)](https://en.wikipedia.org/wiki/Depth-first_search)
