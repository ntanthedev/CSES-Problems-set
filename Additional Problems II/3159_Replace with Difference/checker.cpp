#include "testlib.h"
#include <vector>
#include <string>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        arr[i] = inf.readInt();

    string ans_first = ans.readToken();
    bool solvable = (ans_first != "-1");

    string first = ouf.readToken();
    if (first == "-1") {
        if (solvable)
            quitf(_wa, "Output is -1 but a valid sequence exists");
        if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
        quitf(_ok, "Correctly reported impossible");
    }

    if (!solvable)
        quitf(_wa, "No solution exists but output is not -1");

    multiset<int> cur(arr.begin(), arr.end());
    int a = stoi(first);
    int b = ouf.readInt();

    for (int op = 0; op < n - 1; op++) {
        if (op > 0) {
            a = ouf.readInt();
            b = ouf.readInt();
        }

        auto itA = cur.find(a);
        if (itA == cur.end())
            quitf(_wa, "Operation %d: value %d not found in current array", op + 1, a);
        cur.erase(itA);

        auto itB = cur.find(b);
        if (itB == cur.end())
            quitf(_wa, "Operation %d: value %d not found in current array", op + 1, b);
        cur.erase(itB);

        cur.insert(abs(a - b));
    }

    if (cur.size() != 1 || *cur.begin() != 0)
        quitf(_wa, "Final value should be 0, got %d", cur.empty() ? -1 : *cur.begin());

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid sequence of operations");
}
