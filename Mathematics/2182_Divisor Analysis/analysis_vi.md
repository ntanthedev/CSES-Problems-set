# 2182 - Phân tích ước số

Cho trước một số

$$N=\prod\_{i=1}^n x\_i^{k\_i}$$

và nhiệm vụ của ta là tính số lượng, tổng và tích các ước số của nó.

## Solution 1

Ta tính số lượng ước số như sau:

$$d(N) = \prod\_{i=1}^n (k\_i + 1)$$

Công thức đúng vì có $k\_i+1$ cách chọn một thừa số $x\_i$.

Ta tính tổng các ước số như sau:

$$s(N) = \prod\_{i=1}^n (1 + x\_i + x\_i^2 + \dots + x\_i^{k\_i})
= \prod\_{i=1}^n \frac{x\_i^{k\_i+1}-1}{x\_i-1}$$

Công thức này tương ứng với tổng trong đó mỗi ước số xuất hiện đúng một lần. Vì
mỗi phần của tích là một cấp số nhân, ta có thể tính đáp án hiệu quả hơn bằng
công thức tổng cấp số nhân.

Ta tính tích các ước số như sau:

$$p(N) = \prod\_{i=1}^n (x\_i^{k\_i(k\_i+1)/2})^{d(N)/(k\_i+1)}$$

Công thức này đúng vì nếu một thừa số $x\_i$ xuất hiện trong một ước số, nó có
thể xuất hiện từ $1$ đến $k\_i$ lần, do đó ta có thể dùng công thức tổng
$k\_i(k\_i+1)/2$ để đếm tổng số lần xuất hiện của thừa số. Hơn nữa, có
$d(N)/(k\_i+1)$ cách chọn các thừa số còn lại.

Lưu ý rằng vì ta muốn tính đáp án modulo $M$, ta phải tính $d(N)/(k\_i+1)$ modulo
$M-1$. Ta không thể dùng nghịch đảo modular ở đây vì $k\_i+1$ và $M-1$ không nhất
thiết nguyên tố cùng nhau. Thay vào đó, ta tạo hai vector bổ sung lưu tích tiền tố
và hậu tố của các giá trị $k\_i+1$ và dùng chúng trong vòng lặp cuối.

```cpp
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const int M = 1000000007;

ll power(ll a, ll b) {
    if (b == 0) return 1;
    ll u = power(a, b / 2);
    u = u * u % M;
    if (b % 2 == 1) u = u * a % M;
    return u;
}

ll inv(ll x) {
    return power(x, M - 2);
}

int main() {
    int n;
    cin >> n;

    vector<ll> x(n), k(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> k[i];
    }

    ll count = 1;
    for (int i = 0; i < n; i++) {
        count = count * (k[i] + 1) % M;
    }

    ll sum = 1;
    for (int i = 0; i < n; i++) {
        sum = sum * (power(x[i], k[i] + 1) - 1) % M;
        sum = sum * inv(x[i] - 1) % M;
    }

    vector<ll> prefix(n + 1);
    prefix[0] = 1;
    for (int i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i] * (k[i] + 1) % (M - 1);
    }

    vector<ll> suffix(n);
    suffix[n - 1] = 1;
    for (int i = n - 1; i > 0; i--) {
        suffix[i - 1] = suffix[i] * (k[i] + 1) % (M - 1);
    }

    ll prod = 1;
    for (int i = 0; i < n; i++) {
        ll ways = prefix[i] * suffix[i] % (M - 1);
        prod *= power(power(x[i], k[i] * (k[i] + 1) / 2), ways);
        prod %= M;
    }

    cout << count << " " << sum << " " << prod << "\n";
}
```

## Solution 2

Một cách thanh lịch hơn để tính tích các ước số như sau:

$$p(N) = N^{d(N)/2}$$

Ta có thể suy ra công thức này từ công thức trước bằng cách rút gọn số mũ:

$$p(N) = \prod\_{i=1}^n (x\_i^{k\_i(k\_i+1)/2})^{d(N)/(k\_i+1)}
= \prod\_{i=1}^n (x\_i^{k\_i})^{d(N)/2}
= N^{d(N)/2}$$

Lời giải sau đây tính tích các ước số bằng công thức này và không cần vector bổ
sung.

Ta cần tính $d(N)/2$ modulo $M-1$ và không thể dùng nghịch đảo modular vì $M-1$
và $2$ không nguyên tố cùng nhau. Ta xử lý hai trường hợp trong code:

Trường hợp 1: $N$ không chính phương. Tồn tại một giá trị $k\_i+1$ chẵn và ta chia
giá trị chẵn đầu tiên cho hai để tính số mũ $d(N)/2$.

Trường hợp 2: $N$ chính phương. Khi đó $d(N)$ lẻ và $d(N)/2$ không phải số
nguyên. Tuy nhiên, $\sqrt{N}$ là số nguyên nên ta có thể dùng công thức
$N^{d(N)/2}=\sqrt{N}^{d(N)}$ để tính đáp án. Trong trường hợp này, tất cả $k\_i$
đều chẵn và ta chia mỗi $k\_i$ cho hai trong vòng lặp cuối.

Một cách khác để giải thích công thức $N^{d(N)/2}$ là xét các cặp ước số dạng
$(k,N/k)$ với $k<N/k$. Khi $N$ không chính phương, có $d(N)/2$ cặp và tích mỗi
cặp là $N$. Khi $N$ chính phương, có $(d(N)-1)/2$ cặp có tích $N$ và thêm một ước
số $\sqrt{N}=N^{1/2}$. Công thức cũng đúng trong trường hợp này vì

$$N^{(d(N)-1)/2} N^{1/2} = N^{d(N)/2}.$$

```cpp
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const int M = 1000000007;

ll power(ll a, ll b) {
    if (b == 0) return 1;
    ll u = power(a, b / 2);
    u = u * u % M;
    if (b % 2 == 1) u = u * a % M;
    return u;
}

ll inv(ll x) {
    return power(x, M - 2);
}

int main() {
    int n;
    cin >> n;

    vector<ll> x(n), k(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> k[i];
    }

    ll count = 1;
    for (int i = 0; i < n; i++) {
        count = count * (k[i] + 1) % M;
    }

    ll sum = 1;
    for (int i = 0; i < n; i++) {
        sum = sum * (power(x[i], k[i] + 1) - 1) % M;
        sum = sum * inv(x[i] - 1) % M;
    }

    ll count2 = 1;
    bool is_square = true;
    for (int i = 0; i < n; i++) {
        if (is_square && k[i] % 2 == 1) {
            count2 *= (k[i] + 1) / 2;
            is_square = false;
        } else {
            count2 *= (k[i] + 1);
        }
        count2 %= M - 1;
    }

    ll prod = 1;
    for (int i = 0; i < n; i++) {
        if (is_square) k[i] /= 2;
        prod *= power(power(x[i], k[i]), count2);
        prod %= M;
    }

    cout << count << " " << sum << " " << prod << "\n";
}
```
