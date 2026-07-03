#include "testlib.h"
#include <string>
using namespace std;

int count_occurrences(const string& s, const string& t) {
    if (t.empty()) return 0;
    int cnt = 0, pos = 0;
    while (true) {
        pos = (int)s.find(t, pos);
        if (pos == (int)string::npos) break;
        cnt++;
        pos++;
    }
    return cnt;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    string s = inf.readToken();
    string ref = ans.readLine();
    string out = ouf.readLine();

    if (ref == "-1") {
        if (out != "-1")
            quitf(_wa, "No repeating substring exists but output is not -1");
        if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
        quitf(_ok, "Correct: no repeating substring");
    }

    if (out == "-1")
        quitf(_wa, "A repeating substring exists but output is -1");

    int optimal = (int)ref.size();

    for (char c : out) {
        if (c < 'a' || c > 'z')
            quitf(_wa, "Output contains invalid character '%c'", c);
    }

    if (out.empty())
        quitf(_wa, "Repeating substring must be non-empty");

    if (s.find(out) == string::npos)
        quitf(_wa, "Output is not a substring of the input");

    if (count_occurrences(s, out) < 2)
        quitf(_wa, "Substring occurs fewer than two times");

    if ((int)out.size() != optimal)
        quitf(_wa, "Longest repeating substring has length %d, got %d",
              optimal, (int)out.size());

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid longest repeating substring of length %d", optimal);
}
