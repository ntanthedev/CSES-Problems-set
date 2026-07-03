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
    bool ans_impossible = (ans_first == "IMPOSSIBLE");

    string first = ouf.readToken();
    if (first == "IMPOSSIBLE") {
        if (!ans_impossible)
            quitf(_wa, "A valid third permutation exists but contestant printed IMPOSSIBLE");
        if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
        quitf(_ok, "Correct: no valid third permutation");
    }

    if (ans_impossible)
        quitf(_wa, "No valid third permutation exists but contestant printed one");

    vector<int> c(n);
    vector<bool> seen(n + 1, false);
    c[0] = stoi(first);
    if (c[0] < 1 || c[0] > n)
        quitf(_wa, "Value %d out of range [1,%d]", c[0], n);
    seen[c[0]] = true;

    for (int i = 1; i < n; i++) {
        c[i] = ouf.readInt();
        if (c[i] < 1 || c[i] > n)
            quitf(_wa, "Value %d out of range [1,%d]", c[i], n);
        if (seen[c[i]])
            quitf(_wa, "Value %d appears more than once", c[i]);
        seen[c[i]] = true;
    }

    for (int i = 0; i < n; i++) {
        if (c[i] == a[i])
            quitf(_wa, "Position %d: c=%d equals a=%d", i + 1, c[i], a[i]);
        if (c[i] == b[i])
            quitf(_wa, "Position %d: c=%d equals b=%d", i + 1, c[i], b[i]);
    }

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid third permutation");
}
