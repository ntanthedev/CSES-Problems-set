# 1196 - Các Tuyến Bay

Ta bắt đầu bằng cách trình bày một thuật toán chậm cho bài toán và sau đó sửa đổi nó để chạy nhanh hơn.

Đầu tiên, ta thử giải bài toán bằng cách duyệt qua tất cả các tuyến đường có thể trong bản đồ theo thứ tự tăng dần độ dài. Điều này có thể được thực hiện bằng cách duy trì một hàng đợi ưu tiên các tuyến đường, chứa độ dài và thành phố cuối cùng của mỗi tuyến đường. Ta sẽ luôn lấy tuyến đường ngắn nhất $r$ từ hàng đợi và thêm tất cả các tuyến đường có thể từ $r$ được mở rộng thêm một chuyến bay trở lại hàng đợi. Khi đó, $k$ tuyến đường ngắn nhất từ $1$ đến $n$ là $k$ tuyến đường đầu tiên mà ta lấy từ hàng đợi và kết thúc tại $n$. (Lưu ý rằng vì có thể có nhiều tuyến đường từ $1$ đến $n$ với cùng độ dài, $k$ tuyến đường ngắn nhất có thể không được định nghĩa duy nhất.)

Gọi $x$ là một thành phố bất kỳ. Ta cũng gọi một tuyến đường là tốt nếu nó được mở rộng từ $k$ tuyến đường đầu tiên đến $x$ (sau khi mở rộng, tuyến đường không đi qua $x$ lần nữa) và là xấu nếu tuyến đường không tốt nhưng vẫn đi qua $x$. Để làm cho lời giải nhanh hơn, ta nhận thấy rằng ta có thể bỏ qua (tức là lấy các tuyến đường từ hàng đợi mà không thêm các tuyến đường mở rộng trở lại) tất cả các tuyến đường xấu và vẫn tìm được $k$ tuyến đường ngắn nhất từ $1$ đến $n$. Để chứng minh điều này, hãy bắt đầu với một tập $K$ gồm $k$ tuyến đường ngắn nhất nào đó từ $1$ đến $n$ và giả sử có một tuyến đường $r \in K$ là xấu. Sau đó ta tạo các tuyến đường mới $s\_1, \dots, s\_k$ từ $r$ trong đó $s\_i$ được tạo bằng cách thay thế tiền tố của $r$ cho đến lần xuất hiện cuối cùng của $x$ bằng tuyến đường thứ $i$ đến $x$. Tất cả các $s\_i$ đều là tốt và có độ dài không vượt quá $r$. Hơn nữa, ta có thể chọn $s\_i \not \in K$ và thay thế $r$ bằng nó. Bằng cách lặp lại quy trình này, ta sẽ thu được $k$ tuyến đường ngắn nhất, không có tuyến nào là xấu. Do đó, việc bỏ qua các tuyến đường xấu không ngăn cản ta tìm được $k$ tuyến đường ngắn nhất từ $1$ đến $n$.

Độ phức tạp của lời giải là $O(n + km \log km)$.

```cpp
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
using ll = long long;
template <typename T>
using reverse_priority_queue = priority_queue<T, vector<T>, greater<T>>;
const int N = 100001;
const int K = 10;
vector<pair<int, int>> g[N];
int visited[N];
ll dist[K];

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 1; i <= m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].emplace_back(b, c);
    }

    reverse_priority_queue<pair<ll, int>> q;
    q.emplace(0, 1);

    while (!q.empty()) {
        auto [d, x] = q.top();
        q.pop();
        if (visited[x] >= k) {
            continue;
        }
        if (x == n) {
            dist[visited[x]] = d;
        }
        ++visited[x];
        for (auto [y, len] : g[x]) {
            q.emplace(d + len, y);
        }
    }

    for (int i = 0; i < k; ++i) {
        cout << dist[i] << ' ';
    }
    cout << '\n';
}
```
