# 3311 - Grid Coloring I

We can solve the problem greedily by iterating through the grid from top to bottom and left to right.

For each square, we choose the first character that is not the original character of the square
and is also not the same as the character to the left or the character above.
Since there are four possible characters, we can always find a valid character.

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<string> grid(n);
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }

    for (int y = 0; y < n; y++) {
        for (int x = 0; x < m; x++) {
            for (int c = 'A'; c <= 'D'; c++) {
                bool fail = false;
                if (grid[y][x] == c) fail = true;
                if (y > 0 && grid[y - 1][x] == c) fail = true;
                if (x > 0 && grid[y][x - 1] == c) fail = true;
                if (!fail) {
                    grid[y][x] = c;
                    break;
                }
            }
            cout << grid[y][x];
        }
        cout << "\n";
    }
}
```