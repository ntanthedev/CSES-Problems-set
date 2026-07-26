#include <iostream>
#include <set>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    multiset<int> ms;
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        ms.insert(x);
        sum += x;
    }

    if (sum % 2 != 0) {
        cout << "-1\n";
        return 0;
    }

    vector<pair<int, int>> ops;
    while (ms.size() > 1) {
        int b = *ms.rbegin();
        ms.erase(prev(ms.end()));
        int a = *ms.rbegin();
        ms.erase(prev(ms.end()));
        ops.push_back({a, b});
        ms.insert(abs(a - b));
    }

    if (ms.empty() || *ms.begin() != 0) {
        cout << "-1\n";
        return 0;
    }

    for (auto [a, b] : ops)
        cout << a << ' ' << b << '\n';
    return 0;
}
