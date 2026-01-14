#include <iostream>
using namespace std;

const int M = 1000002;
const int LOG_M = __lg(M);

int nxt[M][LOG_M + 1];

int main() {
    int n, q;
    cin >> n >> q;

    for (int i = 1; i <= M + 1; ++i) {
        nxt[i][0] = M + 1;
    }

    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        nxt[a][0] = min(nxt[a][0], b);
    }

    for (int i = M - 1; i > 0; --i) {
        nxt[i][0] = min(nxt[i][0], nxt[i + 1][0]);
    }

    for (int j = 1; j <= LOG_M; ++j) {
        for (int i = 1; i <= M + 1; ++i) {
            nxt[i][j] = nxt[nxt[i][j - 1]][j - 1];
        }
    }

    for (int qi = 0; qi < q; ++qi) {
        int a, b;
        cin >> a >> b;
        int ans = 0;
        for (int j = LOG_M; j >= 0; --j) {
            if (nxt[a][j] <= b) {
                ans += 1 << j;
                a = nxt[a][j];
            }
        }
        cout << ans << '\n';
    }
}
