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
