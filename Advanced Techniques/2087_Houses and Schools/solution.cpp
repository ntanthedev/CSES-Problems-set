#include <iostream>
using namespace std;
using ll = long long;

const ll INF = 1e18;
const int N = 3000;

int c[N];
ll lcost[N][N];
ll rcost[N][N];

ll left_cost(int l, int r) {
    return l <= r ? lcost[l][r] : 0;
}
ll right_cost(int l, int r) {
    return l <= r ? rcost[l][r] : 0;
}

ll cost(int l, int r) {
    int mid = (l + r) / 2;
    return left_cost(l, mid) + right_cost(mid + 1, r);
}

ll dp[N][N];

void recurse(int lvl, int l, int r, int pos_l, int pos_r) {
    if (l > r) return;

    int mid = (l + r) / 2;
    ll best = INF;
    int pos = l;

    for (int k = pos_l; k <= min(mid, pos_r); k++) {
        ll offer = dp[lvl - 1][k] + cost(k, mid);
        if (offer < best) {
            best = offer;
            pos = k;
        }
    }

    dp[lvl][mid] = best;

    recurse(lvl, l, mid - 1, pos_l, pos);
    recurse(lvl, mid + 1, r, pos, pos_r);
}

int main() {
    int n, k;
    cin >> n >> k;

    for (int i = 0; i < n; ++i) {
        cin >> c[i];
    }

    for (int i = 0; i < n; ++i) {
        ll s = 0;
        for (int j = i; j < n; ++j) {
            s += ll(j - i) * c[j];
            lcost[i][j] = s;
        }
    }

    for (int i = 0; i < n; ++i) {
        ll s = 0;
        for (int j = i; j >= 0; --j) {
            s += ll(i - j) * c[j];
            rcost[j][i] = s;
        }
    }

    for (int i = 0; i < n; ++i) {
        dp[0][i] = right_cost(0, i);
    }

    for (int i = 1; i < k; ++i) {
        recurse(i, 0, n, 0, n);
    }

    ll ans = INF;
    for (int i = 0; i < n; ++i) {
        ans = min(ans, dp[k - 1][i] + left_cost(i, n - 1));
    }

    cout << ans << '\n';
}
