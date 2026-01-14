# 1689 - Knights Tour

# Solution 1

We use a recursive backtracking algorithm that explores possible partial
tours until it finds a complete tour.
The following code uses Warnsdorf's rule to make the search more efficient.
This rule defines the order in which we consider possible knight moves
during the search.

Let the *degree* of a square denote the number of empty squares
to which we can move from that square.
Using Warnsdorf's rule, we go through the moves in ascending order of
target square degrees.

```cpp
#include <algorithm>
#include <array>
#include <iostream>
#include <vector>
using namespace std;

#define N 8

vector<vector<int>> grid(N, vector<int>(N));

vector<int> dy = {1, 1, -1, -1, 2, 2, -2, -2};
vector<int> dx = {2, -2, 2, -2, 1, -1, 1, -1};

int degree(int y, int x) {
    int count = 0;
    for (int d = 0; d < N; d++) {
        int new_y = y + dy[d];
        int new_x = x + dx[d];
        if (new_y < 0 || new_y >= N || new_x < 0 || new_x >= N) continue;
        if (grid[new_y][new_x]) continue;
        count++;
    }
    return count;
}

void print() {
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            cout << grid[y][x] << " ";
        }
        cout << "\n";
    }
}

void search(int y, int x, int c) {
    if (grid[y][x]) return;
    grid[y][x] = c;

    if (c == N * N) {
        print();
        exit(0);
    }

    vector<array<int, 3>> choices;
    for (int d = 0; d < 8; d++) {
        int new_y = y + dy[d];
        int new_x = x + dx[d];
        if (new_y < 0 || new_y >= N || new_x < 0 || new_x >= N) continue;
        if (grid[new_y][new_x]) continue;
        choices.push_back({degree(new_y, new_x), new_y, new_x});
    }

    sort(choices.begin(), choices.end());
    for (auto [_, new_y, new_x] : choices) {
        search(new_y, new_x, c + 1);
    }

    grid[y][x] = 0;
}

int main() {
    int x, y;
    cin >> x >> y;

    search(y - 1, x - 1, 1);
}
```

# Solution 2

There is a simpler solution if we already have a precalculated knight's tour
with the additional requirement that
the knight can move from the last square back to the first square.
After finding such a tour, we can easily change the starting square
by shifting all elements in the grid.

To find the tour, we can use the algorithm from the first solution
with a small modification.

```cpp
#include <iostream>
#include <vector>
using namespace std;

#define N 8

vector<vector<int>> grid = {
    {1, 62, 59, 42, 37, 46, 49, 44}, {60, 41, 64, 53, 58, 43, 36, 47},
    {63, 2, 61, 38, 23, 48, 45, 50}, {40, 19, 54, 57, 52, 7, 24, 35},
    {3, 56, 39, 20, 25, 22, 51, 8},  {18, 13, 16, 55, 6, 29, 34, 31},
    {15, 4, 11, 26, 21, 32, 9, 28},  {12, 17, 14, 5, 10, 27, 30, 33}};

int main() {
    int x, y;
    cin >> x >> y;

    int shift = grid[y - 1][x - 1] - 1;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int step = grid[i][j] - shift;
            if (step <= 0) step += N * N;
            cout << step << " ";
        }
        cout << "\n";
    }
}
```

# References

* [Knight's tour (Wikipedia)](https://en.wikipedia.org/wiki/Knight's_tour)
* H. C. von Warnsdorf. Des Rösselsprunges einfachste und allgemeinste Lösung.
  Schmalkalden, 1823.