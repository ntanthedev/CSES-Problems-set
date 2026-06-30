# 1751 - Chu trình Hành tinh

Chúng ta bắt đầu bằng cách nhận thấy rằng các hành tinh và cổng dịch chuyển tạo thành một đồ thị trong đó mỗi
thành phần liên thông được tạo bởi một chu trình và các cây (có thể chỉ gồm
một hành tinh) bắt đầu từ mỗi hành tinh trong chu trình. Đáp án cho hành tinh
$x$ khi đó là độ dài của chu trình cộng với số lần dịch chuyển cần thiết để
đi đến chu trình.

Chúng ta sẽ xử lý từng thành phần riêng biệt. Ta bắt đầu xử lý một thành phần bằng cách
tìm chu trình (trong lời giải này, sử dụng giải thuật rùa và thỏ của Floyd).
Sau đó ta sẽ chạy tìm kiếm theo chiều sâu (DFS) từ một hành tinh trong chu trình
trên đồ thị mà ta đã đảo chiều tất cả các cổng dịch chuyển. Ta cũng truyền vào
hàm DFS tham số $\mathrm{parent\\_answer}$, đáp án cho hành tinh cha.
Với lần gọi hàm DFS đầu tiên, giá trị này chính là số
hành tinh trong chu trình. Nếu hành tinh hiện tại là một phần của chu trình, đáp án
cho hành tinh hiện tại chính là $\mathrm{parent\\_answer}$. Nếu hành tinh
hiện tại không phải là một phần của chu trình, đáp án là $\mathrm{parent\\_answer} + 1$.

Độ phức tạp thời gian của lời giải là $O(n)$.

```cpp
#include <iostream>
#include <vector>

using namespace std;
const int N = 200001;

int teleporter[N];
vector<int> rev_graph[N];
bool cycle[N];
bool visited[N];
int answer[N];

// trả về một cặp (đỉnh chu trình, độ dài chu trình)
std::pair<int, int> find_cycle(int x) {
    int a = x;
    int b = teleporter[x];
    while (a != b) {
        a = teleporter[a];
        b = teleporter[teleporter[b]];
    }
    int size = 0;
    do {
        ++size;
        cycle[a] = true;
        a = teleporter[a];
    } while (a != b);
    return {a, size};
}

void dfs(int x, int parent_answer) {
    if (visited[x]) return;
    visited[x] = true;
    answer[x] = parent_answer;
    if (!cycle[x]) ++answer[x];
    for (int y : rev_graph[x]) {
        dfs(y, answer[x]);
    }
}

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> teleporter[i];
        rev_graph[teleporter[i]].push_back(i);
    }

    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            auto [x, size] = find_cycle(i);
            dfs(x, size);
        }
    }

    for (int i = 1; i <= n; ++i) {
        cout << answer[i] << ' ';
    }
    cout << '\n';
}
```
