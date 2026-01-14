# 1091 - Concert Tickets

We add all the prices to a multiset, after which we can efficiently find and remove the price that corresponds to the price announced by a customer.

Since we should find the largest price that does not exceed the announced price, we use the function `upper_bound` and first find the smallest price that exceeds the announced price. Then, we decrease the iterator by one to find the desired price, which will then be removed.

If the original iterator points to the smallest price, all prices are larger than the announced price and we can't give a ticket to the customer.

```cpp
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
```