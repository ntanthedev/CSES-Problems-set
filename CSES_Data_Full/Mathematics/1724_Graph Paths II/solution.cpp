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
