/*

* Problem:      1709 Coin Grid
* Input read:   n; n grid rows
* Validity:     Output k moves; each move removes one row or one column, and every coin
* ```
            must be removed by at least one chosen row/column
* Optimality:   k must equal the minimum number of moves from ans
* Complexity:   O(n^2 + k) time, O(n) memory
  */
  #include "testlib.h"
  #include <bits/stdc++.h>
  using namespace std;

int main(int argc, char* argv[]) {
registerTestlibCmd(argc, argv);

int n = inf.readInt();

vector<string> grid(n);
for (int i = 0; i < n; i++) {
    grid[i] = inf.readToken();

    if ((int)grid[i].size() != n) {
        quitf(_fail, "input row %d has length %d, expected %d",
              i + 1, (int)grid[i].size(), n);
    }
}

int optimal = ans.readInt();

int k = ouf.readInt(0, 2 * n, "number of moves");
if (k != optimal) {
    quitf(_wa, "contestant printed %d moves, but optimum is %d", k, optimal);
}

vector<char> removedRow(n, 0), removedCol(n, 0);

for (int move = 1; move <= k; move++) {
    int type = ouf.readInt(1, 2, format("move[%d].type", move).c_str());
    int idx = ouf.readInt(1, n, format("move[%d].index", move).c_str()) - 1;

    if (type == 1) {
        removedRow[idx] = 1;
    } else {
        removedCol[idx] = 1;
    }
}

for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
        if (grid[i][j] == 'o' && !removedRow[i] && !removedCol[j]) {
            quitf(_wa, "coin at row %d column %d is not removed", i + 1, j + 1);
        }
    }
}

if (!ouf.seekEof())
    quitf(_wa, "extra information in the output file");

quitf(_ok, "all coins removed in optimal %d moves", k);

}
