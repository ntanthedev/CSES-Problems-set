#include <algorithm>
#include <iostream>
using namespace std;

const int N = 1e6;
const int INF = 1e9;

int nxt[N + 1][4];

int main() {
    string s;
    cin >> s;

    int n = s.size();

    for (int j = 0; j < 4; ++j) {
        nxt[n][j] = INF;
    }

    for (int i = n; i > 0; --i) {
        for (int j = 0; j < 4; ++j) {
            nxt[i - 1][j] = nxt[i][j];
        }
        int idx = string("ACGT").find(s[i - 1]);
        nxt[i - 1][idx] = i;
    }

    int i = 0;
    string ans;
    while (i < INF) {
        int c = max_element(nxt[i], nxt[i] + 4) - nxt[i];
        ans += "ACGT"[c];
        i = nxt[i][c];
    }

    cout << ans << '\n';
}
