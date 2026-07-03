#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int t = inf.readInt();
    for (int tc = 1; tc <= t; tc++) {
        long long n = inf.readLong();
        long long a = ouf.readLong();
        long long b = ouf.readLong();
        long long c = ouf.readLong();
        long long d = ouf.readLong();

        if (a < 0 || b < 0 || c < 0 || d < 0)
            quitf(_wa, "Test %d: all four numbers must be non-negative", tc);
        long long sum = a * a + b * b + c * c + d * d;
        if (sum != n)
            quitf(_wa, "Test %d: %lld^2 + %lld^2 + %lld^2 + %lld^2 = %lld, expected %lld",
                  tc, a, b, c, d, sum, n);
    }

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid representation for all %d test cases", t);
}
