# 1716 - Phân phối táo

Ta có thể tính kết quả bằng công thức

$${n+m-1 \choose m}$$

trong đó $n$ là số lượng trẻ em và $m$ là số lượng táo.

Ý tưởng là có một tương ứng một-một giữa các cách phân phối táo và
các xâu độ dài $n+m-1$ có $m$ ký tự $X$ và $n-1$ ký tự $\rightarrow$. Cách hiểu
mỗi xâu như sau: Ta bắt đầu ở đứa trẻ đầu tiên và đọc xâu từ trái sang phải.
Nếu ký tự là $X$, ta đưa một quả táo cho đứa trẻ hiện tại, và nếu ký tự là
$\rightarrow$, ta chuyển sang đứa trẻ tiếp theo.

```cpp
#include <iostream>
using namespace std;
using ll = long long;
const int M = 1000000007;
const int N = 2000000;

int power(int a, int b) {
    if (b == 0) return 1;
    ll u = power(a, b / 2);
    u = u * u % M;
    if (b % 2 == 1) u = u * a % M;
    return u;
}

int inv(int x) {
    return power(x, M - 2);
}

ll fac[N + 1];

int ncr(int a, int b) {
    return fac[a] * inv(fac[b] * fac[a - b] % M) % M;
}

int main() {
    fac[0] = 1;
    for (int i = 1; i <= N; i++) {
        fac[i] = fac[i - 1] * i % M;
    }

    int n, m;
    cin >> n >> m;
    cout << ncr(n + m - 1, m) << "\n";
}
```

## Tài liệu tham khảo

* [Sao và vạch (tổ hợp) (Wikipedia)](https://en.wikipedia.org/wiki/Stars_and_bars_(combinatorics))
