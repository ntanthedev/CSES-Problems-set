# 1724 - Graph Paths II

Chúng ta tạo một lớp ma trận tùy chỉnh, trong đó tích $C=AB$ được định nghĩa như sau:

$$C[i][j] = \min\_{k=1}^N A[i][k] + B[k][j]$$

Ngoài ra, chúng ta sử dụng một ma trận đơn vị đặc biệt với các giá trị trên đường chéo chính bằng 0 và tất cả các giá trị khác bằng vô cùng.

Khi đó, cho ma trận khoảng cách $G$ của đồ thị, độ dài đường đi ngắn nhất từ đỉnh $a$ đến đỉnh $b$ sử dụng đúng $k$ cạnh bằng $G^k[a][b]$. Chúng ta xây dựng $G^k$ bằng cách lũy thừa nhanh và sau đó đọc độ dài đường đi từ ma trận.

Lưu ý rằng có thể có các cạnh trùng lặp, vì vậy chúng ta lưu độ dài đường đi một cạnh nhỏ nhất khi đọc dữ liệu vào.

Lời giải có độ phức tạp $O(N^3 \log k)$, trong đó $N$ là chặn trên của số đỉnh và $k$ là số cạnh trên đường đi.

```cpp
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const ll INF = 2e18;

template <int N>
struct Matrix {
    ll m[N][N];

    Matrix<N>(ll x = 0) { fill((ll*)m, (ll*)m + N * N, x); }

    static Matrix<N> ident() {
        Matrix<N> r(INF);
        for (int i = 0; i < N; i++) r.m[i][i] = 0;
        return r;
    }

    Matrix<N> operator*(Matrix<N> b) {
        Matrix<N> r(INF);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                for (int k = 0; k < N; ++k) {
                    r.m[i][j] = min(r.m[i][j], m[i][k] + b.m[k][j]);
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

    Matrix<101> g(INF);
    for (int i = 1; i <= m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        g.m[a][b] = min(g.m[a][b], (ll)c);
    }

    auto p = g.power(k);
    ll answer = p.m[1][n];
    if (answer == INF) answer = -1;
    cout << answer << "\n";
}
```
