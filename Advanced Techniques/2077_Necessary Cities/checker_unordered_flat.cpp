// Generic "unordered set of integers" checker.
// Format: first line k, then k integers - order among the k integers does not
// matter. Matches e.g. CSES "Necessary Cities" ("First print an integer k...
// After that, print a list of k cities. You may print the cities in any order.")
//
// This does NOT recompute the answer from the input - it trusts the judge's
// reference answer (N.out / `ans`) is the unique correct set, which is true
// for "Necessary Cities" (articulation-point style problems have exactly one
// correct answer set; only the print ORDER is free).
#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    // Read the jury answer FIRST, so the contestant's k can be bounded by k_ans
    // before anything is allocated from it. Reading k with a 2e9 bound and then
    // sizing a vector with it let a one-line hostile output ("2000000000")
    // commit ~16 GB and stall the checker for ~10 s - a judge-level failure
    // instead of a clean WA. See CHECKER_STRATEGY_V2.md, bug group 5.
    int k_ans = ans.readInt();
    vector<long long> b(k_ans);
    for (int i = 0; i < k_ans; i++) b[i] = ans.readLong();

    int k_out = ouf.readInt(0, k_ans, "k (contestant)");
    if (k_out != k_ans)
        quitf(_wa, "expected %d values, found %d", k_ans, k_out);

    vector<long long> a(k_out);
    for (int i = 0; i < k_out; i++) a[i] = ouf.readLong(-2000000000LL, 2000000000LL, "value");

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    if (a != b)
        quitf(_wa, "the set of %d values does not match the reference set", k_ans);

    quitf(_ok, "%d values, correct set", k_ans);
}
