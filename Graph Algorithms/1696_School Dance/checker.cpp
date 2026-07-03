#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = inf.readInt();
    int k = inf.readInt();
    set<pair<int, int>> possiblePairs;
    for (int i = 0; i < k; i++) {
        int a = inf.readInt();
        int b = inf.readInt();
        possiblePairs.insert({a, b});
    }

    int r_ans = ans.readInt();
    int r = ouf.readInt();
    if (r != r_ans)
        quitf(_wa, "Claimed %d pairs but optimal is %d", r, r_ans);
    if (r < 0 || r > min(n, m))
        quitf(_wa, "Number of pairs %d out of range [0,%d]", r, min(n, m));

    set<int> usedBoys, usedGirls;
    set<pair<int, int>> answerPairs;
    for (int i = 0; i < r; i++) {
        int a = ouf.readInt();
        int b = ouf.readInt();
        if (a < 1 || a > n)
            quitf(_wa, "Boy %d out of range [1,%d]", a, n);
        if (b < 1 || b > m)
            quitf(_wa, "Girl %d out of range [1,%d]", b, m);
        if (!possiblePairs.count({a, b}))
            quitf(_wa, "Pair (%d,%d) is not a potential pair", a, b);
        if (usedBoys.count(a))
            quitf(_wa, "Boy %d paired more than once", a);
        if (usedGirls.count(b))
            quitf(_wa, "Girl %d paired more than once", b);
        if (answerPairs.count({a, b}))
            quitf(_wa, "Duplicate pair (%d,%d)", a, b);
        usedBoys.insert(a);
        usedGirls.insert(b);
        answerPairs.insert({a, b});
    }

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid maximum matching of size %d", r);
}
