#include "testlib.h"
#include <string>
#include <vector>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int expected = 1 << n;
    vector<string> codes;
    set<string> seen;

    for (int i = 0; i < expected; i++) {
        string line = ouf.readToken();
        if ((int)line.size() != n)
            quitf(_wa, "Line %d: expected %d characters, got %d", i + 1, n, (int)line.size());
        for (char c : line) {
            if (c != '0' && c != '1')
                quitf(_wa, "Line %d: invalid character '%c'", i + 1, c);
        }
        if (seen.count(line))
            quitf(_wa, "Duplicate bit string '%s' on line %d", line.c_str(), i + 1);
        seen.insert(line);
        codes.push_back(line);
    }
    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");

    for (int i = 0; i + 1 < expected; i++) {
        int diff = 0;
        for (int j = 0; j < n; j++)
            if (codes[i][j] != codes[i + 1][j])
                diff++;
        if (diff != 1)
            quitf(_wa, "Lines %d and %d differ in %d bits (expected 1)", i + 1, i + 2, diff);
    }

    quitf(_ok, "Valid Gray code of length %d with %d lines", n, expected);
}
