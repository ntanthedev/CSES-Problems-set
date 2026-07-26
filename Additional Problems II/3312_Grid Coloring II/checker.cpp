/*
 * ============================================================================
 *  CANONICAL TESTLIB CHECKER  (DMOJ/VNOJ "bridged" + "testlib")
 * ============================================================================
 *  HEADER CONTRACT:
 *    Problem:      3312 Grid Coloring II
 *    Input read:    n, m; then n grid rows (each m chars A/B/C) via readToken
 *    Validity:     output is IMPOSSIBLE iff jury says so; else n rows of m chars,
 *                  each in {A,B,C}, each cell differs from input, no equal
 *                  horizontally/vertically adjacent cells
 *    Optimality:   bound only — any valid coloring accepted; IMPOSSIBLE must match ans
 *    Complexity:   O(n*m) time, O(n*m) memory
 * ============================================================================
 */
#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

static bool isAllowed(char c) {
    return c == 'A' || c == 'B' || c == 'C';
}

static void validateColoring(int n, int m, const vector<string>& initial,
                             const vector<string>& out) {
    for (int i = 0; i < n; i++) {
        if ((int)out[i].size() != m)
            quitf(_wa, "output row %d: expected %d characters, got %d",
                  i + 1, m, (int)out[i].size());
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c = out[i][j];
            if (!isAllowed(c))
                quitf(_wa, "row %d col %d: invalid character '%c' (expected A/B/C)",
                      i + 1, j + 1, c);
            if (c == initial[i][j])
                quitf(_wa, "row %d col %d: output '%c' must differ from input '%c'",
                      i + 1, j + 1, c, initial[i][j]);
            if (j + 1 < m && c == out[i][j + 1])
                quitf(_wa, "row %d: adjacent cells (%d,%d) and (%d,%d) have same char '%c'",
                      i + 1, i + 1, j + 1, i + 1, j + 2, c);
            if (i + 1 < n && c == out[i + 1][j])
                quitf(_wa, "col %d: adjacent cells (%d,%d) and (%d,%d) have same char '%c'",
                      j + 1, i + 1, j + 1, i + 2, j + 1, c);
        }
    }
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = inf.readInt();
    vector<string> initial(n);
    for (int i = 0; i < n; i++) {
        initial[i] = inf.readToken();
        if ((int)initial[i].size() != m)
            quitf(_fail, "input grid row %d has wrong length", i + 1);
        for (char c : initial[i]) {
            if (!isAllowed(c))
                quitf(_fail, "input grid row %d contains invalid character '%c'", i + 1, c);
        }
    }

    const string SENT = "IMPOSSIBLE";
    string ansFirst = ans.readToken();
    if (ansFirst == SENT) {
        string tok = ouf.readToken();
        if (tok != SENT)
            quitf(_wa, "jury answer is IMPOSSIBLE but contestant printed \"%s\" "
                       "(claims a solution exists)",
                  compress(tok).c_str());
        if (!ouf.seekEof())
            quitf(_wa, "extra information in the output file");
        quitf(_ok, "correctly reported IMPOSSIBLE");
    }

    for (int i = 1; i < n; i++)
        ans.readToken();

    vector<string> out(n);
    out[0] = ouf.readToken();
    if (out[0] == SENT)
        quitf(_wa, "a valid coloring exists but contestant printed IMPOSSIBLE");
    for (int i = 1; i < n; i++)
        out[i] = ouf.readToken();

    validateColoring(n, m, initial, out);

    if (!ouf.seekEof())
        quitf(_wa, "extra information in the output file");
    quitf(_ok, "valid 3-coloring of %dx%d grid", n, m);
}
