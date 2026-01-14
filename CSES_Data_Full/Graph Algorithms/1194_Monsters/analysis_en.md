# 1194 - Monsters

We start solving the problem by calculating, for each square,
the distance to the nearest monster. We store this in the array `m_dist`.
This is done by running breadth-first search (BFS) with the BFS
queue initialized with the initial monster positions.

Then we calculate with BFS the distances from `A` to each square and store
these in the array `a_dist`. We also associate with each square:

* In the array `parent`, the parent square in the BFS tree.
* In the array `last_letter`, the letter denoting the last move.

Additionally we check for each boundary square `s` if `a_dist[s] < m_dist[s]`.

If we didn't find any such square, then the mosters can arrive at each
boundary square at the same time with us. In this case we print
`NO` and exit the program.

Let's then assume we found such a square `s`. Now if we follow the shortest route from
`A` to `s`, then we will reach `s` before any monster. Therefore we will not
share the square `s` with any monster. This also means that we will not share any square
in the shortest path to `s` with a monster. If we shared any square in the shortest
path, then the monster could always take the same move as us, finally
sharing the square `s` with us, which is impossible.

We will then follow the path from `s` defined by the `parent` array
and construct a reversed string of letters denoting the path. Finally we
reverse the path string and print it.

The time complexity of the solution is $O(nm)$.

```cpp
#include <algorithm>
#include <iostream>
#include <optional>
#include <queue>
#include <tuple>
using namespace std;

const int N = 1001;
const int INF = 1000000;
string grid[N];
int m_dist[N][N];
int a_dist[N][N];
pair<int, int> parent[N][N];
char last_letter[N][N];

tuple<int, int, char> moves[]{
    {0, 1, 'R'}, {1, 0, 'D'}, {0, -1, 'L'}, {-1, 0, 'U'}};

int main() {
    int n, m;
    cin >> n >> m;
    pair<int, int> a;
    queue<pair<int, int>> queue;
    for (int i = 0; i < n; ++i) {
        cin >> grid[i];
        for (int j = 0; j < m; ++j) {
            m_dist[i][j] = INF;
            a_dist[i][j] = INF;
            if (grid[i][j] == 'M') {
                m_dist[i][j] = 0;
                queue.emplace(i, j);
            }
            if (grid[i][j] == 'A') {
                a_dist[i][j] = 0;
                a = {i, j};
            }
        }
    }

    while (!queue.empty()) {
        auto [r, c] = queue.front();
        queue.pop();
        for (auto [dr, dc, letter] : moves) {
            int new_r = r + dr;
            int new_c = c + dc;
            if (new_r >= 0 && new_r < n && new_c >= 0 && new_c < m) {
                if (grid[new_r][new_c] == '#') continue;
                if (m_dist[new_r][new_c] < INF) continue;
                m_dist[new_r][new_c] = m_dist[r][c] + 1;
                queue.emplace(new_r, new_c);
            }
        }
    }

    queue.push(a);
    optional<pair<int, int>> exit_square;

    while (!queue.empty()) {
        auto [r, c] = queue.front();
        if (r == 0 || r == n - 1 || c == 0 || c == m - 1) {
            if (a_dist[r][c] < m_dist[r][c]) {
                exit_square = {r, c};
                break;
            }
        }
        queue.pop();
        for (auto [dr, dc, letter] : moves) {
            int new_r = r + dr;
            int new_c = c + dc;
            if (new_r >= 0 && new_r < n && new_c >= 0 && new_c < m) {
                if (grid[new_r][new_c] == '#') continue;
                if (a_dist[new_r][new_c] < INF) continue;
                a_dist[new_r][new_c] = a_dist[r][c] + 1;
                parent[new_r][new_c] = {r, c};
                last_letter[new_r][new_c] = letter;
                queue.emplace(new_r, new_c);
            }
        }
    }

    if (!exit_square) {
        cout << "NO\n";
        return 0;
    }
    string ans;
    pair<int, int> x = *exit_square;
    while (x != a) {
        auto [r, c] = x;
        ans += last_letter[r][c];
        x = parent[r][c];
    }
    reverse(ans.begin(), ans.end());
    cout << "YES\n";
    cout << ans.size() << '\n';
    cout << ans << '\n';
}
```