#include <iostream>
using namespace std;

int count[128];

int main() {
    string s;
    cin >> s;

    int n = s.size();

    for (auto c : s) {
        count[(int)c]++;
    }

    auto check = [&](int length) {
        for (int i = 'A'; i <= 'Z'; ++i) {
            if (count[i] * 2 > length + 1) {
                return false;
            }
        }
        return true;
    };

    if (!check(n)) {
        cout << -1 << '\n';
        return 0;
    }

    char prev = '$';
    for (int i = 1; i <= n; ++i) {
        for (int nxt = 'A'; nxt <= 'Z'; ++nxt) {
            if (!count[nxt]) continue;
            if (nxt == prev) continue;
            count[nxt]--;
            if (check(n - i)) {
                cout << (char)nxt;
                prev = nxt;
                break;
            }
            count[nxt]++;
        }
    }
    cout << '\n';
}
