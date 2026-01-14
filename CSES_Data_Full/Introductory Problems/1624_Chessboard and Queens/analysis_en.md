# 1624 - Chessboard and Queens

The following code implements a backtracking algorithm that counts the number of solutions. The function `count` adds a queen to row $y$ and then adds the next queen recursively. When all queens have been added to the chessboard, a new solution has been found.

To make sure that no two queens attack each other, the code uses three arrays:

* `col` keeps track of columns that have a queen
* `diag1` keeps track of diagonals (first direction) that have a queen
* `diag2` keeps track of diagonals (second direction) that have a queen

```cpp
#include <iostream>
using namespace std;

const int N = 8;

string grid[N];
int total;
bool col[N], diag1[2 * N], diag2[2 * N];

void search(int y) {
    if (y == N) {
        total++;
        return;
    }
    for (int x = 0; x < N; x++) {
        if (grid[y][x] == '*') {
            continue;
        }
        if (col[x] || diag1[x + y] || diag2[y - x + N]) {
            continue;
        }
        col[x] = diag1[x + y] = diag2[y - x + N] = true;
        search(y + 1);
        col[x] = diag1[x + y] = diag2[y - x + N] = false;
    }
}

int main() {
    for (auto &row : grid) {
        cin >> row;
    }
    search(0);
    cout << total << "\n";
}
```

## References

* [Eight queens puzzle (Wikipedia)](https://en.wikipedia.org/wiki/Eight_queens_puzzle)