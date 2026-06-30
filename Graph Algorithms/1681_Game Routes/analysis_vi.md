# 1681 - Đường đi trong trò chơi

Chúng tôi giải bài toán này bằng quy hoạch động trên đồ thị có hướng không chu trình (DAG).

Đầu tiên, ta phát biểu bài toán dưới dạng đệ quy. Gọi $f(x)$ là số cách để hoàn thành trò chơi khi bắt đầu từ màn $x$.

Ta có hai trường hợp cơ sở:

* Nếu $x = n$, thì $f(x) = 1$ vì không có chu trình có hướng nào trong mạng dịch chuyển.
* Nếu $x \not= n$ và không có đường dịch chuyển nào từ $x$, thì $f(x) = 0$.

Ngược lại, ta sẽ định nghĩa hàm một cách đệ quy. Gọi các điểm đến trực tiếp từ $x$ là $d\_1, \dots, d\_k$. Khi đó $f(x) = \sum\_i f(d\_i)$. Ta nhận xét rằng vì mạng dịch chuyển là không có chu trình, nên đệ quy được định nghĩa tốt. Ta cũng cần nhớ thực hiện tất cả các phép tính theo modulo $10^9 + 7$, như yêu cầu trong đề bài.

Sau đó, ta áp dụng quy hoạch động cho đệ quy bằng cách lưu các giá trị đã tính của $f(x)$ vào mảng `n_ways`.

Độ phức tạp thời gian của lời giải là $O(n + m)$.

```cpp
#include <iostream>
#include <vector>

using namespace std;

const int N = 100001;
const int MOD = 1000000007;

vector<int> g[N];

bool ready[N];
int n_ways[N];
int n;

int f(int x) {
    if (ready[x]) return n_ways[x];
    ready[x] = true;
    if (x == n) {
        return n_ways[x] = 1;
    }
    for (int y : g[x]) {
        n_ways[x] = (n_ways[x] + f(y)) % MOD;
    }
    return n_ways[x];
}

int main() {
    int m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
    }

    cout << f(1) << endl;
}
```

## Tài liệu tham khảo

* [CPHB (Sổ tay lập trình viên thi đấu)](http://cses.fi/book),
  Chương 7.4.2
