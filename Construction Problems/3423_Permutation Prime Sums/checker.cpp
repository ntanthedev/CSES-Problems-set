#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

static bool is_prime(int x) {
    if (x < 2) return false;
    if (x == 2) return true;
    if (x % 2 == 0) return false;
    for (int d = 3; d * d <= x; d += 2) {
        if (x % d == 0) return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    string ans_first = ans.readToken();
    bool ans_impossible = (ans_first == "IMPOSSIBLE");

    string first = ouf.readToken();
    if (first == "IMPOSSIBLE") {
        if (!ans_impossible)
            quitf(_wa, "A solution exists for n=%d but contestant printed IMPOSSIBLE", n);
        if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
        quitf(_ok, "Correct: no solution");
    }

    if (ans_impossible)
        quitf(_wa, "No solution exists but contestant printed permutations");

    vector<int> a(n), b(n);
    vector<bool> seen_a(n + 1, false), seen_b(n + 1, false);

    a[0] = stoi(first);
    if (a[0] < 1 || a[0] > n)
        quitf(_wa, "Value %d out of range [1,%d]", a[0], n);
    seen_a[a[0]] = true;

    for (int i = 1; i < n; i++) {
        a[i] = ouf.readInt();
        if (a[i] < 1 || a[i] > n)
            quitf(_wa, "Value %d out of range [1,%d]", a[i], n);
        if (seen_a[a[i]])
            quitf(_wa, "Value %d appears more than once in first permutation", a[i]);
        seen_a[a[i]] = true;
    }

    for (int i = 0; i < n; i++) {
        b[i] = ouf.readInt();
        if (b[i] < 1 || b[i] > n)
            quitf(_wa, "Value %d out of range [1,%d]", b[i], n);
        if (seen_b[b[i]])
            quitf(_wa, "Value %d appears more than once in second permutation", b[i]);
        seen_b[b[i]] = true;
    }

    for (int i = 0; i < n; i++) {
        int sum = a[i] + b[i];
        if (!is_prime(sum))
            quitf(_wa, "a[%d]+b[%d] = %d+%d = %d is not prime",
                  i + 1, i + 1, a[i], b[i], sum);
    }

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid prime-sum permutations");
}
