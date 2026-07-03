/*

* Problem:      1689 Knights Tour
* Input read:   starting position x, y
* Validity:     Output an 8x8 grid containing each number 1..64 exactly once; number 1
* ```
            must be at the requested start square, and consecutive numbers must be
* ```
            legal knight moves
* Optimality:   Any valid knight tour is accepted
* Complexity:   O(1) time and memory
  */
  #include "testlib.h"
  #include <bits/stdc++.h>
  using namespace std;

static bool is_knight_move(pair<int, int> a, pair<int, int> b) {
int dr = abs(a.first - b.first);
int dc = abs(a.second - b.second);

return (dr == 1 && dc == 2) || (dr == 2 && dc == 1);

}

int main(int argc, char* argv[]) {
registerTestlibCmd(argc, argv);

int x = inf.readInt();
int y = inf.readInt();

vector<pair<int, int>> pos(65, {-1, -1});
vector<char> seen(65, 0);

for (int row = 1; row <= 8; row++) {
    for (int col = 1; col <= 8; col++) {
        int value = ouf.readInt(1, 64, format("board[%d][%d]", row, col).c_str());

        if (seen[value]) {
            quitf(_wa, "number %d appears more than once", value);
        }

        seen[value] = 1;
        pos[value] = {row, col};
    }
}

for (int value = 1; value <= 64; value++) {
    if (!seen[value]) {
        quitf(_wa, "number %d is missing from the board", value);
    }
}

if (pos[1] != make_pair(y, x)) {
    quitf(_wa, "tour starts at row %d column %d, expected row %d column %d",
          pos[1].first, pos[1].second, y, x);
}

for (int value = 1; value < 64; value++) {
    if (!is_knight_move(pos[value], pos[value + 1])) {
        quitf(_wa,
              "move from %d at row %d column %d to %d at row %d column %d is not a knight move",
              value, pos[value].first, pos[value].second,
              value + 1, pos[value + 1].first, pos[value + 1].second);
    }
}

if (!ouf.seekEof())
    quitf(_wa, "extra information in the output file");

quitf(_ok, "valid knight tour");

}
