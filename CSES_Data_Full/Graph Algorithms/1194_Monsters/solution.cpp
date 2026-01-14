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
