#include "testlib.h"
#include <queue>
#include <string>
#include <vector>
using namespace std;

static bool is_tromino(const vector<pair<int, int>>& cells) {
    if ((int)cells.size() != 3)
        return false;

    auto adj = [](int r1, int c1, int r2, int c2) {
        return abs(r1 - r2) + abs(c1 - c2) == 1;
    };

    int r1 = cells[0].first, c1 = cells[0].second;
    int r2 = cells[1].first, c2 = cells[1].second;
    int r3 = cells[2].first, c3 = cells[2].second;

    if (adj(r1, c1, r2, c2) && adj(r1, c1, r3, c3) && !adj(r2, c2, r3, c3))
        return true;
    if (adj(r2, c2, r1, c1) && adj(r2, c2, r3, c3) && !adj(r1, c1, r3, c3))
        return true;
    if (adj(r3, c3, r1, c1) && adj(r3, c3, r2, c2) && !adj(r1, c1, r2, c2))
        return true;
    return false;
}

static void validate_grid(int n, int m, const vector<string>& grid) {
    vector<vector<bool>> seen(n, vector<bool>(m, false));
    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] < 'A' || grid[i][j] > 'Z')
                quitf(_wa, "Invalid character '%c' at (%d,%d)", grid[i][j], i + 1, j + 1);
            if (seen[i][j])
                continue;

            char letter = grid[i][j];
            vector<pair<int, int>> comp;
            queue<pair<int, int>> q;
            q.push({i, j});
            seen[i][j] = true;

            while (!q.empty()) {
                auto [r, c] = q.front();
                q.pop();
                comp.push_back({r, c});
                for (int d = 0; d < 4; d++) {
                    int nr = r + dr[d], nc = c + dc[d];
                    if (nr < 0 || nr >= n || nc < 0 || nc >= m)
                        continue;
                    if (seen[nr][nc] || grid[nr][nc] != letter)
                        continue;
                    seen[nr][nc] = true;
                    q.push({nr, nc});
                }
            }

            if (!is_tromino(comp))
                quitf(_wa,
                      "Letter '%c' component at (%d,%d) is not a valid L-tromino (%d cells)",
                      letter, i + 1, j + 1, (int)comp.size());
        }
    }
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int t = inf.readInt();
    for (int test = 0; test < t; test++) {
        int n = inf.readInt();
        int m = inf.readInt();
        string ans_flag = ans.readToken();
        string ouf_flag = ouf.readToken();

        if (ans_flag == "NO") {
            if (ouf_flag != "NO")
                quitf(_wa, "Test %d: no valid tiling exists but contestant printed '%s'", test + 1, ouf_flag.c_str());
            continue;
        }

        if (ans_flag != "YES")
            quitf(_fail, "Test %d: judge answer malformed, expected YES or NO", test + 1);

        if (ouf_flag == "NO")
            quitf(_wa, "Test %d: a valid tiling exists but contestant printed NO", test + 1);
        if (ouf_flag != "YES")
            quitf(_wa, "Test %d: expected YES or NO, got '%s'", test + 1, ouf_flag.c_str());

        for (int i = 0; i < n; i++)
            ans.readToken();

        vector<string> grid(n);
        for (int i = 0; i < n; i++) {
            grid[i] = ouf.readToken();
            if ((int)grid[i].size() != m)
                quitf(_wa, "Test %d row %d has %d characters, expected %d",
                      test + 1, i + 1, (int)grid[i].size(), m);
        }

        validate_grid(n, m, grid);
    }

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "All %d tests passed", t);
}
