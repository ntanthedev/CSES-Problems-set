# 1678 - Hành trình khứ hồi II

Chúng tôi giải bài toán bằng cách chạy tìm kiếm theo chiều sâu (DFS) từ mỗi thành phố chưa được ghé thăm trước đó trong đồ thị. Nếu trong khi chạy DFS nào đó, ta tìm thấy một thành phố có kết nối đến một thành phố hiện đang nằm trong ngăn xếp DFS, thì ta đã tìm thấy một chu trình.

Hãy chứng minh rằng thuật toán này thực sự tìm thấy một chu trình nếu có chu trình tồn tại. Giả sử tồn tại một chu trình $x\_1, \dots, x\_k, x\_1$ và thuật toán không tìm thấy chu trình nào trong đồ thị. Tuy nhiên, quá trình tìm kiếm sẽ ghé thăm mọi đỉnh của chu trình. Ta giả sử thành phố đầu tiên của chu trình được tìm kiếm ghé thăm là $x\_1$. Khi đó, trước khi lấy $x\_1$ ra khỏi ngăn xếp, quá trình tìm kiếm cuối cùng sẽ ghé thăm $x\_k$ và do đó tìm thấy chu trình.

Độ phức tạp thời gian của lời giải là $O(n + m)$.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
const int N = 100001;
vector<int> g[N];
bool visited[N];
bool active[N];
vector<int> answer;

bool dfs(int x) {
    if (active[x]) {
        answer.push_back(x);
        return true;
    }
    if (visited[x]) return false;
    visited[x] = true;
    active[x] = true;
    for (int y : g[x]) {
        if (dfs(y)) {
            answer.push_back(x);
            active[x] = false;
            return true;
        }
    }
    active[x] = false;
    return false;
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
        if (!visited[i]) {
            if (dfs(i)) break;
        }
    }

    if (answer.empty()) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    // Xóa các phần tử sau lần xuất hiện cuối cùng của `answer.front()`
    // `.base()` chuyển đổi iterator ngược thành iterator xuôi để có thể
    // dùng với `.erase()`
    // Nếu `r_it` là iterator ngược tương ứng với `it`, thì
    // `r_it.base() == it + 1`
    auto last = find(answer.rbegin(), answer.rend(), answer.front());
    answer.erase(last.base(), answer.end());
    reverse(answer.begin(), answer.end());

    cout << answer.size() << '\n';
    for (int x : answer) {
        cout << x << ' ';
    }
    cout << '\n';
}
```
