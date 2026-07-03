#include "testlib.h"
#include <vector>
#include <string>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    string ans_first = ans.readToken();
    bool ans_impossible = (ans_first == "IMPOSSIBLE");

    string first = ouf.readToken();
    if (first == "IMPOSSIBLE") {
        if (!ans_impossible)
            quitf(_wa, "A solution exists for n=%d but contestant printed IMPOSSIBLE", n);
        if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
        quitf(_ok, "Correct: no solution for n=%d", n);
    }

    if (ans_impossible)
        quitf(_wa, "No solution exists for n=%d but contestant printed a grid", n);

    vector<vector<int>> grid(n, vector<int>(n));
    vector<int> freq(n + 1, 0);

    grid[0][0] = stoi(first);
    if (grid[0][0] < 1 || grid[0][0] > n)
        quitf(_wa, "Value %d out of range [1,%d]", grid[0][0], n);
    freq[grid[0][0]]++;

    for (int i = 0; i < n; i++) {
        for (int j = (i == 0 ? 1 : 0); j < n; j++) {
            grid[i][j] = ouf.readInt();
            if (grid[i][j] < 1 || grid[i][j] > n)
                quitf(_wa, "Value %d out of range [1,%d]", grid[i][j], n);
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
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid grid with %d distinct sums", (int)sums.size());
}
