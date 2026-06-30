# 1202 - Investigation

Trong bài toán này, chúng ta được yêu cầu trả lời nhiều câu hỏi khác nhau về các
đường đi có giá rẻ nhất từ thành phố $1$ đến thành phố $n$. Câu hỏi đầu tiên
("giá rẻ nhất của một đường đi như vậy là bao nhiêu?") có thể được trả lời đơn giản
bằng thuật toán Dijkstra. Các câu hỏi khác đều có thể được trả lời
bằng quy hoạch động. Chúng ta chỉ xét câu hỏi
"có bao nhiêu đường đi với giá rẻ nhất?" vì cả ba câu hỏi
đều có thể được giải theo cách rất tương tự.

Chúng ta bắt đầu bằng cách chạy thuật toán Dijkstra từ thành phố $n$ trên đồ thị đảo ngược.
Chúng ta lưu giá đường đi rẻ nhất từ mỗi thành phố đến $n$ vào mảng $\mathrm{price}$.

Sau đó, chúng ta phát biểu bài toán dưới dạng đệ quy. Gọi $\mathrm{n\\_min\\_price}(x)$ là số lượng đường đi giá rẻ nhất từ $x$ đến $n$.

Chúng ta có hai trường hợp cơ sở:

* Nếu $x = n$, thì $\mathrm{n\\_min\\_price}(x) = 1$ vì tất cả các chuyến bay
  đều có chi phí dương.
* Nếu $x \not= n$ và không có đường đi nào từ $x$ đến $n$, thì
  $\mathrm{n\\_min\\_price}(x) = 0$.

Nếu không, chúng ta có thể định nghĩa giá trị một cách đệ quy. Xét tất cả các chuyến bay
từ $x$ là một phần của đường đi giá rẻ nhất từ $x$ đến $n$
và gọi các thành phố đích của các chuyến bay này là $y\_1, \dots, y\_k$ (nói cách khác,
với mọi $y\_i$ phải thỏa mãn $\mathrm{price}[x] = \mathrm{price}[y\_i] + p$ với
$p$ là giá của chuyến bay). Khi đó số lượng đường đi giá rẻ nhất từ $x$
đến $n$ bắt đầu bằng chuyến bay tương ứng với $y\_i$ là
$\mathrm{n\\_min\\_price}(y\_i)$ nên tổng số đường đi giá rẻ nhất là

$$\mathrm{n\\_min\\_price}(x) = \sum\_i \mathrm{n\\_min\\_price}(y\_i).$$

Công thức đệ quy được xác định tốt vì với mọi đỉnh $x$, bất đẳng thức
$\mathrm{price}[x] > \mathrm{price}[y\_i]$ luôn đúng.

Sau đó, chúng ta áp dụng quy hoạch động cho công thức đệ quy bằng cách ghi nhớ các giá trị
đã tính của hàm.

Độ phức tạp thời gian của lời giải là $O(n + m \log m)$.

```cpp
#include <iostream>
#include <queue>
#include <tuple>
using namespace std;
using ll = long long;
template <typename T>
using reverse_priority_queue = priority_queue<T, vector<T>, greater<T>>;

const int N = 100001;
const int MOD = 1000000007;
const ll INF = 1e18;

vector<pair<int, int>> g[N];
vector<pair<int, int>> rev_g[N];
ll price[N];
int n;

bool ready[N];
ll n_min_price[N];
ll min_flights[N];
ll max_flights[N];

void f(int x) {
    if (ready[x]) return;
    ready[x] = true;
    if (x == n) {
        n_min_price[x] = 1;
        min_flights[x] = 0;
        max_flights[x] = 0;
        return;
    }
    n_min_price[x] = 0;
    min_flights[x] = INF;
    max_flights[x] = -INF;
    for (auto [y, len] : g[x]) {
        if (price[x] == price[y] + len) {
            f(y);
            n_min_price[x] = (n_min_price[x] + n_min_price[y]) % MOD;
            min_flights[x] = min(min_flights[x], min_flights[y] + 1);
            max_flights[x] = max(max_flights[x], max_flights[y] + 1);
        }
    }
}

int main() {
    int m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].emplace_back(b, c);
        rev_g[b].emplace_back(a, c);
    }

    fill(price, price + n + 1, INF);

    reverse_priority_queue<pair<ll, int>> queue;
    queue.emplace(0, n);
    price[n] = 0;

    while (!queue.empty()) {
        auto [d, x] = queue.top();
        queue.pop();
        if (d > price[x]) continue;
        for (auto [y, len] : rev_g[x]) {
            ll new_d = d + len;
            if (new_d < price[y]) {
                price[y] = new_d;
                queue.emplace(new_d, y);
            }
        }
    }

    f(1);

    cout << price[1] << ' ' << n_min_price[1] << ' ';
    cout << min_flights[1] << ' ' << max_flights[1] << '\n';
}
```

## Tài liệu tham khảo

* [CPHB (Competitive Programmer's Handbook)](http://cses.fi/book),
  Chương 7.4.2
