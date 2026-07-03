#include "testlib.h"
#include <vector>
using namespace std;

bool is_subseq(const vector<int>& arr, const vector<int>& sub) {
    int j = 0;
    for (int i = 0; i < (int)arr.size() && j < (int)sub.size(); i++) {
        if (arr[i] == sub[j]) j++;
    }
    return j == (int)sub.size();
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = inf.readInt();
    vector<int> a(n), b(m);
    for (int i = 0; i < n; i++) a[i] = inf.readInt();
    for (int i = 0; i < m; i++) b[i] = inf.readInt();

    int optimal = ans.readInt();
    int k = ouf.readInt();

    if (k != optimal)
        quitf(_wa, "Longest common subsequence has length %d, got %d", optimal, k);

    vector<int> sub(k);
    for (int i = 0; i < k; i++)
        sub[i] = ouf.readInt();

    if (!is_subseq(a, sub))
        quitf(_wa, "Output is not a subsequence of the first array");

    if (!is_subseq(b, sub))
        quitf(_wa, "Output is not a subsequence of the second array");

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid longest common subsequence of length %d", k);
}
