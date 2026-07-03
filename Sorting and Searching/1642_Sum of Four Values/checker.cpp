#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int x = inf.readInt();
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        a[i] = inf.readInt();
    string ans_first = ans.readToken();
    string ouf_first = ouf.readToken();

    if (ans_first == "IMPOSSIBLE") {
        if (ouf_first != "IMPOSSIBLE")
            quitf(_wa, "No valid quadruple exists but contestant printed '%s'", ouf_first.c_str());
        if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
        quitf(_ok, "Correct: no quadruple");
    }

    if (ouf_first == "IMPOSSIBLE")
        quitf(_wa, "A valid quadruple exists but contestant printed IMPOSSIBLE");

    int i = stoi(ouf_first);
    int j = ouf.readInt();
    int k = ouf.readInt();
    int l = ouf.readInt();
    ouf.readEoln();
    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");

    if (i < 1 || i > n)
        quitf(_wa, "Position %d out of range [1,%d]", i, n);
    if (j < 1 || j > n)
        quitf(_wa, "Position %d out of range [1,%d]", j, n);
    if (k < 1 || k > n)
        quitf(_wa, "Position %d out of range [1,%d]", k, n);
    if (l < 1 || l > n)
        quitf(_wa, "Position %d out of range [1,%d]", l, n);
    if (i == j || i == k || i == l || j == k || j == l || k == l)
        quitf(_wa, "Positions must be distinct, got %d %d %d %d", i, j, k, l);
    if ((long long)a[i - 1] + a[j - 1] + a[k - 1] + a[l - 1] != x)
        quitf(_wa, "Values at positions %d,%d,%d,%d sum to %lld, expected %d",
              i, j, k, l, (long long)a[i - 1] + a[j - 1] + a[k - 1] + a[l - 1], x);

    quitf(_ok, "Valid quadruple (%d, %d, %d, %d)", i, j, k, l);
}
