# 2208 - Another Game

We win the game if there is at least one heap that has an odd number of coins,
and we lose the game if each heap has an even number of coins.

The idea is that we always select the heaps that have an odd number of coins
and remove a coin from each of them. This ensures that each heap has an even
number of coins when the opponent moves. Finally, each heap is empty and we have
won the game.

```cpp
#include <iostream>
using namespace std;

int main() {
    int t;
    cin >> t;

    for (int ti = 1; ti <= t; ti++) {
        int n;
        cin >> n;
        bool win = false;
        for (int i = 1; i <= n; i++) {
            int x;
            cin >> x;
            if (x % 2 == 1) win = true;
        }
        cout << (win ? "first" : "second") << "\n";
    }
}
```