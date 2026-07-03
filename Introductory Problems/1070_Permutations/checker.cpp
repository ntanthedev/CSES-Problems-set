#include "testlib.h"
#include <cstdlib>
#include <vector>
using namespace std;

static void consume_permutation(int n, InStream& stream) {
    for (int i = 1; i < n; i++)
        stream.readInt();
}

static void check_permutation(int n, const vector<int>& perm) {
    if ((int)perm.size() != n)
        quitf(_wa, "Expected %d numbers, got %d", n, (int)perm.size());

    vector<bool> seen(n + 1, false);
    for (int i = 0; i < n; i++) {
        int x = perm[i];
        if (x < 1 || x > n)
            quitf(_wa, "Value %d out of range [1,%d]", x, n);
        if (seen[x])
            quitf(_wa, "Duplicate value %d", x);
        seen[x] = true;
    }

    for (int i = 0; i + 1 < n; i++) {
        if (abs(perm[i] - perm[i + 1]) == 1)
            quitf(_wa, "Adjacent elements %d and %d differ by 1", perm[i], perm[i + 1]);
    }
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    string ans_first = ans.readToken();
    if (ans_first == "NO") {
        string ans_second = ans.readToken();
        if (ans_second != "SOLUTION")
            quitf(_fail, "Judge answer malformed: expected NO SOLUTION");

        string ouf_first = ouf.readToken();
        if (ouf_first != "NO")
            quitf(_wa, "No beautiful permutation exists but contestant printed '%s'", ouf_first.c_str());
        string ouf_second = ouf.readToken();
        if (ouf_second != "SOLUTION")
            quitf(_wa, "Expected 'NO SOLUTION' but got 'NO %s'", ouf_second.c_str());
        if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
        quitf(_ok, "Correct: no solution for n=%d", n);
    }

    consume_permutation(n, ans);

    string ouf_first = ouf.readToken();
    if (ouf_first == "NO")
        quitf(_wa, "A beautiful permutation exists but contestant printed NO SOLUTION");

    vector<int> perm;
    perm.push_back(atoi(ouf_first.c_str()));
    for (int i = 1; i < n; i++)
        perm.push_back(ouf.readInt());
    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");

    check_permutation(n, perm);
    quitf(_ok, "Valid beautiful permutation of length %d", n);
}
