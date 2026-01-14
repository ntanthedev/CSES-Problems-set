#include <iostream>
#include <set>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    multiset<int> prices;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        prices.insert(x);
    }

    for (int i = 1; i <= m; i++) {
        int x;
        cin >> x;
        auto it = prices.upper_bound(x);
        if (it == prices.begin()) {
            cout << "-1\n";
        } else {
            it--;
            cout << *it << "\n";
            prices.erase(it);
        }
    }
}
