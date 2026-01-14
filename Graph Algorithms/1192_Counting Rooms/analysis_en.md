# 1192 - Counting Rooms

We solve the problem going through every
square in the map while remembering the number of encountered unique rooms.
If the square is a wall or a visited
room square, we continue to the next location. Otherwise we are in a
square that is part of an unvisited room. We increase the counter of unique rooms
and mark all of the locations in this room visited by using depth-first search.

This corresponds to finding the number of connected components in a graph
defined by the map.

The time complexity of the solution is $O(nm)$ as we go through $nm$ squares
in the main loop and the total number of squares visited by the depth-first
search is $nm$.

```cpp
#include <iostream>
using namespace std;
const int MN = 1001;
string building[MN];
int n, m;

void dfs(int r, int c) {
    if (building[r][c] != '.') return;
    building[r][c] = '#';
    pair<int, int> deltas[]{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    for (auto [dr, dc] : deltas) {
        int new_r = r + dr;
        int new_c = c + dc;
        if (new_r >= 0 && new_r < n && new_c >= 0 && new_c < m) {
            dfs(new_r, new_c);
        }
    }
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        cin >> building[i];
    }

    int n_rooms = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (building[i][j] == '.') {
                ++n_rooms;
                dfs(i, j);
            }
        }
    }
    cout << n_rooms << endl;
}
```