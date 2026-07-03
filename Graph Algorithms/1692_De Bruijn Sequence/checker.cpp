#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    string ref = ans.readToken();
    string s = ouf.readToken();

    int expectedLen = (int)ref.size();
    if ((int)s.size() != expectedLen)
        quitf(_wa, "String length is %d, expected %d", (int)s.size(), expectedLen);

    for (char c : s) {
        if (c != '0' && c != '1')
            quitf(_wa, "Invalid character '%c', expected only 0 or 1", c);
    }

    int total = 1 << n;
    vector<bool> seen(total, false);
    int mask = total - 1;
    int val = 0;
    for (int i = 0; i < n - 1; i++)
        val = ((val << 1) | (s[i] - '0')) & mask;

    for (int i = n - 1; i < expectedLen; i++) {
        val = ((val << 1) | (s[i] - '0')) & mask;
        if (seen[val])
            quitf(_wa, "Substring appears more than once");
        seen[val] = true;
    }

    for (int i = 0; i < total; i++) {
        if (!seen[i])
            quitf(_wa, "Not all substrings of length %d appear", n);
    }

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid De Bruijn sequence of order %d", n);
}
