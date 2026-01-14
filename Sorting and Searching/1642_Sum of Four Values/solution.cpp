#include <iostream>
#include <set>
#include <tuple>
#include <vector>
using namespace std;

int main() {
    int n, x;
    cin >> n >> x;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    set<tuple<int, int, int>> sums;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            sums.emplace(a[i] + a[j], i, j);
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            sums.erase({a[i] + a[j], i, j});
        }
        for (int j = i - 1; j >= 1; j--) {
            int diff = x - a[i] - a[j];
            auto it = sums.lower_bound({diff, 0, 0});
            if (it == sums.end()) continue;
            auto [sum, a, b] = *it;
            if (sum != diff) continue;
            cout << i << " " << j << " " << a << " " << b << "\n";
            return 0;
        }
    }
    cout << "IMPOSSIBLE\n";
}
