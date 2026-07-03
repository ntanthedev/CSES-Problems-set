/*

* Problem:      2131 Grid Puzzle II
* Input read:   n; row requirements a[1..n], column requirements b[1..n], n x n coin grid
* Validity:     -1 iff jury says impossible; otherwise output optimal coin total followed by
* ```
            n rows over X/. satisfying all row and column counts, with selected sum equal
* ```
            to the claimed optimum
* Optimality:   Claimed total must equal the maximum total from ans
* Complexity:   O(n^2) time, O(n^2) memory
  */
  #include "testlib.h"
  #include <bits/stdc++.h>
  using namespace std;

int main(int argc, char* argv[]) {
registerTestlibCmd(argc, argv);

int n = inf.readInt();

vector<int> rowNeed(n), colNeed(n);
for (int i = 0; i < n; i++) {
    rowNeed[i] = inf.readInt();
}

for (int j = 0; j < n; j++) {
    colNeed[j] = inf.readInt();
}

vector<vector<int>> coins(n, vector<int>(n));
int maxTotal = 0;

for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
        coins[i][j] = inf.readInt();
        maxTotal += coins[i][j];
    }
}

int ansFirst = ans.readInt();

if (ansFirst == -1) {
    int outFirst = ouf.readInt(-1, maxTotal, "answer");

    if (outFirst != -1) {
        quitf(_wa, "jury answer is -1, but contestant claimed value %d", outFirst);
    }

    if (!ouf.seekEof())
        quitf(_wa, "extra information in the output file");

    quitf(_ok, "correctly reported -1");
}

int claimed = ouf.readInt(-1, maxTotal, "maximum coins");

if (claimed == -1) {
    quitf(_wa, "a feasible optimal selection exists, but contestant printed -1");
}

if (claimed != ansFirst) {
    quitf(_wa, "contestant claimed maximum %d, but optimum is %d",
          claimed, ansFirst);
}

vector<string> grid(n);
long long total = 0;

for (int i = 0; i < n; i++) {
    grid[i] = ouf.readToken(format("[X.]{%d}", n), format("row[%d]", i + 1).c_str());

    int rowCnt = 0;
    for (int j = 0; j < n; j++) {
        if (grid[i][j] == 'X') {
            rowCnt++;
            total += coins[i][j];
        }
    }

    if (rowCnt != rowNeed[i]) {
        quitf(_wa, "row %d has %d selected squares, expected %d",
              i + 1, rowCnt, rowNeed[i]);
    }
}

for (int j = 0; j < n; j++) {
    int colCnt = 0;

    for (int i = 0; i < n; i++) {
        if (grid[i][j] == 'X') {
            colCnt++;
        }
    }

    if (colCnt != colNeed[j]) {
        quitf(_wa, "column %d has %d selected squares, expected %d",
              j + 1, colCnt, colNeed[j]);
    }
}

if (total != claimed) {
    quitf(_wa, "claimed maximum is %d, but selected squares sum to %lld",
          claimed, total);
}

if (!ouf.seekEof())
    quitf(_wa, "extra information in the output file");

quitf(_ok, "valid optimal selection with %lld coins", total);

}
