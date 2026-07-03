#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sum += a[i];
    }

    if (sum % 2 == 1) {
        cout << "-1\n";
        return 0;
    }

    vector<int> odds, evens;
    for (int x : a) {
        if (x % 2) odds.push_back(x);
        else evens.push_back(x);
    }

    vector<pair<int,int>> ops;

    while ((int)odds.size() > 1) {
        int x = odds.back(); odds.pop_back();
        int y = odds.back(); odds.pop_back();
        ops.push_back({x, y});
        evens.push_back(abs(x - y));
    }

    while ((int)evens.size() > 1) {
        int x = evens.back(); evens.pop_back();
        int y = evens.back(); evens.pop_back();
        ops.push_back({x, y});
        evens.push_back(abs(x - y));
    }

    if (!odds.empty() && !evens.empty()) {
        int x = odds.back(); odds.pop_back();
        int y = evens.back(); evens.pop_back();
        ops.push_back({x, y});
        evens.push_back(abs(x - y));
    }

    while ((int)evens.size() > 1) {
        int x = evens.back(); evens.pop_back();
        int y = evens.back(); evens.pop_back();
        ops.push_back({x, y});
        evens.push_back(abs(x - y));
    }

    if (evens.size() == 1 && evens[0] == 0) {
        for (auto [x, y] : ops) cout << x << ' ' << y << '\n';
        return 0;
    }

    if (n == 2 && a[0] == a[1]) {
        cout << a[0] << ' ' << a[1] << '\n';
        return 0;
    }

    cout << "-1\n";
}
