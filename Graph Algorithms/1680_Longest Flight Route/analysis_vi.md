# 1680 - Đường bay dài nhất

Chúng tôi giải bài toán bằng quy hoạch động trên đồ thị có hướng không chu trình (DAG).

Đầu tiên, ta phát biểu bài toán dưới dạng đệ quy. Gọi $f(x)$ là độ dài (tính bằng số đỉnh) của đường đi dài nhất từ thành phố $x$ đến thành phố $n$. Ta cũng đặt $f(x) = -\infty$, nếu không có đường đi nào từ $x$ đến $n$.

Ta có hai trường hợp cơ sở:

* Nếu $x = n$, thì $f(x) = 1$ vì không có chu trình có hướng nào trong mạng bay.
* Nếu $x \not= n$ và không có chuyến bay nào từ $x$, thì $f(x) = -\infty$.

Ngược lại, ta sẽ gọi đệ quy hàm này. Gọi các điểm đến trực tiếp từ $x$ là $d\_1, \dots, d\_k$. Khi đó $f(x) = 1 + \max\_i f(d\_i)$. Ta nhận xét rằng vì mạng bay là không có chu trình, nên đệ quy được định nghĩa tốt. Ta cũng gắn với thành phố $x$ thành phố tiếp theo trên đường đi dài nhất bằng cách chọn $d\_i$ sao cho $f(d\_i)$ lớn nhất và lưu nó vào mảng `next_city`.

Sau đó, ta áp dụng quy hoạch động cho đệ quy bằng cách lưu các giá trị đã tính của $f(x)$ vào mảng `longest`.

Độ phức tạp thời gian của lời giải là $O(n + m)$.

```cpp
#include <iostream>
#include <vector>

using namespace std;

const int N = 100001;
const int INF = 1000000000;
vector<int> g[N];

bool ready[N];
int longest[N];
int next_city[N];
int n;

int f(int x) {
    if (ready[x]) return longest[x];
    ready[x] = true;
    longest[x] = -INF;
    if (x == n) {
        return longest[x] = 1;
    }
    for (int y : g[x]) {
        f(y);
        if (longest[y] + 1 > longest[x]) {
            longest[x] = longest[y] + 1;
            next_city[x] = y;
        }
    }
    return longest[x];
}

int main() {
    int m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
    }

    if (f(1) < 0) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    cout << f(1) << '\n';
    int x = 1;
    while (x != 0) {
        cout << x << ' ';
        x = next_city[x];
    }
    cout << '\n';
}
```

## Tài liệu tham khảo

* [CPHB (Sổ tay lập trình viên thi đấu)](http://cses.fi/book),
  Chương 7.4.2
