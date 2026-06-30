# 1197 - Tìm Chu Trình

Ta giải bài toán bằng thuật toán Bellman-Ford trong thời gian $O(nm)$.

Vì ta chỉ quan tâm đến việc tìm chu trình âm, ta khởi tạo mảng $\mathrm{distance}$ được sử dụng trong Bellman-Ford bằng các số 0. Ta cũng gán với mỗi đỉnh $x$ đỉnh trước đó trên đường đi ngắn nhất đến $x$ và lưu trữ nó trong mảng $\mathrm{previous}$.

Ta chạy $n$ vòng lặp của thuật toán Bellman-Ford. Nếu mảng $\mathrm{distance}$ không bị thay đổi ở vòng lặp thứ $n$, thì đồ thị không chứa chu trình âm. Ngược lại, đồ thị chứa một chu trình âm.

Để xây dựng chu trình âm, ta bắt đầu bằng cách chọn một đỉnh $x\_1$ nào đó mà $\mathrm{distance}[x\_1]$ được cập nhật trong vòng lặp thứ $n$. Sau đó ta tạo một đường đi $x\_1, x\_2, \dots$ bằng cách đặt $x\_{i+1} = \mathrm{previous}[x\_i]$ và trích xuất chu trình âm từ đường đi này.

Trước tiên, hãy chứng minh rằng đường đi chứa một chu trình. Vì $\mathrm{distance}[x\_1]$ được cập nhật trong vòng $n$, ta biết rằng đỉnh $x\_2=\mathrm{previous}[x\_1]$ tồn tại và $\mathrm{distance}[x\_2]$ được cập nhật trong vòng $n-1$ hoặc muộn hơn. Bằng quy nạp, ta có thể chỉ ra rằng đỉnh $x\_{n+1}$ tồn tại. Đồ thị gồm $n$ đỉnh, do đó phải có một chu trình.

Tiếp theo, hãy tập trung vào chu trình $y\_1, \dots y\_k$, trong đó $y\_1 = y\_k$ và $y\_{i+1} = \mathrm{previous}[y\_i]$. Ta ký hiệu độ dài các cạnh trong chu trình là $c\_1, \dots, c\_{k-1}$ trong đó $c\_i$ tương ứng với cạnh từ $y\_{i+1}$ đến $y\_i$. Ta biết rằng
$$\mathrm{distance}[y\_{i+1}] + c\_i \le \mathrm{distance}[y\_i]$$
với mọi đỉnh trong chu trình. Ngoài ra, gọi $y\_a$ là đỉnh có khoảng cách được cập nhật gần đây nhất trong chu trình. Vì $\mathrm{distance}[y\_a]$ giảm cuối cùng, ta có một chặn chặt hơn trên cạnh trước đó
(quay vòng đến cuối chu trình nếu cần),
$$\mathrm{distance}[y\_a] + c\_{a-1} < \mathrm{distance}[y\_{a-1}].$$

Điều này dẫn đến
$$\sum\_{i=1}^{k-1} c\_i < \sum\_{i=1}^{k-1} \mathrm{distance}[y\_{i}] -
\mathrm{distance}[y\_{i+1}] = 0$$
chứng tỏ rằng độ dài chu trình là âm.

```cpp
#include <algorithm>
#include <iostream>
#include <optional>
#include <tuple>
#include <vector>
using namespace std;
using ll = long long;

int main() {
    int n, m;
    vector<tuple<int, int, int>> edges;

    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        edges.emplace_back(a, b, c);
    }

    vector<ll> distance(n + 1);
    vector<int> previous(n + 1);
    optional<int> path_end;

    for (int i = 1; i <= n; ++i) {
        for (auto [from, to, len] : edges) {
            ll new_distance = distance[from] + len;
            if (new_distance < distance[to]) {
                distance[to] = new_distance;
                previous[to] = from;
                if (i == n) {
                    path_end = to;
                }
            }
        }
    }

    if (!path_end) {
        cout << "NO\n";
        return 0;
    }

    vector<char> visited(n + 1);
    vector<int> path;
    int x = *path_end;
    while (true) {
        path.push_back(x);
        if (visited[x]) break;
        visited[x] = 1;
        x = previous[x];
    }
    reverse(path.begin(), path.end());

    cout << "YES\n";
    for (int i = 0; i < path.size(); ++i) {
        cout << path[i] << ' ';
        if (i > 0 && path[i] == path.front()) break;
    }
    cout << '\n';
}
```

## Tài liệu tham khảo

* [CPHB (Sổ tay Lập trình Viên Thi đấu)](https://cses.fi/book),
  Chương 7.3.1, Thuật toán Bellman-Ford
