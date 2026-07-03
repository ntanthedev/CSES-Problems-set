/*

* Problem:      2423 Filling Trominos
* Input read:   t; for each test n, m
* Validity:     For each test, NO iff jury says impossible; otherwise YES followed by n rows
* ```
            of m letters A-Z whose same-letter connected components are L-trominoes
* Optimality:   Feasibility is taken from ans; any valid tiling is accepted
* Complexity:   O(total n*m) time, O(n*m) memory per test
  */
  #include "testlib.h"
  #include <bits/stdc++.h>
  using namespace std;

static bool is_l_tromino(const vector<pair<int, int>>& cells) {
if ((int)cells.size() != 3) return false;

int minr = cells[0].first, maxr = cells[0].first;
int minc = cells[0].second, maxc = cells[0].second;
for (auto [r, c] : cells) {
    minr = min(minr, r);
    maxr = max(maxr, r);
    minc = min(minc, c);
    maxc = max(maxc, c);
}

return maxr - minr == 1 && maxc - minc == 1;

}

static void validate_grid(int test, int n, int m, const vector<string>& grid) {
vector<vector<char>> seen(n, vector<char>(m, 0));
const int dr[4] = {-1, 1, 0, 0};
const int dc[4] = {0, 0, -1, 1};

for (int i = 0; i < n; i++) {
    if ((int)grid[i].size() != m) {
        quitf(_wa, "test %d: row %d has length %d, expected %d",
              test, i + 1, (int)grid[i].size(), m);
    }
    for (int j = 0; j < m; j++) {
        if (grid[i][j] < 'A' || grid[i][j] > 'Z') {
            quitf(_wa, "test %d: invalid character '%c' at row %d column %d",
                  test, grid[i][j], i + 1, j + 1);
        }
    }
}

for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
        if (seen[i][j]) continue;

        char ch = grid[i][j];
        vector<pair<int, int>> comp;
        queue<pair<int, int>> q;
        q.push({i, j});
        seen[i][j] = 1;

        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();
            comp.push_back({r, c});

            for (int d = 0; d < 4; d++) {
                int nr = r + dr[d], nc = c + dc[d];
                if (nr < 0 || nr >= n || nc < 0 || nc >= m) continue;
                if (seen[nr][nc] || grid[nr][nc] != ch) continue;
                seen[nr][nc] = 1;
                q.push({nr, nc});
            }
        }

        if (!is_l_tromino(comp)) {
            quitf(_wa,
                  "test %d: component of letter '%c' starting at row %d column %d is not an L-tromino; size = %d",
                  test, ch, i + 1, j + 1, (int)comp.size());
        }
    }
}

}

int main(int argc, char* argv[]) {
registerTestlibCmd(argc, argv);

int t = inf.readInt();

for (int tc = 1; tc <= t; tc++) {
    int n = inf.readInt();
    int m = inf.readInt();

    string ansFlag = ans.readToken();
    if (ansFlag != "YES" && ansFlag != "NO") {
        quitf(_fail, "test %d: malformed jury answer token '%s'",
              tc, compress(ansFlag).c_str());
    }

    if (ansFlag == "YES") {
        for (int i = 0; i < n; i++) ans.readToken();
    }

    string outFlag = ouf.readToken();
    if (outFlag != "YES" && outFlag != "NO") {
        quitf(_wa, "test %d: expected YES or NO, got '%s'",
              tc, compress(outFlag).c_str());
    }

    if (ansFlag == "NO") {
        if (outFlag != "NO") {
            quitf(_wa, "test %d: no valid tiling exists, but contestant printed YES", tc);
        }
        continue;
    }

    if (outFlag == "NO") {
        quitf(_wa, "test %d: a valid tiling exists, but contestant printed NO", tc);
    }

    vector<string> grid(n);
    for (int i = 0; i < n; i++) {
        grid[i] = ouf.readToken();
    }

    validate_grid(tc, n, m, grid);
}

if (!ouf.seekEof())
    quitf(_wa, "extra information in the output file");

quitf(_ok, "all %d tests passed", t);

}
