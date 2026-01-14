# 1754 - Coin Piles

Since each move removes three coins, the total number of coins must be divisible by three.

Each move removes at least one coin from each pile, so the number of coins in a pile must be at most twice the number of coins in the other pile.

If the above conditions hold, we can always empty the piles using a greedy algorithm that removes two coins from the pile that has more coins. If both piles have the same number of coins, we can arbitrarily select the move.

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int t;
    cin >> t;

    while (t--) {
        int a, b;
        cin >> a >> b;
        if ((a + b) % 3 == 0 && a <= 2 * b && b <= 2 * a) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}
```