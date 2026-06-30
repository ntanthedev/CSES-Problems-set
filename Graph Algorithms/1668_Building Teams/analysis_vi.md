# 1668 - Building Teams

Trong bài toán này, chúng ta được yêu cầu kiểm tra xem đồ thị có phải là đồ thị hai phía hay không.

Nhận xét chính để giải bài toán là nếu chúng ta gán học sinh
$x$ vào đội $1$, thì chúng ta phải gán tất cả bạn bè của $x$ vào
đội $2$. Chúng ta có thể tiếp tục quá trình này đến bạn bè của bạn bè
và cứ thế. Nếu chúng ta nhận thấy hai người bạn đã được
gán vào cùng một đội, chúng ta biết rằng việc chia thành hai đội là
không thể. Nếu không, chúng ta đã tìm được cách chia hợp lệ cho tất cả học sinh
có thể đến được từ $x$.

Chúng ta bắt đầu bằng cách duyệt qua tất cả học sinh. Nếu học sinh $x$ chưa được
gán vào đội nào, chúng ta chạy tìm kiếm theo chiều sâu (DFS) gán $x$ vào
đội $1$ và tất cả học sinh có thể đến được theo cấu trúc đồ thị.

Sau đó, chúng ta duyệt qua các học sinh và in ra các gán đội.

Độ phức tạp thời gian của lời giải là $O(n + m)$.

```cpp
#include <iostream>
#include <vector>
using namespace std;

const int N = 100001;
vector<int> graph[N];
int teams[N];

// Giá trị trả về cho biết việc gán đội có thành công hay không
bool dfs(int x, int team) {
    if (teams[x] != 0) return teams[x] == team;
    teams[x] = team;
    for (int y : graph[x]) {
        if (!dfs(y, 3 - team)) return false;
    }
    return true;
}

int main() {
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    for (int i = 1; i <= n; ++i) {
        if (teams[i] != 0) continue;
        if (!dfs(i, 1)) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
    }

    for (int i = 1; i <= n; ++i) {
        cout << teams[i] << ' ';
    }
    cout << '\n';
}
```
