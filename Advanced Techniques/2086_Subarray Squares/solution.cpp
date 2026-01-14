#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const ll INF = 1e18;

struct Line {
    ll a, b;  // Represents the line y = ax + b
    // Returns the height of the line at x.
    ll operator()(ll x) { return a * x + b; }
};

int main() {
    int n, k;
    cin >> n >> k;

    vector<int> x(n);
    vector<ll> sum(n + 1);
    for (int i = 0; i < n; ++i) {
        cin >> x[i];
        sum[i + 1] = sum[i] + x[i];
    }

    vector<ll> dp(n + 1, INF);
    dp[0] = 0;

    for (int i = 0; i < k; ++i) {
        vector<Line> lines;
        int pos = 0;  // Stores the index of the current lowest line.

        // Finds the height of the lowest line at position x.
        // Assumes that the sequence of x's is increasing.
        auto get_best = [&](ll x) {
            while (pos + 1 < size(lines) && lines[pos + 1](x) < lines[pos](x)) {
                pos++;
            }
            return lines[pos](x);
        };

        vector<ll> ndp(n + 1);
        for (int j = i; j <= n; ++j) {
            if (j != i) {
                ndp[j] = sum[j] * sum[j] + get_best(sum[j]);
            }
            Line l = {-2 * sum[j], dp[j] + sum[j] * sum[j]};
            while (lines.size() > 1) {
                auto a = lines[lines.size() - 2];
                auto b = lines[lines.size() - 1];
                if ((l.b - a.b) * (a.a - b.a) <= (b.b - a.b) * (a.a - l.a)) {
                    lines.pop_back();
                } else {
                    break;
                }
            }
            lines.push_back(l);
        }
        swap(dp, ndp);
    }
    cout << dp[n] << '\n';
}
