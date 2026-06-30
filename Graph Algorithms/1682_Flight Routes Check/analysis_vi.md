# 1682 - Kiểm tra các tuyến bay

Để giải bài toán, ta chỉ cần kiểm tra, với mọi thành phố $x$, xem có thể đi từ $x$ đến $1$ và từ $1$ đến $x$ hay không. Điều này có thể thực hiện bằng cách chạy hai lần duyệt theo chiều sâu (DFS) từ $1$, một lần trên đồ thị gốc và một lần trên đồ thị được tạo ra từ đồ thị gốc bằng cách đảo ngược tất cả các cạnh.

Nếu ta tìm thấy một thành phố $x$ mà một trong hai điều kiện không thỏa mãn, thì không thể đi từ mọi thành phố đến mọi thành phố khác. Nếu các điều kiện đều thỏa mãn với mọi $x$, thì ta có thể đi giữa bất kỳ cặp thành phố nào $a$ và $b$ bằng cách đầu tiên đi từ $a$ đến $1$, sau đó từ $1$ đến $b$.

Độ phức tạp thời gian của lời giải là $O(n + m)$.

```cpp
#include <iostream>
#include <vector>

using namespace std;
const int N = 100001;

vector<int> g[N];
vector<int> rev_g[N];

bool visited1[N];
bool visited2[N];

void dfs1(int x) {
    if (visited1[x]) return;
    visited1[x] = true;
    for (int y : g[x]) {
        dfs1(y);
    }
}

void dfs2(int x) {
    if (visited2[x]) return;
    visited2[x] = true;
    for (int y : rev_g[x]) {
        dfs2(y);
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        rev_g[b].push_back(a);
    }

    dfs1(1);
    dfs2(1);

    for (int i = 1; i <= n; ++i) {
        if (!visited1[i]) {
            cout << "NO\n";
            cout << 1 << ' ' << i << '\n';
            return 0;
        }
        if (!visited2[i]) {
            cout << "NO\n";
            cout << i << ' ' << 1 << '\n';
            return 0;
        }
    }

    cout << "YES\n";
}
```
