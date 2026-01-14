# 1723 - Graph Paths I

Given the adjacency matrix $G$ of a graph, the number of paths from node $a$ to
node $b$ using exactly $k$ edges equals $G^k[a][b]$. We can prove this property
using induction:

Case $k=1$: The property holds because $G[a][b]$ denotes the number of paths
from node $a$ to node $b$ using exactly one edge.

Case $k=n$: Assume that the property holds for $G^{n-1}$, i.e., $G^{n-1}[a][b]$
denotes the number of paths from node $a$ to node $b$ using exactly $n-1$ edges.
Then the property also holds for $G^n = G^{n-1} G$ because we can think that the
matrix multiplication formula

$$G^n[a][b] = \sum\_{i=1}^N (G^{n-1}[a][i] \cdot G[i][b])$$

goes through all possible ways to choose node $i$ which is the last node before
the final node $b$. In each case, there is first a path of length $n-1$ from
node $a$ to node $i$ and then a path of length $1$ from node $i$ to node $b$.

To efficiently solve the problem, we construct $G^k$ using fast exponentiation
and then read the number of paths from the matrix.

Note that there can be duplicate edges, so we increase the number of paths by
one after reading each edge.

The solution works in $O(N^3 \log k)$ time where $N$ is the upper bound for the
number of nodes and $k$ is the number of edges on the path.

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