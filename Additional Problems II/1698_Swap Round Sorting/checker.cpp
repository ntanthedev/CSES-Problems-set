#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    vector<int> perm(n + 1);
    for (int i = 1; i <= n; i++)
        perm[i] = inf.readInt();

    int k_ans = ans.readInt();
    int k = ouf.readInt();
    if (k != k_ans)
        quitf(_wa, "Minimum rounds is %d, got %d", k_ans, k);
    if (k < 0)
        quitf(_wa, "Number of rounds must be non-negative, got %d", k);

    vector<int> cur = perm;
    for (int round = 0; round < k; round++) {
        int cnt = ouf.readInt();
        if (cnt < 0)
            quitf(_wa, "Round %d: number of swaps must be non-negative, got %d", round + 1, cnt);

        vector<bool> used(n + 1, false);
        for (int s = 0; s < cnt; s++) {
            int i = ouf.readInt();
            int j = ouf.readInt();
            if (i < 1 || i > n)
                quitf(_wa, "Round %d swap %d: index i=%d out of bounds", round + 1, s + 1, i);
            if (j < 1 || j > n)
                quitf(_wa, "Round %d swap %d: index j=%d out of bounds", round + 1, s + 1, j);
            if (i == j)
                quitf(_wa, "Round %d swap %d: cannot swap same index", round + 1, s + 1);
            if (used[i] || used[j])
                quitf(_wa, "Round %d swap %d: index %d or %d already used in this round",
                      round + 1, s + 1, i, j);
            used[i] = used[j] = true;
            swap(cur[i], cur[j]);
        }
    }

    for (int i = 1; i <= n; i++) {
        if (cur[i] != i)
            quitf(_wa, "After all rounds, position %d has value %d, expected %d", i, cur[i], i);
    }

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid optimal sorting with %d rounds", k);
}
