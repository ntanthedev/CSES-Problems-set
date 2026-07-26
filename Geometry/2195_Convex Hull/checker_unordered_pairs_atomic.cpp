// Generic "unordered set of ATOMIC pairs" checker - for problems whose output
// is k lines, each a pair "x y" that must NOT be swapped (unlike an edge, a
// point (x,y) is not the same as (y,x)), but the k lines may be printed in
// any order. Matches CSES "Convex Hull" ("... print k lines that describe the
// points. You can print the points in any order.").
#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

typedef pair<long long, long long> pll;

static pll read_point(InStream &s) {
    long long x = s.readLong(-2000000000LL, 2000000000LL, "x");
    long long y = s.readLong(-2000000000LL, 2000000000LL, "y");
    return pll(x, y);   // NOT canonicalised - (x,y) != (y,x) here
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    // Read the jury answer FIRST, so the contestant's k can be bounded by k_ans
    // before anything is allocated from it. Reading k with a 2e9 bound and then
    // sizing a vector with it let a one-line hostile output ("2000000000")
    // commit tens of GB and stall the checker - a judge-level failure instead
    // of a clean WA. See CHECKER_STRATEGY_V2.md, bug group 5.
    int k_ans = ans.readInt();
    vector<pll> b(k_ans);
    for (int i = 0; i < k_ans; i++) b[i] = read_point(ans);

    int k_out = ouf.readInt(0, k_ans, "k (contestant)");
    if (k_out != k_ans)
        quitf(_wa, "expected %d points, found %d", k_ans, k_out);

    vector<pll> a(k_out);
    for (int i = 0; i < k_out; i++) a[i] = read_point(ouf);

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    if (a != b)
        quitf(_wa, "the set of %d points does not match the reference set", k_ans);

    quitf(_ok, "%d points, correct set", k_ans);
}
