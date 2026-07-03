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

    long long target = n + 1;
    string s;
    vector<long long> dp = {1};
    int last[2] = {-1, -1};

    while (dp.back() < target) {
        long long cur = dp.back();
        long long opt[2];
        for (int c = 0; c < 2; ++c) {
            opt[c] = 2 * cur;
            if (last[c] != -1) opt[c] -= dp[last[c]];
        }

        int choice;
        if (opt[0] == target) choice = 0;
        else if (opt[1] == target) choice = 1;
        else if (opt[0] <= target && opt[1] <= target) choice = opt[1] > opt[0];
        else if (opt[0] <= target) choice = 0;
        else if (opt[1] <= target) choice = 1;
        else choice = opt[1] < opt[0];

        s.push_back(char('0' + choice));
        dp.push_back(opt[choice]);
        last[choice] = (int)s.size() - 1;
    }

    cout << s << '\n';
    return 0;
}
