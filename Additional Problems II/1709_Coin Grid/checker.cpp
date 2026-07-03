#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    vector<string> grid(n);
    for (int i = 0; i < n; i++)
        grid[i] = inf.readToken();

    int k_ans = ans.readInt();
    int k = ouf.readInt();
    if (k != k_ans)
        quitf(_wa, "Minimum number of moves is %d, got %d", k_ans, k);
    if (k < 0)
        quitf(_wa, "Number of moves must be non-negative, got %d", k);

    vector<vector<bool>> removed(n, vector<bool>(n, false));
    for (int move = 0; move < k; move++) {
        int type = ouf.readInt();
        int idx = ouf.readInt();
        if (type != 1 && type != 2)
            quitf(_wa, "Move %d: type must be 1 (row) or 2 (column), got %d", move + 1, type);
        if (idx < 1 || idx > n)
            quitf(_wa, "Move %d: index out of bounds [1,%d], got %d", move + 1, n, idx);
        idx--;

        if (type == 1) {
            for (int j = 0; j < n; j++) removed[idx][j] = true;
        } else {
            for (int i = 0; i < n; i++) removed[i][idx] = true;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 'o' && !removed[i][j])
                quitf(_wa, "Coin at row %d, column %d not removed", i + 1, j + 1);
        }
    }

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "All coins removed in optimal %d moves", k);
}
