#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = inf.readInt();
    vector<string> grid(n);
    pair<int, int> start, target;
    for (int i = 0; i < n; i++) {
        grid[i] = inf.readLine();
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'A') start = {i, j};
            if (grid[i][j] == 'B') target = {i, j};
        }
    }

    string ansFlag = ans.readToken();
    if (ansFlag != "YES" && ansFlag != "NO")
        quitf(_fail, "Invalid judge answer token '%s'", ansFlag.c_str());

    string outFlag = ouf.readToken();
    if (outFlag != "YES" && outFlag != "NO")
        quitf(_wa, "Expected YES or NO, got '%s'", outFlag.c_str());

    if (outFlag == "NO") {
        if (ansFlag != "NO")
            quitf(_wa, "Output is NO but a path exists");
        if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
        quitf(_ok, "Correct: no path");
    }

    if (ansFlag == "NO")
        quitf(_wa, "A path exists but output is NO");

    int minLen = ans.readInt();
    int len = ouf.readInt();
    string path = ouf.readToken();

    if ((int)path.size() != len)
        quitf(_wa, "Path length %d does not match string length %d", len, (int)path.size());
    if (len != minLen)
        quitf(_wa, "Path length %d is not shortest (optimal is %d)", len, minLen);

    int r = start.first, c = start.second;
    for (char ch : path) {
        if (ch == 'L') c--;
        else if (ch == 'R') c++;
        else if (ch == 'U') r--;
        else if (ch == 'D') r++;
        else quitf(_wa, "Invalid direction '%c'", ch);

        if (r < 0 || r >= n || c < 0 || c >= m)
            quitf(_wa, "Path goes out of bounds at step with '%c'", ch);
        if (grid[r][c] == '#')
            quitf(_wa, "Path walks into a wall at (%d,%d)", r + 1, c + 1);
    }

    if (r != target.first || c != target.second)
        quitf(_wa, "Path ends at (%d,%d) instead of target (%d,%d)",
              r + 1, c + 1, target.first + 1, target.second + 1);

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid shortest path of length %d", len);
}
