/*

* Problem:      3355 Sum of Four Squares
* Input read:   t; n for each test case
* Validity:     For each test, output four non-negative integers a,b,c,d such that
* ```
            a^2 + b^2 + c^2 + d^2 = n
* Optimality:   Any valid representation is accepted
* Complexity:   O(t) time, O(1) memory
  */
  #include "testlib.h"
  #include <bits/stdc++.h>
  using namespace std;

int main(int argc, char* argv[]) {
registerTestlibCmd(argc, argv);

int t = inf.readInt();

for (int tc = 1; tc <= t; tc++) {
    long long n = inf.readLong();

    long long a = ouf.readLong(0LL, 10000000LL, format("test %d: a", tc).c_str());
    long long b = ouf.readLong(0LL, 10000000LL, format("test %d: b", tc).c_str());
    long long c = ouf.readLong(0LL, 10000000LL, format("test %d: c", tc).c_str());
    long long d = ouf.readLong(0LL, 10000000LL, format("test %d: d", tc).c_str());

    __int128 sum = 0;
    sum += (__int128)a * a;
    sum += (__int128)b * b;
    sum += (__int128)c * c;
    sum += (__int128)d * d;

    if (sum != (__int128)n) {
        quitf(_wa,
              "test %d: %lld^2 + %lld^2 + %lld^2 + %lld^2 = %lld, expected %lld",
              tc, a, b, c, d, (long long)sum, n);
    }
}

if (!ouf.seekEof())
    quitf(_wa, "extra information in the output file");

quitf(_ok, "valid representations for all %d test cases", t);

}
