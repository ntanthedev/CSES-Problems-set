#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<pair<int, int>> ops;
    for (int i = 1; i <= n; i++) {
        int pos = i;
        while (a[pos] != i) {
            pos++;
        }
        if (pos != i) {
            ops.push_back({i, pos});
            reverse(a.begin() + i, a.begin() + pos + 1);
        }
    }

    cout << ops.size() << '\n';
    for (auto [l, r] : ops) {
        cout << l << ' ' << r << '\n';
    }
}
