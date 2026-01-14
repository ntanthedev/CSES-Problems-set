#include <iostream>
#include <vector>
using namespace std;
const int M = 1000000007;
const int N = 100001;

int count[N][102];

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> x(n + 1);
    for (int i = 1; i <= n; ++i) cin >> x[i];

    for (int j = 1; j <= m; ++j) {
        if (x[1] == 0 || x[1] == j) {
            count[1][j] = 1;
        }
    }
    for (int i = 2; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (x[i] == 0 || x[i] == j) {
                for (int k = -1; k <= 1; ++k) {
                    count[i][j] = (count[i][j] + count[i - 1][j + k]) % M;
                }
            }
        }
    }

    int result = 0;
    for (int j = 1; j <= m; ++j) {
        result = (result + count[n][j]) % M;
    }
    cout << result << "\n";
}
