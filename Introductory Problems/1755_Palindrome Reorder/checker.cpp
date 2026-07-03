#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    string s = inf.readToken();
    int n = (int)s.size();

    vector<int> cnt_in(26, 0);
    for (char c : s)
        cnt_in[c - 'A']++;

    string ans_first = ans.readToken();
    if (ans_first == "NO") {
        string ans_second = ans.readToken();
        if (ans_second != "SOLUTION")
            quitf(_fail, "Judge answer malformed: expected NO SOLUTION");

        string ouf_first = ouf.readToken();
        if (ouf_first != "NO")
            quitf(_wa, "No palindrome exists but contestant printed '%s'", ouf_first.c_str());
        string ouf_second = ouf.readToken();
        if (ouf_second != "SOLUTION")
            quitf(_wa, "Expected 'NO SOLUTION' but got 'NO %s'", ouf_second.c_str());
        if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
        quitf(_ok, "Correct: no palindrome possible");
    }

    string ouf_first = ouf.readToken();
    if (ouf_first == "NO")
        quitf(_wa, "A palindrome exists but contestant printed NO SOLUTION");

    string out = ouf_first;
    while (!ouf.readEof())
        out += ouf.readToken();

    if ((int)out.size() != n)
        quitf(_wa, "Output length %d differs from input length %d", (int)out.size(), n);

    vector<int> cnt_out(26, 0);
    for (char c : out) {
        if (c < 'A' || c > 'Z')
            quitf(_wa, "Invalid character '%c' in output", c);
        cnt_out[c - 'A']++;
    }
    for (int i = 0; i < 26; i++) {
        if (cnt_out[i] != cnt_in[i])
            quitf(_wa,
                  "Character '%c' appears %d times in output but %d times in input",
                  (char)('A' + i), cnt_out[i], cnt_in[i]);
    }

    for (int i = 0; i < n / 2; i++) {
        if (out[i] != out[n - 1 - i])
            quitf(_wa,
                  "Output is not a palindrome: position %d='%c' vs %d='%c'",
                  i, out[i], n - 1 - i, out[n - 1 - i]);
    }

    quitf(_ok, "Valid palindrome of length %d", n);
}
