# 1729 - Stick Game

We go through the states $1,2,\dots,n$ and determine the position of each state.
If there is a move that leads to a losing position, then we are in a winning
position, and otherwise we are in a losing position.

The algorithm works in $O(nk)$ time where $n$ is the number of sticks and $k$ is
the number of moves.

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> move(k);
    for (int i = 0; i < k; i++) {
        cin >> move[i];
    }

    string pos(n + 1, 'L');
    for (int i = 1; i <= n; i++) {
        for (auto m : move) {
            if (i - m >= 0 && pos[i - m] == 'L') {
                pos[i] = 'W';
            }
        }
    }
    cout << pos.substr(1) << "\n";
}
```