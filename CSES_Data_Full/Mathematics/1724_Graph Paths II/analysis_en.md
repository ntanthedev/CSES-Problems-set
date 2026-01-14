# 1724 - Graph Paths II

We create a custom matrix implementation where the product $C=AB$ is defined as
follows:

$$C[i][j] = \min\_{k=1}^N A[i][k] + B[k][j]$$

In addition, we use a special identity matrix where the main diagonal values are
zeros and all other values are infinity values.

Then, given the distance matrix $G$ of a graph, the shortest path length from
node $a$ to node $b$ using exactly $k$ edges equals $G^k[a][b]$. We construct
$G^k$ using fast exponentiation and then read the path length from the matrix.

Note that there can be duplicate edges, so we maintain the minimum single-edge
path length when reading the input.

The solution works in $O(N^3 \log k)$ time where $N$ is the upper bound for the
number of nodes and $k$ is the number of edges on the path.

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