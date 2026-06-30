# 1722 - Số Fibonacci

## Cách giải 1

Ta tạo một ma trận

$$\begin{bmatrix}
0 & 1 \\
1 & 1
\end{bmatrix}$$

có tính chất sau:

$$\begin{bmatrix}
0 & 1 \\
1 & 1
\end{bmatrix}
\begin{bmatrix}
F\_i \\
F\_{i+1}
\end{bmatrix}
= \begin{bmatrix}
F\_{i+1} \\
F\_{i+2}
\end{bmatrix}$$

Sau đó, ta có thể tính bất kỳ giá trị $F\_n$ nào bằng luỹ thừa ma trận:

$$\begin{bmatrix}
0 & 1 \\
1 & 1
\end{bmatrix}^n
\begin{bmatrix}
F\_0 \\
F\_1
\end{bmatrix}
= \begin{bmatrix}
F\_n \\
F\_{n+1}
\end{bmatrix}$$

Thuật toán kết quả chạy trong $O(\log n)$ thời gian.

```cpp
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const int M = 1000000007;

template <int N>
struct Matrix {
    ll m[N][N];

    static Matrix<N> ident() {
        Matrix<N> r{};
        for (int i = 0; i < N; i++) r.m[i][i] = 1;
        return r;
    }

    Matrix<N> operator*(Matrix<N> b) {
        Matrix<N> r{};
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                for (int k = 0; k < N; ++k) {
                    r.m[i][j] += m[i][k] * b.m[k][j];
                    r.m[i][j] %= M;
                }
            }
        }
        return r;
    }

    Matrix<N> power(ll b) {
        if (b == 0) return ident();
        auto a = *this;
        return b & 1 ? a.power(b - 1) * a : (a * a).power(b / 2);
    }
};

int main() {
    ll n;
    cin >> n;

    Matrix<2> m{{{0, 1}, {1, 1}}};
    auto p = m.power(n);
    cout << p.m[0][1] << "\n";
}
```

## Cách giải 2

Đây là một cách giải ngắn hơn, đặc biệt, không cần tính toán ma trận. Cách
giải dựa trên các đồng nhất thức sau:

* $F\_{2n} = (2F\_{n+1}-F\_n)F\_n$
* $F\_{2n+1} = F\_n^2 + F\_{n+1}^2$

Để đảm bảo cách giải hiệu quả, ta lưu mỗi giá trị vào một map sau khi
tính toán. Cách giải chạy trong $O(\log n)$ thời gian.

```cpp
#include <iostream>
#include <map>
using namespace std;
using ll = long long;
const int M = 1000000007;

map<ll, ll> dp;

ll f(ll n) {
    if (n <= 2) return n >= 1;
    if (dp.count(n)) return dp[n];
    auto a = f(n / 2);
    auto b = f(n / 2 + 1);
    if (n % 2 == 0) {
        dp[n] = (2 * b - a) * a;
    } else {
        dp[n] = a * a + b * b;
    }
    dp[n] = (dp[n] % M + M) % M;
    return dp[n];
}

int main() {
    ll n;
    cin >> n;
    cout << f(n) << "\n";
}
```

## Tài liệu tham khảo

* [Số Fibonacci (Wikipedia)](https://en.wikipedia.org/wiki/Fibonacci_number#Combinatorial_identities)
