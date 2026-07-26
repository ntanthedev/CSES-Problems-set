/*

* Problem:      2165 Tower of Hanoi
* Input read:   n
* Validity:     Output k minimum moves, followed by k legal moves between stacks 1..3;
* ```
            all disks must end on stack 3 and no larger disk may be placed on a smaller disk
* Optimality:   k must equal 2^n - 1 from ans
* Complexity:   O(2^n) time, O(2^n + n) memory; n <= 16
  */
  #include "testlib.h"
  #include <bits/stdc++.h>
  using namespace std;

int main(int argc, char* argv[]) {
registerTestlibCmd(argc, argv);

int n = inf.readInt();

int optimal = ans.readInt();
int maxMoves = (1 << n) - 1;

if (optimal != maxMoves) {
    quitf(_fail, "jury answer has %d moves, expected %d", optimal, maxMoves);
}

int k = ouf.readInt(0, maxMoves, "number of moves");

if (k != optimal) {
    quitf(_wa, "contestant printed %d moves, but optimum is %d", k, optimal);
}

vector<int> stacks[4];
for (int disk = n; disk >= 1; disk--) {
    stacks[1].push_back(disk);
}

for (int move = 1; move <= k; move++) {
    int from = ouf.readInt(1, 3, format("move[%d].from", move).c_str());
    int to = ouf.readInt(1, 3, format("move[%d].to", move).c_str());

    if (from == to) {
        quitf(_wa, "move %d has identical source and target stack %d", move, from);
    }

    if (stacks[from].empty()) {
        quitf(_wa, "move %d tries to move from empty stack %d", move, from);
    }

    int disk = stacks[from].back();

    if (!stacks[to].empty() && stacks[to].back() < disk) {
        quitf(_wa,
              "move %d tries to place disk %d on smaller disk %d",
              move, disk, stacks[to].back());
    }

    stacks[from].pop_back();
    stacks[to].push_back(disk);
}

if (!stacks[1].empty() || !stacks[2].empty() || (int)stacks[3].size() != n) {
    quitf(_wa, "after all moves, not all disks are on stack 3");
}

for (int i = 0; i < n; i++) {
    if (stacks[3][i] != n - i) {
        quitf(_wa, "final stack 3 has invalid disk order");
    }
}

if (!ouf.seekEof())
    quitf(_wa, "extra information in the output file");

quitf(_ok, "valid optimal Hanoi solution with %d moves", k);

}
