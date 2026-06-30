# 1079 - Hệ số nhị thức

## Cách giải 1

Nhiệm vụ của chúng ta là tính toán hiệu quả các giá trị của hệ số nhị thức

$${a \choose b} = \frac{a!}{b!(a-b)!}$$

modulo $M$ trong đó $a$ và $b$ nằm giữa $0$ và $N$ (trong bài toán này $N=10^6$).

Đầu tiên ta tiền xử lý tất cả các giai thừa $k!$ modulo $M$ với $k$ từ $0$ đến $N$. Sau đó, ta có thể tính bất kỳ hệ số nhị thức nào bằng tích của một giai thừa và hai nghịch đảo giai thừa.

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
    for (int i = 1; i <= n; i++) {
        int a, b;
        cin >> a >> b;
        cout << ncr(a, b) << "\n";
    }
}
```

## Cách giải 2

Để tạo ra một giải pháp hiệu quả hơn, ta cũng có thể tiền xử lý các giá trị nghịch đảo của mỗi giai thừa.

Trong đoạn code sau, đầu tiên ta tính nghịch đảo của $N!$. Sau đó ta có thể dùng một vòng lặp đơn giản để tính các nghịch đảo giai thừa còn lại. Vòng lặp hoạt động vì nếu ta biết giá trị của $\frac{1}{(k+1)!}$, ta có thể nhân nó với $k+1$ để được giá trị của $\frac{1}{k!}$.

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
ll inv_fac[N + 1];

int ncr(int a, int b) {
    return fac[a] * inv_fac[b] % M * inv_fac[a - b] % M;
}

int main() {
    fac[0] = 1;
    for (int i = 1; i <= N; i++) {
        fac[i] = fac[i - 1] * i % M;
    }
    inv_fac[N] = inv(fac[N]);
    for (int i = N - 1; i >= 0; i--) {
        inv_fac[i] = inv_fac[i + 1] * (i + 1) % M;
    }

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int a, b;
        cin >> a >> b;
        cout << ncr(a, b) << "\n";
    }
}
```
