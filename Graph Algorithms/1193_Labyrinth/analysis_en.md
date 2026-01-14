# 1193 - Labyrinth

We start by forming a graph corresponding to the labyrinth.
In this graph, every node corresponds to a square in the labyrinth.
Two nodes are connected by an edge if and only if the corresponding
squares have a common side and neither of the squares is wall.
All of the edges have unit length.

The length of the shortest path in such a graph can be found with the breadth-first search (BFS).
We are also asked to construct the shortest path. To do this we modify the
BFS somewhat.

When processing a node $x$ and adding a new node $y$ to the BFS queue we
also store some additional information which we associate with the node $y$:

* The position of $x$. This is stored in the `previous` array and corresponds
  to the second-last position in the shortest path from `A` to $y$.
* The direction of the move to $y$. This is stored in the `last_letter` array
  and corresponds to the last move in the shortest path from `A` to $y$.

After finishing the BFS we then construct the shortest path in a reversed order.
To do this we start from `B` and follow the positions in `previous` until we
arrive at `A`. This means we follow the shortest path from the end to the beginning.
For every visited position (except the `A`) we add the letter in `last_letter`
to the `ans` string.

When we are done with this, we reverse `ans` and print it.

The number of edges in the graph and the length of the shortest path are both $O(nm)$ so
the total time complexity is also $O(nm)$.

```cpp
#include <algorithm>
#include <iostream>
#include <queue>
#include <tuple>
using namespace std;
const int N = 1001;
string grid[N];
bool visited[N][N];
pair<int, int> previous[N][N];
char last_letter[N][N];

tuple<int, int, char> moves[]{
    {0, 1, 'R'}, {1, 0, 'D'}, {0, -1, 'L'}, {-1, 0, 'U'}};

int main() {
    int n, m;
    cin >> n >> m;

    pair<int, int> a;
    pair<int, int> b;
    for (int i = 0; i < n; ++i) {
        cin >> grid[i];
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == 'A') a = {i, j};
            if (grid[i][j] == 'B') b = {i, j};
        }
    }

    queue<pair<int, int>> queue;
    queue.push(a);
    visited[a.first][a.second] = true;

    while (!queue.empty()) {
        auto [r, c] = queue.front();
        queue.pop();
        for (auto [delta_r, delta_c, letter] : moves) {
            int new_r = r + delta_r;
            int new_c = c + delta_c;
            if (new_r >= 0 && new_r < n && new_c >= 0 && new_c < m) {
                if (grid[new_r][new_c] == '#') continue;
                if (visited[new_r][new_c]) continue;
                visited[new_r][new_c] = true;
                previous[new_r][new_c] = {r, c};
                last_letter[new_r][new_c] = letter;
                queue.emplace(new_r, new_c);
            }
        }
    }

    if (!visited[b.first][b.second]) {
        cout << "NO\n";
        return 0;
    }
    string ans;
    auto pos = b;
    while (pos != a) {
        auto [r, c] = pos;
        ans += last_letter[r][c];
        pos = previous[r][c];
    }
    reverse(ans.begin(), ans.end());
    cout << "YES\n";
    cout << ans.size() << '\n';
    cout << ans << '\n';
}
```