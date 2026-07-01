// Generic "unordered set of unordered pairs" checker - for problems whose
// output is k lines, each an edge "a b" where (a,b) and (b,a) are the SAME
// edge, and the k lines may be printed in any order. Matches e.g. CSES
// "Necessary Roads" and "Pruefer Code" ("... print k lines that describe the
// roads/edges. You can print the roads/edges in any order.").
//
// Each pair is canonicalised to (min, max) before comparison, since an edge
// a-b is identical to b-a - this is the exact detail a naive "sort all
// whitespace tokens" checker gets wrong (it would accept a submission that
// has the right 2k numbers but paired into the WRONG, nonexistent edges).
#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

typedef pair<long long, long long> pll;

static pll read_edge(InStream &s) {
    long long a = s.readLong(0, 2000000000LL, "a");
    long long b = s.readLong(0, 2000000000LL, "b");
    if (a > b) swap(a, b);
    return pll(a, b);
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int k_out = ouf.readInt(0, 2000000000, "k (contestant)");
    vector<pll> a(k_out);
    for (int i = 0; i < k_out; i++) a[i] = read_edge(ouf);

    int k_ans = ans.readInt();
    vector<pll> b(k_ans);
    for (int i = 0; i < k_ans; i++) b[i] = read_edge(ans);

    if (k_out != k_ans)
        quitf(_wa, "expected %d edges, found %d", k_ans, k_out);

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    if (a != b)
        quitf(_wa, "the set of %d edges does not match the reference set", k_ans);

    quitf(_ok, "%d edges, correct set", k_ans);
}
