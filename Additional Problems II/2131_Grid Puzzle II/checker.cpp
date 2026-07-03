#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    vector<int> a(n), b(n);
    vector<vector<int>> coins(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        a[i] = inf.readInt();
    for (int i = 0; i < n; i++)
        b[i] = inf.readInt();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            coins[i][j] = inf.readInt();

    int k_ans = ans.readInt();
    int k = ouf.readInt();

    if (k == -1) {
        if (k_ans != -1)
            quitf(_wa, "Output is -1 but a valid selection exists");
        if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
        quitf(_ok, "Correctly reported impossible");
    }

    if (k_ans == -1)
        quitf(_wa, "Expected -1 (impossible), but contestant claimed %d coins", k);

    if (k != k_ans)
        quitf(_wa, "Claimed %d coins but optimal is %d", k, k_ans);

    vector<string> grid(n);
    for (int i = 0; i < n; i++) {
        grid[i] = ouf.readToken();
        if ((int)grid[i].size() != n)
            quitf(_wa, "Row %d has length %d, expected %d", i + 1, (int)grid[i].size(), n);
    }

    long long total = 0;
    for (int i = 0; i < n; i++) {
        int rowCnt = 0;
        for (int j = 0; j < n; j++) {
            if (grid[i][j] != 'X' && grid[i][j] != '.')
                quitf(_wa, "Invalid character '%c' at (%d,%d)", grid[i][j], i + 1, j + 1);
            if (grid[i][j] == 'X') {
                rowCnt++;
                total += coins[i][j];
            }
        }
        if (rowCnt != a[i])
            quitf(_wa, "Row %d has %d selected squares, expected %d", i + 1, rowCnt, a[i]);
    }

    for (int j = 0; j < n; j++) {
        int colCnt = 0;
        for (int i = 0; i < n; i++)
            if (grid[i][j] == 'X')
                colCnt++;
        if (colCnt != b[j])
            quitf(_wa, "Column %d has %d selected squares, expected %d", j + 1, colCnt, b[j]);
    }

    if (total != k)
        quitf(_wa, "Claimed maximum %d but selected squares sum to %lld", k, total);

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid optimal selection with %d coins", k);
}
