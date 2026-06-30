# 1723 - Đường đi trên đồ thị I

Cho ma trận kề $G$ của một đồ thị, số đường đi từ đỉnh $a$ đến
đỉnh $b$ sử dụng đúng $k$ cạnh bằng $G^k[a][b]$. Ta có thể chứng minh tính
chất này bằng quy nạp:

Trường hợp $k=1$: Tính chất đúng vì $G[a][b]$ là số đường đi
từ đỉnh $a$ đến đỉnh $b$ sử dụng đúng một cạnh.

Trường hợp $k=n$: Giả sử tính chất đúng với $G^{n-1}$, tức là $G^{n-1}[a][b]$
là số đường đi từ đỉnh $a$ đến đỉnh $b$ sử dụng đúng $n-1$ cạnh.
Khi đó tính chất cũng đúng với $G^n = G^{n-1} G$ vì ta có thể xem công thức
nhân ma trận

$$G^n[a][b] = \sum\_{i=1}^N (G^{n-1}[a][i] \cdot G[i][b])$$

duyệt qua mọi cách chọn đỉnh $i$ là đỉnh cuối cùng trước
đỉnh đích $b$. Trong mỗi trường hợp, trước hết có một đường đi độ dài $n-1$
từ đỉnh $a$ đến đỉnh $i$ và sau đó là một đường đi độ dài $1$ từ đỉnh $i$
đến đỉnh $b$.

Để giải quyết bài toán một cách hiệu quả, ta xây dựng $G^k$ bằng luỹ thừa
nhanh và sau đó đọc số đường đi từ ma trận.

Lưu ý rằng có thể có các cạnh trùng lặp, do đó ta tăng số đường đi lên
một sau khi đọc mỗi cạnh.

Cách giải chạy trong $O(N^3 \log k)$ thời gian, trong đó $N$ là cận trên của
số đỉnh và $k$ là số cạnh trên đường đi.

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
    int n, m, k;
    cin >> n >> m >> k;

    Matrix<101> g{};
    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        g.m[a][b]++;
    }

    auto p = g.power(k);
    cout << p.m[1][n] << "\n";
}
```
