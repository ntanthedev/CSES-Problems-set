#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = n * (n - 1) / 2;

    vector<ll> inputB(m);
    for (int i = 0; i < m; i++)
        inputB[i] = inf.readLong();
    sort(inputB.begin(), inputB.end());

    vector<ll> A(n);
    for (int i = 0; i < n; i++)
        A[i] = ouf.readLong();

    vector<ll> computedB;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++)
            computedB.push_back(A[i] + A[j]);
    }
    sort(computedB.begin(), computedB.end());

    if (inputB != computedB)
        quitf(_wa, "The pairwise sums of the output do not match the input list B");

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid reconstruction");
}
