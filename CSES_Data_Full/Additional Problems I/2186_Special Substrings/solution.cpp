#include <array>
#include <iostream>
#include <map>
using namespace std;
using ll = long long;

using A = array<int, 26>;

int main() {
    string s;
    cin >> s;

    bool seen[26]{};
    char reference_char = s[0];

    for (char c : s) seen[c - 'a'] = true;

    map<A, int> m;
    A cur{};
    m[cur] = 1;
    ll ans = 0;

    for (char c : s) {
        if (c == reference_char) {
            for (int i = 0; i < 26; ++i) {
                if (seen[i]) cur[i]--;
            }
        }
        cur[c - 'a']++;
        ans += m[cur];
        m[cur]++;
    }

    cout << ans << '\n';
}
