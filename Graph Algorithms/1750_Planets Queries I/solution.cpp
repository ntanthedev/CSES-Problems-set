#include <iostream>
using namespace std;

const int N = 200001;
const int M = 30;

int succ[M][N];

int main() {
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; ++i) {
        cin >> succ[0][i];
    }

    for (int i = 1; i < M; ++i) {
        for (int j = 1; j <= n; ++j) {
            succ[i][j] = succ[i - 1][succ[i - 1][j]];
        }
    }

    for (int i = 0; i < q; ++i) {
        int x, k;
        cin >> x >> k;
        for (int j = 0; j < M; ++j) {
            if (k & (1 << j)) {
                x = succ[j][x];
            }
        }
        std::cout << x << '\n';
    }
}
