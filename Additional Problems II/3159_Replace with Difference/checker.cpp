/*
 * Problem:      3159 Replace with Difference
 * Input read:   n; array x[1..n]
 * Validity:     -1 iff impossible; else n-1 operations removing two present values
 *               a,b and inserting |a-b|, leaving exactly 0
 * Optimality:   any valid operation sequence (no scalar from ans)
 * Complexity:   O(n log n)
 */
#include "testlib.h"
#include <vector>
#include <string>
#include <set>
#include <cstdlib>
using namespace std;

static int readFirstOperationValue(const string &t, const char *name) {
    if (t.empty())
        quitf(_wa, "%s is empty", name);

    /*
     * Sentinel -1 is handled before this function is called.
     * Operation values must be plain non-negative integers in [0,1000].
     * Do not accept signs like -5, +5, or bare "-".
     */
    long long v = 0;
    for (char c : t) {
        if (c < '0' || c > '9')
            quitf(_wa, "%s must be an integer in [0,1000], got \"%s\"",
                  name, compress(t).c_str());

        v = v * 10 + (c - '0');
        if (v > 1000)
            quitf(_wa, "%s = %lld is out of range [0,1000]", name, v);
    }

    return (int)v;
}

static void applyOperation(multiset<int> &cur, int a, int b, int op) {
    auto itA = cur.find(a);
    if (itA == cur.end())
        quitf(_wa, "Operation %d: value %d not found in current array", op, a);
    cur.erase(itA);

    auto itB = cur.find(b);
    if (itB == cur.end())
        quitf(_wa, "Operation %d: value %d not found in current array", op, b);
    cur.erase(itB);

    cur.insert(abs(a - b));
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        arr[i] = inf.readInt();

    string ansFirst = ans.readToken();

    if (ansFirst == "-1") {
        string tok = ouf.readToken();
        if (tok != "-1")
            quitf(_wa, "Jury answer is -1 but contestant printed \"%s\"",
                  compress(tok).c_str());

        if (!ouf.seekEof())
            quitf(_wa, "extra information in the output file");

        quitf(_ok, "correctly reported impossible");
    }

    string oufFirst = ouf.readToken();

    if (oufFirst == "-1")
        quitf(_wa, "jury has a valid operation sequence but contestant printed -1");

    multiset<int> cur(arr.begin(), arr.end());

    int a0 = readFirstOperationValue(oufFirst, "a (operation 1)");
    int b0 = ouf.readInt(0, 1000, "b (operation 1)");

    applyOperation(cur, a0, b0, 1);

    for (int op = 2; op <= n - 1; op++) {
        int a = ouf.readInt(0, 1000, format("a (operation %d)", op).c_str());
        int b = ouf.readInt(0, 1000, format("b (operation %d)", op).c_str());

        applyOperation(cur, a, b, op);
    }

    if (cur.size() != 1 || *cur.begin() != 0)
        quitf(_wa, "Final value should be 0, got %d",
              cur.empty() ? -1 : *cur.begin());

    if (!ouf.seekEof())
        quitf(_wa, "extra information in the output file");

    quitf(_ok, "valid sequence of operations");
}