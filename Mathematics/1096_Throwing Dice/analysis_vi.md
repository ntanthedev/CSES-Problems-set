# 1096 - Gieo xúc xắc

Gọi $f(n)$ là số cách để đạt được tổng $n$ bằng cách gieo xúc xắc.

Để giải bài toán, ta tạo một ma trận

$$M=\begin{bmatrix}
0 & 1 & 0 & 0 & 0 & 0 \\
0 & 0 & 1 & 0 & 0 & 0 \\
0 & 0 & 0 & 1 & 0 & 0 \\
0 & 0 & 0 & 0 & 1 & 0 \\
0 & 0 & 0 & 0 & 0 & 1 \\
1 & 1 & 1 & 1 & 1 & 1 \\
\end{bmatrix}$$

có tính chất sau:

$$M
\begin{bmatrix}
f(k) \\
f(k+1) \\
f(k+2) \\
f(k+3) \\
f(k+4) \\
f(k+5) \\
\end{bmatrix}
= \begin{bmatrix}
f(k+1) \\
f(k+2) \\
f(k+3) \\
f(k+4) \\
f(k+5) \\
f(k+6) \\
\end{bmatrix}$$

Sử dụng ma trận và lũy thừa nhanh, ta có thể tính hiệu quả giá trị $f(n)$ trong $O(\log n)$ thời gian.

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

    Matrix<6> m{{{0, 1, 0, 0, 0, 0},
                 {0, 0, 1, 0, 0, 0},
                 {0, 0, 0, 1, 0, 0},
                 {0, 0, 0, 0, 1, 0},
                 {0, 0, 0, 0, 0, 1},
                 {1, 1, 1, 1, 1, 1}}};
    auto p = m.power(n + 6);
    cout << p.m[0][0] << "\n";
}
```
