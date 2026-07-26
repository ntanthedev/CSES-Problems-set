/*
 * Problem:      1194 Monsters
 * Input read:   n, m; n grid rows (each m chars: . # A M)
 * Validity:     YES/NO matches possibility; if YES: path length <= n*m, steps are
 *               D/U/L/R on walkable cells, never shares square with monster at
 *               same time, ends on boundary
 * Optimality:   any valid path (no scalar from ans)
 * Complexity:   O(n*m) BFS + O(path length)
 */
#include "testlib.h"
#include <vector>
#include <string>
#include <queue>
using namespace std;

const int INF = 1000000000;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = inf.readInt();
    vector<string> grid(n);
    pair<int, int> start{-1, -1};
    for (int i = 0; i < n; i++) {
        grid[i] = inf.readToken();
        if ((int)grid[i].size() != m)
            quitf(_fail, "Grid row %d has length %d, expected %d", i + 1, (int)grid[i].size(), m);
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'A')
                start = {i, j};
        }
    }
    if (start.first == -1)
        quitf(_fail, "No starting position A in input");

    int dr[] = {0, 1, 0, -1};
    int dc[] = {1, 0, -1, 0};
    vector<vector<int>> mdist(n, vector<int>(m, INF));
    queue<pair<int, int>> q;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'M') {
                mdist[i][j] = 0;
                q.push({i, j});
            }
        }
    }
    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();
        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d], nc = c + dc[d];
            if (nr >= 0 && nr < n && nc >= 0 && nc < m &&
                grid[nr][nc] != '#' && mdist[nr][nc] == INF) {
                mdist[nr][nc] = mdist[r][c] + 1;
                q.push({nr, nc});
            }
        }
    }

    string ansFlag = ans.readToken();
    if (ansFlag != "YES" && ansFlag != "NO")
        quitf(_fail, "Invalid judge answer token '%s'", ansFlag.c_str());

    string outFlag = ouf.readToken();
    if (outFlag != "YES" && outFlag != "NO")
        quitf(_wa, "Expected YES or NO, got '%s'", outFlag.c_str());

    if (outFlag == "NO") {
        if (ansFlag != "NO")
            quitf(_wa, "Contestant printed NO but escape is possible");
        if (!ouf.seekEof())
            quitf(_wa, "extra information in the output file");
        quitf(_ok, "correctly reported no escape");
    }

    if (ansFlag == "NO")
        quitf(_wa, "Contestant printed YES but escape is impossible");

    int maxLen = n * m;
    int len = ouf.readInt(0, maxLen, "path length");
    string path;
    if (len > 0)
        path = ouf.readToken();
    if ((int)path.size() != len)
        quitf(_wa, "Path length %d does not match string length %d", len, (int)path.size());

    int r = start.first, c = start.second;
    for (int step = 0; step < len; step++) {
        char ch = path[step];
        int nr = r, nc = c;
        if (ch == 'L') nc--;
        else if (ch == 'R') nc++;
        else if (ch == 'U') nr--;
        else if (ch == 'D') nr++;
        else quitf(_wa, "Invalid direction '%c' at step %d", ch, step + 1);

        if (nr < 0 || nr >= n || nc < 0 || nc >= m)
            quitf(_wa, "Path goes out of bounds at step %d", step + 1);
        if (grid[nr][nc] == '#')
            quitf(_wa, "Path walks into a wall at step %d", step + 1);
        if (mdist[nr][nc] <= step + 1)
            quitf(_wa, "Monster reaches (%d,%d) at time %d", nr + 1, nc + 1, step + 1);

        r = nr;
        c = nc;
    }

    if (r != 0 && r != n - 1 && c != 0 && c != m - 1)
        quitf(_wa, "Path ends at (%d,%d), not on boundary", r + 1, c + 1);

    if (!ouf.seekEof())
        quitf(_wa, "extra information in the output file");
    quitf(_ok, "valid escape path of length %d", len);
}
