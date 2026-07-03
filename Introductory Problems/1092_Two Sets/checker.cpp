#include "testlib.h"
#include <set>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    string ans_token = ans.readToken();
    string ouf_token = ouf.readToken();

    if (ans_token == "NO") {
        if (ouf_token != "NO")
            quitf(_wa, "No partition exists but contestant printed '%s'", ouf_token.c_str());
        if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
        quitf(_ok, "Correct: no partition");
    }

    if (ouf_token == "NO")
        quitf(_wa, "A partition exists but contestant printed NO");
    if (ouf_token != "YES")
        quitf(_wa, "Expected YES or NO, got '%s'", ouf_token.c_str());

    int k1 = ouf.readInt();
    if (k1 < 0 || k1 > n)
        quitf(_wa, "First set size %d out of range [0,%d]", k1, n);

    vector<int> set1(k1);
    long long sum1 = 0;
    for (int i = 0; i < k1; i++) {
        set1[i] = ouf.readInt();
        if (set1[i] < 1 || set1[i] > n)
            quitf(_wa, "Value %d out of range [1,%d]", set1[i], n);
        sum1 += set1[i];
    }

    int k2 = ouf.readInt();
    if (k1 + k2 != n)
        quitf(_wa, "Set sizes %d + %d != n=%d", k1, k2, n);

    long long sum2 = 0;
    for (int i = 0; i < k2; i++) {
        int x = ouf.readInt();
        if (x < 1 || x > n)
            quitf(_wa, "Value %d out of range [1,%d]", x, n);
        sum2 += x;
        set1.push_back(x);
    }
    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");

    set<int> seen;
    for (int x : set1) {
        if (seen.count(x))
            quitf(_wa, "Value %d appears more than once", x);
        seen.insert(x);
    }
    if ((int)seen.size() != n)
        quitf(_wa, "Output does not use each number 1..%d exactly once", n);

    if (sum1 != sum2)
        quitf(_wa, "Set sums differ: %lld vs %lld", sum1, sum2);

    quitf(_ok, "Valid partition of 1..%d", n);
}
