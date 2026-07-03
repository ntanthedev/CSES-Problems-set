#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

struct Clause {
    char sign1, sign2;
    int x1, x2;
};

static bool wish_satisfied(char sign, int x, const vector<char>& assign) {
    return assign[x] == sign;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = inf.readInt();
    vector<Clause> clauses(n);
    for (int i = 0; i < n; i++) {
        string s1 = inf.readToken();
        int x1 = inf.readInt();
        string s2 = inf.readToken();
        int x2 = inf.readInt();
        if (s1 != "+" && s1 != "-")
            quitf(_wa, "Invalid wish sign '%s'", s1.c_str());
        if (s2 != "+" && s2 != "-")
            quitf(_wa, "Invalid wish sign '%s'", s2.c_str());
        if (x1 < 1 || x1 > m)
            quitf(_wa, "Topping %d out of range [1,%d]", x1, m);
        if (x2 < 1 || x2 > m)
            quitf(_wa, "Topping %d out of range [1,%d]", x2, m);

        clauses[i] = {s1[0], s2[0], x1, x2};
    }

    string ans_first = ans.readToken();
    bool ans_impossible = (ans_first == "IMPOSSIBLE");

    string first = ouf.readToken();
    if (first == "IMPOSSIBLE") {
        if (!ans_impossible)
            quitf(_wa, "A satisfying assignment exists but contestant printed IMPOSSIBLE");
        if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
        quitf(_ok, "Correct: no satisfying assignment");
    }

    if (ans_impossible)
        quitf(_wa, "No satisfying assignment exists but contestant gave an assignment");

    vector<char> assign(m + 1);
    if (first.size() != 1 || (first[0] != '+' && first[0] != '-'))
        quitf(_wa, "Expected + or - for topping 1, got '%s'", first.c_str());
    assign[1] = first[0];
    for (int i = 2; i <= m; i++) {
        string tok = ouf.readToken();
        if (tok.size() != 1 || (tok[0] != '+' && tok[0] != '-'))
            quitf(_wa, "Expected + or - for topping %d, got '%s'", i, tok.c_str());
        assign[i] = tok[0];
    }
    if (!ouf.readEof())
        quitf(_pe, "Extra output after %d topping symbols", m);

    for (int i = 0; i < n; i++) {
        const Clause& c = clauses[i];
        bool ok = wish_satisfied(c.sign1, c.x1, assign)
               || wish_satisfied(c.sign2, c.x2, assign);
        if (!ok)
            quitf(_wa, "Wish %d (%c%d %c%d) not satisfied",
                  i + 1, c.sign1, c.x1, c.sign2, c.x2);
    }

    quitf(_ok, "Valid assignment for %d toppings", m);
}
