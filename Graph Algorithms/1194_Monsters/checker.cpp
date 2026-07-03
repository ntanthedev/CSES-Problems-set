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
    pair<int, int> start;
    vector<pair<int, int>> monsters;
    for (int i = 0; i < n; i++) {
        grid[i] = inf.readLine();
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'A') start = {i, j};
            if (grid[i][j] == 'M') monsters.push_back({i, j});
        }
    }

    int dr[] = {0, 1, 0, -1};
    int dc[] = {1, 0, -1, 0};
    vector<vector<int>> mdist(n, vector<int>(m, INF));
    queue<pair<int, int>> q;
    for (auto [r, c] : monsters) {
        mdist[r][c] = 0;
        q.push({r, c});
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
            quitf(_wa, "Output is NO but escape is possible");
        if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
        quitf(_ok, "Correct: no escape");
    }

    if (ansFlag == "NO")
        quitf(_wa, "Escape is possible but output is NO");

    if (ansFlag == "YES")
        ans.readInt(), ans.readToken();

    int len = ouf.readInt();
    string path = ouf.readToken();

    if ((int)path.size() != len)
        quitf(_wa, "Path length %d does not match string length %d", len, (int)path.size());
    if (len > n * m)
        quitf(_wa, "Path length %d exceeds maximum %d", len, n * m);

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
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid escape path of length %d", len);
}
