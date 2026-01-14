#include <iostream>
using namespace std;

const int N = 200001;

int jmp[N][20];

int main() {
    int n, q;

    cin >> n >> q;

    for (int i = 2; i <= n; ++i) {
        cin >> jmp[i][0];
    }

    for (int j = 0; (1 << j) <= n; ++j) {
        for (int i = 1; i <= n; ++i) {
            jmp[i][j + 1] = jmp[jmp[i][j]][j];
        }
    }

    for (int qi = 0; qi < q; ++qi) {
        int x, k;
        cin >> x >> k;

        for (int j = 19; j >= 0; --j) {
            if (k >> j & 1) {
                x = jmp[x][j];
            }
        }

        cout << (x ? x : -1) << '\n';
    }
}
