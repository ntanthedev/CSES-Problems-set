#include "testlib.h"
#include <string>
using namespace std;

bool is_palindrome(const string& t) {
    int l = 0, r = (int)t.size() - 1;
    while (l < r) {
        if (t[l] != t[r]) return false;
        l++;
        r--;
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    string s = inf.readToken();
    string ref = ans.readToken();
    string out = ouf.readToken();

    int optimal = (int)ref.size();

    for (char c : out) {
        if (c < 'a' || c > 'z')
            quitf(_wa, "Output contains invalid character '%c'", c);
    }

    if (out.empty())
        quitf(_wa, "Output must be non-empty");

    if (!is_palindrome(out))
        quitf(_wa, "Output is not a palindrome");

    if (s.find(out) == string::npos)
        quitf(_wa, "Output is not a substring of the input");

    if ((int)out.size() != optimal)
        quitf(_wa, "Longest palindrome has length %d, got %d",
              optimal, (int)out.size());

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid longest palindrome of length %d", optimal);
}
