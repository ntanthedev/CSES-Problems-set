# 1625 - Grid Path Description

We can use a recursive backtracking algorithm to solve the problem. However, since the number of possible paths is large, we have to prune the search so that the algorithm is efficient enough.

We maintain an array `grid` that contains the status of each square. If the status is 0, the square is empty and we can visit it. If the status is 1, the square is wall or we have already visited it. Note that the array has a border of wall squares which makes it easier to implement the search.

There are two optimizations in the search. First, we always terminate the search after visiting the bottom-left square. If we have visited all other squares before that, we have found a valid solution. Otherwise it is clear that we cannot create a valid solution because we visited the final square too early.

Second, if we are in a square where both adjacent squares in one direction have status 0 and both adjacent squares in another direction have status 1, we terminate the search. In this case the grid has at least two separate components of empty squares, and it is not possible to visit all the squares anymore.

```cpp
#include <iostream>
using namespace std;

const int N = 7;

int grid[N + 2][N + 2];
string path;
int total;

void search(int y, int x, int c) {
    if (grid[y][x]) return;

    if (y == N && x == 1) {
        if (c == N * N) total++;
        return;
    }

    bool down = grid[y + 1][x];
    bool up = grid[y - 1][x];
    bool left = grid[y][x - 1];
    bool right = grid[y][x + 1];
    if (down && up && !left && !right) return;
    if (!down && !up && left && right) return;

    char d = path[c - 1];
    grid[y][x] = 1;
    if (d == '?' || d == 'D') search(y + 1, x, c + 1);
    if (d == '?' || d == 'U') search(y - 1, x, c + 1);
    if (d == '?' || d == 'L') search(y, x - 1, c + 1);
    if (d == '?' || d == 'R') search(y, x + 1, c + 1);
    grid[y][x] = 0;
}

int main() {
    for (int i = 0; i <= N + 1; i++) {
        grid[0][i] = grid[N + 1][i] = 1;
        grid[i][0] = grid[i][N + 1] = 1;
    }

    cin >> path;
    search(1, 1, 1);
    cout << total << "\n";
}
```