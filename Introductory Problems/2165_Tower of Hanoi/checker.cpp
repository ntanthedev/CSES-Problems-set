#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int optimal = ans.readInt();

    int k = ouf.readInt();
    if (k != optimal)
        quitf(_wa, "Minimum number of moves is %d, got %d", optimal, k);

    vector<vector<int>> pegs(4);
    for (int d = n; d >= 1; d--)
        pegs[1].push_back(d);

    for (int i = 0; i < k; i++) {
        int a = ouf.readInt();
        int b = ouf.readInt();
        if (a < 1 || a > 3 || b < 1 || b > 3)
            quitf(_wa, "Stack numbers must be between 1 and 3");
        if (a == b)
            quitf(_wa, "Move %d: source and destination are the same", i + 1);
        if (pegs[a].empty())
            quitf(_wa, "Move %d: stack %d is empty", i + 1, a);

        int disk = pegs[a].back();
        if (!pegs[b].empty() && pegs[b].back() < disk)
            quitf(_wa, "Move %d: cannot place disk %d on a smaller disk",
                  i + 1, disk);

        pegs[a].pop_back();
        pegs[b].push_back(disk);
    }

    if ((int)pegs[3].size() != n)
        quitf(_wa, "All disks must end on stack 3");

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid optimal Tower of Hanoi solution");
}
