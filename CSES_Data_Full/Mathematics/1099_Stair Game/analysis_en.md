# 1099 - Stair Game

This game corresponds to nim where we only include every second value in the xor
sum. More precisely, we only consider stairs whose index is even.

If a player moves $c$ coins from stair $k$ to stair $k-1$ where $k$ is odd, the
opponent can always cancel the move by moving $c$ coins from stair $k-1$ to
$k-2$ after that. Thus, we can ignore stairs whose index is odd and play nim
using stairs whose index is even.

```cpp
#include <iostream>
using namespace std;

int main() {
    int t;
    cin >> t;

    for (int ti = 1; ti <= t; ti++) {
        int n;
        cin >> n;
        int sum = 0;
        for (int i = 1; i <= n; i++) {
            int x;
            cin >> x;
            if (i % 2 == 0) sum ^= x;
        }
        cout << (sum != 0 ? "first" : "second") << "\n";
    }
}
```