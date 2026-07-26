#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++)
        a[i] = inf.readInt();
    for (int i = 0; i < n; i++)
        b[i] = inf.readInt();

    string ans_first = ans.readToken();
    string ouf_first = ouf.readToken();

    if (ouf_first == "-1") {
        if (ans_first != "-1")
            quitf(_wa, "Output is -1 but a valid selection exists");
        if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
        quitf(_ok, "Correctly reported impossible");
    }

    if (ans_first == "-1")
        quitf(_wa, "Expected -1 (impossible), but contestant gave a solution");

    vector<string> grid(n);
    grid[0] = ouf_first;
    for (int i = 1; i < n; i++)
        grid[i] = ouf.readToken();

    for (int i = 0; i < n; i++) {
        if ((int)grid[i].size() != n)
            quitf(_wa, "Row %d has length %d, expected %d", i + 1, (int)grid[i].size(), n);
        int rowCnt = 0;
        for (int j = 0; j < n; j++) {
            if (grid[i][j] != 'X' && grid[i][j] != '.')
                quitf(_wa, "Invalid character '%c' at (%d,%d)", grid[i][j], i + 1, j + 1);
            if (grid[i][j] == 'X')
                rowCnt++;
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

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid selection");
}
