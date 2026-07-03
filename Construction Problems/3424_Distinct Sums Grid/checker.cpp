/*
 * Problem:      3424 Distinct Sums Grid
 * Input read:   n
 * Validity:     IMPOSSIBLE iff no grid exists; else n x n grid with each value
 *               1..n appearing exactly n times and exactly 2n distinct row+column
 *               sums
 * Optimality:   any valid grid (no scalar from ans)
 * Complexity:   O(n^2)
 */
#include "testlib.h"
#include <vector>
#include <string>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();

    string ansFirst = ans.readToken();
    if (ansFirst == "IMPOSSIBLE") {
        string tok = ouf.readToken();
        if (tok != "IMPOSSIBLE")
            quitf(_wa, "Jury answer is IMPOSSIBLE but contestant printed \"%s\"",
                  compress(tok).c_str());
        if (!ouf.seekEof())
            quitf(_wa, "extra information in the output file");
        quitf(_ok, "correctly reported IMPOSSIBLE");
    }

    vector<vector<int>> grid(n, vector<int>(n));
    vector<int> freq(n + 1, 0);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            grid[i][j] = ouf.readInt(1, n, format("grid[%d][%d]", i + 1, j + 1).c_str());
            freq[grid[i][j]]++;
        }
    }

    for (int v = 1; v <= n; v++) {
        if (freq[v] != n)
            quitf(_wa, "Value %d appears %d times, must appear exactly %d times", v, freq[v], n);
    }

    set<int> sums;
    for (int i = 0; i < n; i++) {
        int row_sum = 0;
        for (int j = 0; j < n; j++)
            row_sum += grid[i][j];
        sums.insert(row_sum);
    }
    for (int j = 0; j < n; j++) {
        int col_sum = 0;
        for (int i = 0; i < n; i++)
            col_sum += grid[i][j];
        sums.insert(col_sum);
    }

    if ((int)sums.size() != 2 * n)
        quitf(_wa, "Got %d distinct row+column sums, expected %d", (int)sums.size(), 2 * n);

    if (!ouf.seekEof())
        quitf(_wa, "extra information in the output file");
    quitf(_ok, "valid grid with %d distinct sums", (int)sums.size());
}
