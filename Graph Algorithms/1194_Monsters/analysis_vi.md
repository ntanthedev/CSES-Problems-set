# 1194 - Quái Vật

Ta bắt đầu giải bài toán bằng cách tính toán, với mỗi ô, khoảng cách đến quái vật gần nhất. Ta lưu trữ giá trị này trong mảng `m_dist`. Điều này được thực hiện bằng cách chạy tìm kiếm theo chiều rộng (BFS) với hàng đợi BFS được khởi tạo bằng các vị trí quái vật ban đầu.

Sau đó, ta tính bằng BFS khoảng cách từ `A` đến mỗi ô và lưu trữ chúng trong mảng `a_dist`. Ta cũng gán với mỗi ô:

* Trong mảng `parent`, ô cha trong cây BFS.
* Trong mảng `last_letter`, ký tự biểu diễn bước di chuyển cuối cùng.

Thêm vào đó, ta kiểm tra với mỗi ô biên `s` nếu `a_dist[s] < m_dist[s]`.

Nếu ta không tìm thấy ô nào như vậy, thì lũ quái vật có thể đến mỗi ô biên cùng lúc với ta. Trong trường hợp này, ta in ra `NO` và thoát chương trình.

Giả sử ta tìm thấy một ô `s` như vậy. Bây giờ nếu ta đi theo đường đi ngắn nhất từ `A` đến `s`, thì ta sẽ đến `s` trước bất kỳ con quái vật nào. Do đó ta sẽ không ở chung ô `s` với bất kỳ con quái vật nào. Điều này cũng có nghĩa là ta sẽ không ở chung bất kỳ ô nào trên đường đi ngắn nhất đến `s` với quái vật. Nếu ta ở chung bất kỳ ô nào trên đường đi ngắn nhất, thì quái vật luôn có thể thực hiện cùng bước di chuyển như ta, cuối cùng ở chung ô `s` với ta, điều này là không thể.

Sau đó, ta sẽ đi theo đường đi từ `s` được xác định bởi mảng `parent` và xây dựng một xâu đảo ngược các ký tự biểu diễn đường đi. Cuối cùng ta đảo ngược xâu đường đi và in ra.

Độ phức tạp thời gian của lời giải là $O(nm)$.

```cpp
#include <algorithm>
#include <iostream>
#include <optional>
#include <queue>
#include <tuple>
using namespace std;

const int N = 1001;
const int INF = 1000000;
string grid[N];
int m_dist[N][N];
int a_dist[N][N];
pair<int, int> parent[N][N];
char last_letter[N][N];

tuple<int, int, char> moves[]{
    {0, 1, 'R'}, {1, 0, 'D'}, {0, -1, 'L'}, {-1, 0, 'U'}};

int main() {
    int n, m;
    cin >> n >> m;
    pair<int, int> a;
    queue<pair<int, int>> queue;
    for (int i = 0; i < n; ++i) {
        cin >> grid[i];
        for (int j = 0; j < m; ++j) {
            m_dist[i][j] = INF;
            a_dist[i][j] = INF;
            if (grid[i][j] == 'M') {
                m_dist[i][j] = 0;
                queue.emplace(i, j);
            }
            if (grid[i][j] == 'A') {
                a_dist[i][j] = 0;
                a = {i, j};
            }
        }
    }

    while (!queue.empty()) {
        auto [r, c] = queue.front();
        queue.pop();
        for (auto [dr, dc, letter] : moves) {
            int new_r = r + dr;
            int new_c = c + dc;
            if (new_r >= 0 && new_r < n && new_c >= 0 && new_c < m) {
                if (grid[new_r][new_c] == '#') continue;
                if (m_dist[new_r][new_c] < INF) continue;
                m_dist[new_r][new_c] = m_dist[r][c] + 1;
                queue.emplace(new_r, new_c);
            }
        }
    }

    queue.push(a);
    optional<pair<int, int>> exit_square;

    while (!queue.empty()) {
        auto [r, c] = queue.front();
        if (r == 0 || r == n - 1 || c == 0 || c == m - 1) {
            if (a_dist[r][c] < m_dist[r][c]) {
                exit_square = {r, c};
                break;
            }
        }
        queue.pop();
        for (auto [dr, dc, letter] : moves) {
            int new_r = r + dr;
            int new_c = c + dc;
            if (new_r >= 0 && new_r < n && new_c >= 0 && new_c < m) {
                if (grid[new_r][new_c] == '#') continue;
                if (a_dist[new_r][new_c] < INF) continue;
                a_dist[new_r][new_c] = a_dist[r][c] + 1;
                parent[new_r][new_c] = {r, c};
                last_letter[new_r][new_c] = letter;
                queue.emplace(new_r, new_c);
            }
        }
    }

    if (!exit_square) {
        cout << "NO\n";
        return 0;
    }
    string ans;
    pair<int, int> x = *exit_square;
    while (x != a) {
        auto [r, c] = x;
        ans += last_letter[r][c];
        x = parent[r][c];
    }
    reverse(ans.begin(), ans.end());
    cout << "YES\n";
    cout << ans.size() << '\n';
    cout << ans << '\n';
}
```
