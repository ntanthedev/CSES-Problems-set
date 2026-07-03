#include "testlib.h"
#include <string>
using namespace std;

bool is_subseq(const string& s, const string& t) {
    int j = 0;
    for (int i = 0; i < (int)s.size() && j < (int)t.size(); i++) {
        if (s[i] == t[j]) j++;
    }
    return j == (int)t.size();
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    string s = inf.readToken();
    string ref = ans.readToken();
    string out = ouf.readToken();

    int optimal = (int)ref.size();

    for (char c : out) {
        if (c != 'A' && c != 'C' && c != 'G' && c != 'T')
            quitf(_wa, "Output contains invalid character '%c'", c);
    }

    if (is_subseq(s, out))
        quitf(_wa, "Output is a subsequence of the input string");

    if ((int)out.size() != optimal)
        quitf(_wa, "Shortest absent subsequence has length %d, got %d",
              optimal, (int)out.size());

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid shortest absent subsequence of length %d", optimal);
}
