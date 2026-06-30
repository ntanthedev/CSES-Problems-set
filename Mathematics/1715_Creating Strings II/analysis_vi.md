# 1715 - Tạo xâu II

## Cách giải 1

Đầu tiên ta đếm số lần xuất hiện của mỗi ký tự trong xâu. Sau
đó, ta duyệt qua các ký tự và tính kết quả sử dụng các hệ số nhị thức.

Giả sử xâu có $n$ ký tự và ký tự đầu tiên xuất hiện $k$ lần
trong xâu. Điều này có nghĩa là có ${n \choose k}$ cách để chọn
vị trí cho ký tự đầu tiên. Sau đó, còn $n-k$ vị trí và ta tiếp tục
theo cách tương tự.

```cpp
#include <iostream>
#include <map>
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

    string s;
    cin >> s;
    int n = s.size();

    map<char, int> count;
    for (auto c : s) count[c]++;

    ll answer = 1;
    for (auto [c, k] : count) {
        answer = answer * ncr(n, k) % M;
        n -= k;
    }
    cout << answer << "\n";
}
```

## Cách giải 2

Ta cũng có thể tính hệ số đa thức

$${n \choose k\_1, k\_2, \dots, k\_m} = \frac{n!}{k\_1! k\_2! \dots k\_m!}$$

tương ứng với số cách chia $n$ phần tử vào $m$ tập hợp
có kích thước lần lượt là $k\_1,k\_2,\dots,k\_m$.

Trong bài toán này, $m$ bằng số lượng ký tự và $k\_i$ là
số lần xuất hiện của ký tự thứ $i$ trong xâu.

```cpp
#include <iostream>
#include <map>
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

int main() {
    fac[0] = 1;
    for (int i = 1; i <= N; i++) {
        fac[i] = fac[i - 1] * i % M;
    }

    string s;
    cin >> s;
    int n = s.size();

    map<char, int> count;
    for (auto c : s) count[c]++;

    ll answer = fac[n];
    for (auto [c, k] : count) {
        answer = answer * inv(fac[k]) % M;
    }
    cout << answer << "\n";
}
```

## Tài liệu tham khảo

* [Wikipedia (Định lý đa thức)](https://en.wikipedia.org/wiki/Multinomial_theorem)
