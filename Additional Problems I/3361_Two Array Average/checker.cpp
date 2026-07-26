/*

* Problem:      3361 Two Array Average
* Input read:   n; arrays a[1..n], b[1..n]
* Validity:     Output two prefix sizes x,y in [1,n]
* Optimality:   Average of chosen prefixes must match the optimum average derived from ans
* ```
            within absolute or relative error 1e-6
* Complexity:   O(n) time, O(n) memory
  */
  #include "testlib.h"
  #include <bits/stdc++.h>
  using namespace std;

static long double average_of(const vector<long long>& pa, const vector<long long>& pb, int x, int y) {
return ((long double)pa[x] + (long double)pb[y]) / (long double)(x + y);
}

int main(int argc, char* argv[]) {
registerTestlibCmd(argc, argv);

int n = inf.readInt();

vector<long long> pa(n + 1, 0), pb(n + 1, 0);

for (int i = 1; i <= n; i++) {
    long long x = inf.readLong();
    pa[i] = pa[i - 1] + x;
}

for (int i = 1; i <= n; i++) {
    long long x = inf.readLong();
    pb[i] = pb[i - 1] + x;
}

int ansX = ans.readInt();
int ansY = ans.readInt();

if (ansX < 1 || ansX > n || ansY < 1 || ansY > n) {
    quitf(_fail, "jury answer has invalid prefix sizes %d %d for n = %d", ansX, ansY, n);
}

long double opt = average_of(pa, pb, ansX, ansY);

int outX = ouf.readInt(1, n, "first prefix size");
int outY = ouf.readInt(1, n, "second prefix size");

long double got = average_of(pa, pb, outX, outY);
long double diff = fabsl(got - opt);
long double relBase = max((long double)1.0, fabsl(opt));
const long double EPS = 1e-6L;

if (!(diff <= EPS || diff <= EPS * relBase)) {
    quitf(_wa,
          "chosen prefixes have average %.12Lf, but optimum is %.12Lf; absolute difference %.12Lf exceeds tolerance",
          got, opt, diff);
}

if (!ouf.seekEof())
    quitf(_wa, "extra information in the output file");

quitf(_ok, "valid prefixes %d and %d with average %.12Lf", outX, outY, got);

}
