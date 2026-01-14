#include <iostream>
using namespace std;
using ll = long long;
const ll INF = 1e18;

const int N = 5000;
int x[N], pos[N][N];
ll s[N + 1], dp[N][N];

int main() {
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> x[i];
        s[i + 1] = s[i] + x[i];
        dp[i][i] = 0;
        pos[i][i] = i + 1;
    }

    for (int len = 2; len <= n; ++len) {
        for (int l = 0; l <= n - len; ++l) {
            int r = l + len - 1;
            dp[l][r] = INF;
            for (int p = pos[l][r - 1]; p <= pos[l + 1][r]; ++p) {
                ll off = dp[l][p - 1] + dp[p][r] + (s[r + 1] - s[l]);
                if (off < dp[l][r]) {
                    dp[l][r] = off;
                    pos[l][r] = p;
                }
            }
        }
    }

    cout << dp[0][n - 1] << endl;
}
