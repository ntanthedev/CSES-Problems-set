#include <iostream>
using namespace std;

const int M = 1e9 + 7;
const int N = 501;
const int K = 124751;
int dp[N][K];

int main() {
    int n, k;
    cin >> n >> k;

    dp[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int h = 0; h <= k; ++h) {
            for (int j = 0; j <= min(h, i - 1); ++j) {
                dp[i][h] += dp[i - 1][h - j];
                dp[i][h] %= M;
            }
        }
    }

    cout << dp[n][k] << '\n';
}
