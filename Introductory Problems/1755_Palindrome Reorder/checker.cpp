/*
 * HEADER CONTRACT
 * Problem:      1755 Palindrome Reorder
 * Input read:   string s of length n (letters A-Z)
 * Validity:     NO SOLUTION iff no palindrome reordering exists; else print a string of
 *               length n using exactly the same multiset of letters as s, reading the
 *               same forwards and backwards.
 * Optimality:   none (any valid palindrome accepted)
 * Complexity:   O(n) time and memory — frequency counts over 26 letters
 */
#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    string s = inf.readToken();
    int n = (int)s.size();

    vector<int> cntIn(26, 0);
    for (char c : s) {
        if (c < 'A' || c > 'Z')
            quitf(_fail, "jury input has invalid character '%c'", c);
        cntIn[c - 'A']++;
    }

    string ansTok = ans.readToken();
    if (ansTok == "NO") {
        string ansSecond = ans.readToken();
        if (ansSecond != "SOLUTION")
            quitf(_fail, "judge answer malformed: expected NO SOLUTION");

        string oufFirst = ouf.readToken();
        if (oufFirst != "NO")
            quitf(_wa, "jury answer is NO SOLUTION but contestant printed \"%s\"",
                  compress(oufFirst).c_str());
        string oufSecond = ouf.readToken();
        if (oufSecond != "SOLUTION")
            quitf(_wa, "contestant printed \"NO %s\" but expected NO SOLUTION",
                  compress(oufSecond).c_str());
        if (!ouf.seekEof())
            quitf(_wa, "extra information in the output file");
        quitf(_ok, "correctly reported NO SOLUTION");
    }

    string oufTok = ouf.readToken();
    if (oufTok == "NO")
        quitf(_wa, "a palindrome exists but contestant printed NO SOLUTION");

    if ((int)oufTok.size() != n)
        quitf(_wa, "output length %d differs from input length %d", (int)oufTok.size(), n);

    vector<int> cntOut(26, 0);
    for (char c : oufTok) {
        if (c < 'A' || c > 'Z')
            quitf(_wa, "invalid character '%c' in output", c);
        cntOut[c - 'A']++;
    }
    for (int i = 0; i < 26; i++) {
        if (cntOut[i] != cntIn[i])
            quitf(_wa, "character '%c' appears %d times in output but %d times in input",
                  (char)('A' + i), cntOut[i], cntIn[i]);
    }

    for (int i = 0; i < n / 2; i++) {
        if (oufTok[i] != oufTok[n - 1 - i])
            quitf(_wa, "output is not a palindrome: position %d='%c' vs %d='%c'",
                  i + 1, oufTok[i], n - i, oufTok[n - 1 - i]);
    }

    if (!ouf.seekEof())
        quitf(_wa, "extra information in the output file");
    quitf(_ok, "valid palindrome of length %d", n);
}
