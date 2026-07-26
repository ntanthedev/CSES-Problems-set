#include <bits/stdc++.h>
using namespace std;

string dp[448];
map<string, string> pred;
vector<string> moves;
string s;

void precompute(int n) {
    pred.clear();
    int sz = 0;
    for (int i = 0; i <= n - 2; i++) {
        string cur = string(i, 'A') + string(n - 2 - i, 'B');
        cur.insert(0, "..");
        dp[sz++] = cur;
        pred[cur] = "";
        if (n < 8) {
            cur = string(i, 'A') + string(n - 2 - i, 'B');
            cur.insert(1, "..");
            dp[sz++] = cur;
            pred[cur] = "";
        }
    }
    for (int i = 0; i < sz; i++) {
        string cur = dp[i];
        int k = (int)cur.find('.');
        for (int j = 0; j < n - 1; j++) {
            if (cur[j] != '.' && cur[j + 1] != '.') {
                string nxt = cur;
                swap(nxt[j], nxt[k]);
                swap(nxt[j + 1], nxt[k + 1]);
                if (!pred.count(nxt)) {
                    pred[nxt] = cur;
                    dp[sz++] = nxt;
                }
            }
        }
    }
}

void solve_segment(int l, int r) {
    string cur = s.substr(l, r - l);
    while (!pred[cur].empty()) {
        cur = pred[cur];
        moves.push_back(s.substr(0, l) + cur + s.substr(r));
    }
    s = s.substr(0, l) + cur + s.substr(r);
}

void op(int i, int j) {
    swap(s[i], s[j]);
    swap(s[i + 1], s[j + 1]);
    moves.push_back(s);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    if (n == 1) {
        cout << "0\n";
        return 0;
    }

    cin >> s;
    if (n * 2 < 8) {
        precompute(n * 2);
        if (!pred.count(s)) {
            cout << "-1\n";
            return 0;
        }
        solve_segment(0, n * 2);
    } else {
        int dots = (int)s.find('.');
        if (dots > 1) op(dots, 0);
        else if (dots == 1) {
            op(dots, 3);
            op(3, 0);
        }
        dots = 0;
        precompute(8);
        while (dots + 8 < 2 * n) {
            if (s[dots + 2] == 'A' && s[dots + 3] == 'A') {
                op(dots, dots + 2);
                dots += 2;
            } else {
                int bpos = (int)s.find('B', dots);
                int apos = (int)s.find('A', bpos + 2);
                int flag = 0;
                if (apos == (int)string::npos) {
                    solve_segment(dots, dots + 8);
                    break;
                }
                if (apos == 2 * n - 1) {
                    apos--;
                    flag = 1;
                }
                op(dots, bpos);
                op(bpos, apos);
                op(apos, dots);
                if (flag) solve_segment(dots, dots + 8);
            }
        }
        solve_segment(dots, dots + 8);
    }

    cout << moves.size() << '\n';
    for (const string& x : moves) cout << x << '\n';
    return 0;
}
