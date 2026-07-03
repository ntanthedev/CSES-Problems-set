#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n;
    cin >> n;
    if (n == 1) {
        cout << "0\n";
        return 0;
    }

    string s;
    vector<long long> dp = {1};
    int last[2] = {-1, -1};

    while (dp.back() < n + 1) {
        char chosen = '0';
        long long best = -1;
        for (int c = 0; c < 2; c++) {
            long long nd = 2 * dp.back();
            if (last[c] != -1)
                nd -= dp[last[c]];
            if (nd <= n + 1 && nd > best) {
                best = nd;
                chosen = char('0' + c);
            }
        }
        int c = chosen - '0';
        s.push_back(chosen);
        dp.push_back(best);
        last[c] = (int)s.size() - 1;
    }

    cout << s << '\n';
    return 0;
}
