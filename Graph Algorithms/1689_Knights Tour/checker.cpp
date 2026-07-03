#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int x = inf.readInt();
    int y = inf.readInt();
    vector<vector<int>> grid(8, vector<int>(8));
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            grid[r][c] = ouf.readInt();
            if (grid[r][c] < 1 || grid[r][c] > 64)
                quitf(_wa, "Grid value %d out of range [1,64] at (%d,%d)", grid[r][c], r + 1, c + 1);
        }
    }
    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");

    vector<bool> seen(65, false);
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            int val = grid[r][c];
            if (seen[val])
                quitf(_wa, "Number %d appears more than once", val);
            seen[val] = true;
        }
    }

    vector<pair<int, int>> pos(65);
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++)
            pos[grid[r][c]] = {r, c};
    }

    if (pos[1].first != y - 1 || pos[1].second != x - 1)
        quitf(_wa, "Starting position must be (%d,%d), got (%d,%d)",
              x, y, pos[1].second + 1, pos[1].first + 1);

    for (int step = 1; step < 64; step++) {
        int r1 = pos[step].first, c1 = pos[step].second;
        int r2 = pos[step + 1].first, c2 = pos[step + 1].second;
        int dr = abs(r1 - r2), dc = abs(c1 - c2);
        if (!((dr == 2 && dc == 1) || (dr == 1 && dc == 2)))
            quitf(_wa,
                  "Move from step %d to %d ((%d,%d) to (%d,%d)) is not a valid knight move",
                  step, step + 1, c1 + 1, r1 + 1, c2 + 1, r2 + 1);
    }

    quitf(_ok, "Valid knight's tour");
}
