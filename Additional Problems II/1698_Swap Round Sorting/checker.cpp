/*

* Problem:      1698 Swap Round Sorting
* Input read:   n; permutation p[1..n]
* Validity:     Output k rounds; in each round, each index appears in at most one swap,
* ```
            all swap indices are in [1,n], and applying all swaps sorts the permutation
* Optimality:   k must equal the minimum number of rounds from ans
* Complexity:   O(n + total swaps) time, O(n) memory
  */
  #include "testlib.h"
  #include <bits/stdc++.h>
  using namespace std;

int main(int argc, char* argv[]) {
registerTestlibCmd(argc, argv);

int n = inf.readInt();

vector<int> cur(n + 1);
for (int i = 1; i <= n; i++) {
    cur[i] = inf.readInt();
}

int optimalRounds = ans.readInt();

int rounds = ouf.readInt(0, n, "number of rounds");
if (rounds != optimalRounds) {
    quitf(_wa, "contestant printed %d rounds, but optimum is %d",
          rounds, optimalRounds);
}

vector<int> usedMark(n + 1, 0);

for (int round = 1; round <= rounds; round++) {
    int cnt = ouf.readInt(0, n / 2, format("round[%d].swap_count", round).c_str());

    for (int s = 1; s <= cnt; s++) {
        int i = ouf.readInt(1, n, format("round[%d].swap[%d].i", round, s).c_str());
        int j = ouf.readInt(1, n, format("round[%d].swap[%d].j", round, s).c_str());

        if (i == j) {
            quitf(_wa, "round %d swap %d uses the same index %d twice", round, s, i);
        }

        if (usedMark[i] == round) {
            quitf(_wa, "round %d uses index %d more than once", round, i);
        }

        if (usedMark[j] == round) {
            quitf(_wa, "round %d uses index %d more than once", round, j);
        }

        usedMark[i] = round;
        usedMark[j] = round;

        swap(cur[i], cur[j]);
    }
}

for (int i = 1; i <= n; i++) {
    if (cur[i] != i) {
        quitf(_wa, "after all rounds, position %d has value %d, expected %d",
              i, cur[i], i);
    }
}

if (!ouf.seekEof())
    quitf(_wa, "extra information in the output file");

quitf(_ok, "valid optimal sorting with %d rounds", rounds);

}
