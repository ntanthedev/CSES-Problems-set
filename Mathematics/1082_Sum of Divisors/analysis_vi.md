# 1082 - Tổng các ước số

## Cách giải 1

Vì một ước số $k$ xuất hiện trong $\lfloor n / k \rfloor$ số từ $1$ đến $n$, bài toán có thể được phát biểu lại thành tính tổng

$$\sum\_{k=1}^n \lfloor n / k \rfloor k.$$

Giải pháp sau tính tổng trong $O(n)$ thời gian. Đây là một khởi đầu tốt nhưng quá chậm khi $n=10^{12}$.

```cpp
#include <iostream>
using namespace std;
using ll = long long;
const int M = 1000000007;

int main() {
    ll n;
    cin >> n;

    ll s = 0;
    for (ll k = 1; k <= n; k++) {
        s += (n / k) * k;
        s %= M;
    }
    cout << s << "\n";
}
```

## Cách giải 2

Ta có thể cải thiện cách giải thứ nhất bằng cách tính tổng thành hai phần.

Đầu tiên, ta dùng công thức gốc cho các ước số nhỏ từ $1$ đến $\lfloor \sqrt n \rfloor$. Sau đó, ta tính phần còn lại của tổng bằng cách xét các khối ước số lớn mà mỗi ước số xuất hiện cùng số lần.

Ví dụ, các ước số từ $\lfloor n / 2 \rfloor + 1$ đến $n$ xuất hiện một lần, các ước số từ $\lfloor n / 3 \rfloor + 1$ đến $\lfloor n / 2 \rfloor$ xuất hiện hai lần, v.v. Tổng quát hơn, các ước số từ $\lfloor n / (k + 1) \rfloor + 1$ đến $\lfloor n / k \rfloor$ xuất hiện $k$ lần.

Ta tính tổng các ước số trong một khối bằng công thức tổng

$$a+(a+1)+\dots+b = \frac{(a + b) (b - a + 1)}{2}.$$

Lưu ý rằng vì tổng có thể lớn, ta dùng nghịch đảo nhân của $2$ modulo $M$ để chia tích cho $2$.

Ta tính cả hai phần của tổng trong $O(\sqrt n)$ thời gian, do đó thuật toán chạy trong $O(\sqrt n)$ thời gian, đủ nhanh khi $n=10^{12}$.

```cpp
#include <iostream>
using namespace std;
using ll = long long;
const int M = 1000000007;
const int INV2 = 500000004;

// a + (a+1) + ... + b
ll sum(ll a, ll b) {
    return (a + b) % M * ((b - a + 1) % M) % M * INV2 % M;
}

int main() {
    ll n;
    cin >> n;

    ll s = 0;
    for (ll k = 1; k * k <= n; k++) {
        s += (n / k) * k;
        s %= M;
    }
    for (ll k = 1; n / k > k; k++) {
        s += sum(n / (k + 1) + 1, n / k) * k;
        s %= M;
    }
    cout << s << "\n";
}
```
