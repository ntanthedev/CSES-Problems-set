#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

static void consume_grid(int n, InStream& stream) {
    for (int i = 1; i < n; i++)
        stream.readToken();
}

static void validate_coloring(int n, int m, const vector<string>& initial, const vector<string>& out) {
    for (int i = 0; i < n; i++) {
        if ((int)out[i].size() != m)
            quitf(_wa, "Output row %d: expected %d chars, got %d", i + 1, m, (int)out[i].size());
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c = out[i][j];
            if (c != 'A' && c != 'B' && c != 'C')
                quitf(_wa, "Row %d col %d: invalid char '%c' (expected A/B/C)", i + 1, j + 1, c);
            if (c == initial[i][j])
                quitf(_wa, "Row %d col %d: output '%c' must differ from input '%c'",
                      i + 1, j + 1, c, initial[i][j]);
            if (j + 1 < m && c == out[i][j + 1])
                quitf(_wa, "Row %d: adjacent cells (%d,%d) and (%d,%d) have same char '%c'",
                      i + 1, i + 1, j + 1, i + 1, j + 2, c);
            if (i + 1 < n && c == out[i + 1][j])
                quitf(_wa, "Col %d: adjacent cells (%d,%d) and (%d,%d) have same char '%c'",
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
        initial[i] = inf.readLine();
        if ((int)initial[i].size() != m)
            quitf(_fail, "Input grid row %d has wrong length", i + 1);
    }

    string ans_first = ans.readToken();
    string ouf_first = ouf.readToken();

    if (ans_first == "IMPOSSIBLE") {
        if (ouf_first != "IMPOSSIBLE")
            quitf(_wa, "No valid coloring exists but contestant printed '%s'", ouf_first.c_str());
        if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
        quitf(_ok, "Correct: impossible");
    }

    if (ouf_first == "IMPOSSIBLE")
        quitf(_wa, "A valid coloring exists but contestant printed IMPOSSIBLE");

    consume_grid(n, ans);

    vector<string> out(n);
    out[0] = ouf_first;
    for (int i = 1; i < n; i++)
        out[i] = ouf.readWord();

    validate_coloring(n, m, initial, out);
    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid 3-coloring of %dx%d grid", n, m);
}
