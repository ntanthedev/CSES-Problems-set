/*
 * HEADER CONTRACT
 * Problem:      1684 Giant Pizza
 * Input read:   n, m; n lines of two wishes (+x or -x), x in [1,m]
 * Validity:     IMPOSSIBLE if unsatisfiable; else m symbols '+'/'-',
 *               each person has at least one wish satisfied
 * Optimality:   any satisfying assignment (no scalar from ans)
 * Complexity:   O(n + m) time, O(n + m) memory
 */
#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct Clause {
    char sign1, sign2;
    int x1, x2;
};

static bool wishSatisfied(char sign, int x, const vector<char> &assign) {
    return assign[x] == sign;
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = inf.readInt();
    vector<Clause> clauses(n);
    for (int i = 0; i < n; i++) {
        string s1 = inf.readToken();
        int x1 = inf.readInt();
        string s2 = inf.readToken();
        int x2 = inf.readInt();
        clauses[i] = {s1[0], s2[0], x1, x2};
    }

    string ansTok = ans.readToken();
    if (ansTok == "IMPOSSIBLE") {
        string oufTok = ouf.readToken();
        if (oufTok != "IMPOSSIBLE")
            quitf(_wa, "jury answer is IMPOSSIBLE but contestant printed \"%s\" "
                       "(claims a satisfying topping assignment exists)",
                  compress(oufTok).c_str());
        if (!ouf.seekEof())
            quitf(_wa, "extra information in the output file");
        quitf(_ok, "correctly reported IMPOSSIBLE");
    }

    vector<char> assign(m + 1);
    string tok = ouf.readToken();
    if (tok.size() != 1 || (tok[0] != '+' && tok[0] != '-'))
        quitf(_wa, "expected '+' or '-' for topping 1, contestant printed \"%s\"",
              compress(tok).c_str());
    assign[1] = tok[0];
    for (int i = 2; i <= m; i++) {
        tok = ouf.readToken();
        if (tok.size() != 1 || (tok[0] != '+' && tok[0] != '-'))
            quitf(_wa, "expected '+' or '-' for topping %d, contestant printed \"%s\"",
                  i, compress(tok).c_str());
        assign[i] = tok[0];
    }

    for (int i = 0; i < n; i++) {
        const Clause &c = clauses[i];
        bool ok = wishSatisfied(c.sign1, c.x1, assign)
               || wishSatisfied(c.sign2, c.x2, assign);
        if (!ok)
            quitf(_wa, "wish of family member %d (%c%d or %c%d) is not satisfied",
                  i + 1, c.sign1, c.x1, c.sign2, c.x2);
    }

    if (!ouf.seekEof())
        quitf(_wa, "extra information in the output file");
    quitf(_ok, "valid assignment for %d toppings", m);
}
