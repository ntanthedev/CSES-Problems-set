# 2064 - Dãy ngoặc I

Nếu $n$ lẻ, ta không thể tạo bất kỳ dãy ngoặc hợp lệ nào, do đó ta giả sử $n$
chẵn. Ta xét các dãy ngoặc gồm $\frac{n}{2}$ dấu ngoặc mở và $\frac{n}{2}$ dấu
ngoặc đóng. Tổng số dãy như vậy là

$${n \choose \frac{n}{2}}.$$

Sau đó, ta tính số lượng dãy ngoặc không hợp lệ gồm $\frac{n}{2}$ dấu ngoặc mở và
$\frac{n}{2}$ dấu ngoặc đóng. Một dãy không hợp lệ nếu tồn tại tiền tố nào đó
chứa nhiều ngoặc đóng hơn ngoặc mở.

Nếu ta đảo ngược mỗi ngoặc trong tiền tố không hợp lệ nhỏ nhất, ta thu được một
dãy ngoặc khác gồm $n+1$ dấu ngoặc mở và $n-1$ dấu ngoặc đóng. Hơn nữa, có một
song ánh giữa các dãy ngoặc không hợp lệ và các dãy ngoặc gồm $n+1$ dấu ngoặc mở
và $n-1$ dấu ngoặc đóng. Do đó, số lượng dãy ngoặc không hợp lệ là

$${n \choose \frac{n}{2}+1}.$$

Ta có thể tính đáp án bằng công thức

$${n \choose \frac{n}{2}} - {n \choose \frac{n}{2} + 1}
= \frac{2}{n+2} {n \choose \frac{n}{2}}$$

trong đó ta lấy tổng số dãy ngoặc trừ đi số dãy ngoặc không hợp lệ.

```cpp
#include <iostream>
using namespace std;
using ll = long long;
const int M = 1000000007;
const int N = 1000000;

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

    int n;
    cin >> n;
    if (n % 2 == 0) {
        ll answer = 2LL * ncr(n, n / 2) * inv(n + 2) % M;
        cout << answer << "\n";
    } else {
        cout << "0\n";
    }
}
```
