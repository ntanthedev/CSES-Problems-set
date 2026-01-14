# 3217 - Knight Moves Grid

We first place the number $0$ in the top-left square. Subsequently, for $x=1,2,3,\dots$, we place the number $x$ in all unvisited squares that can be reached in one move from a square containing the number $x-1$. This process continues until all squares have been visited.

This approach can be efficiently implemented using a queue that stores squares in order of increasing distance. The algorithm is similar to the breadth-first search algorithm.

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<vector<int>> grid(n, vector<int>(n, -1));
    vector<pair<int, int>> queue;

    grid[0][0] = 0;
    queue.emplace_back(0, 0);

    int dy[8] = {1, 1, -1, -1, 2, 2, -2, -2};
    int dx[8] = {2, -2, 2, -2, 1, -1, 1, -1};

    for (int i = 0; i < queue.size(); i++) {
        auto [y, x] = queue[i];
        for (int d = 0; d < 8; d++) {
            int ny = y + dy[d];
            int nx = x + dx[d];
            if (ny < 0 || ny >= n || nx < 0 || nx >= n || grid[ny][nx] != -1) {
                continue;
            }
            grid[ny][nx] = grid[y][x] + 1;
            queue.emplace_back(ny, nx);
        }
    }

    for (int y = 0; y < n; y++) {
        for (int x = 0; x < n; x++) {
            cout << grid[y][x] << " ";
        }
        cout << "\n";
    }
}
```