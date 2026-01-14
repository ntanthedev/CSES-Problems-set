#include <iostream>
using namespace std;

const int N = 1001;
int sums[N][N];

int main() {
    int n, q;
    cin >> n >> q;

    for (int i = 0; i < n; ++i) {
        string row;
        cin >> row;

        for (int j = 0; j < n; ++j) {
            sums[i + 1][j + 1] = sums[i + 1][j] + sums[i][j + 1] - sums[i][j];
            sums[i + 1][j + 1] += (row[j] == '*');
        }
    }

    for (int qi = 0; qi < q; ++qi) {
        int y1, x1, y2, x2;
        cin >> y1 >> x1 >> y2 >> x2;
        // Make the range 0-indexed and half-open.
        y1--;
        x1--;
        // We're querying the range [y1, y2) x [x1, x2).
        int ans = sums[y2][x2] - sums[y1][x2] - sums[y2][x1] + sums[y1][x1];
        cout << ans << '\n';
    }
}
