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
            quitf(_wa, "No valid pair exists but contestant printed '%s'", ouf_first.c_str());
        if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
        quitf(_ok, "Correct: no pair");
    }

    if (ouf_first == "IMPOSSIBLE")
        quitf(_wa, "A valid pair exists but contestant printed IMPOSSIBLE");

    int i = stoi(ouf_first);
    int j = ouf.readInt();
    ouf.readEoln();
    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");

    if (i < 1 || i > n)
        quitf(_wa, "First position %d out of range [1,%d]", i, n);
    if (j < 1 || j > n)
        quitf(_wa, "Second position %d out of range [1,%d]", j, n);
    if (i == j)
        quitf(_wa, "Positions must be distinct, got %d and %d", i, j);
    if ((long long)a[i - 1] + a[j - 1] != x)
        quitf(_wa, "Values at positions %d and %d sum to %lld, expected %d",
              i, j, (long long)a[i - 1] + a[j - 1], x);

    quitf(_ok, "Valid pair (%d, %d)", i, j);
}
