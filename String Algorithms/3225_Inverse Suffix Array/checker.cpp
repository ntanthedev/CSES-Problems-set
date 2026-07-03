#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

struct RollingHash {
    static const long long base = 911382323;
    static const long long mod = 1000000007;
    vector<long long> pw, h;

    RollingHash(const string& s) {
        int n = (int)s.size();
        pw.resize(n + 1);
        h.resize(n + 1);
        pw[0] = 1;
        for (int i = 0; i < n; i++) {
            pw[i + 1] = pw[i] * base % mod;
            h[i + 1] = (h[i] * base + s[i]) % mod;
        }
    }

    long long get(int l, int r) const {
        return (h[r] - h[l] * pw[r - l] % mod + mod) % mod;
    }
};

bool suffix_less(const string& s, const RollingHash& rh, int i, int j) {
    int ni = (int)s.size() - i;
    int nj = (int)s.size() - j;
    int lo = 0, hi = min(ni, nj);
    while (lo < hi) {
        int mid = (lo + hi + 1) / 2;
        if (rh.get(i, i + mid) == rh.get(j, j + mid))
            lo = mid;
        else
            hi = mid - 1;
    }
    if (lo == ni && lo == nj) return false;
    if (lo == ni) return true;
    if (lo == nj) return false;
    return s[i + lo] < s[j + lo];
}

bool valid_suffix_array(const string& s, const vector<int>& sa) {
    int n = (int)sa.size();
    vector<int> seen(n + 1, 0);
    for (int i = 0; i < n; i++) {
        if (sa[i] < 1 || sa[i] > n) return false;
        if (seen[sa[i]]) return false;
        seen[sa[i]] = 1;
    }

    RollingHash rh(s);
    for (int i = 0; i + 1 < n; i++) {
        int a = sa[i] - 1;
        int b = sa[i + 1] - 1;
        if (!suffix_less(s, rh, a, b))
            return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    vector<int> given(n);
    for (int i = 0; i < n; i++)
        given[i] = inf.readInt();

    string ref = ans.readToken();
    string first = ouf.readToken();

    if (ref == "-1") {
        if (first != "-1")
            quitf(_wa, "No string corresponds to this suffix array");
        if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
        quitf(_ok, "Correct: impossible suffix array");
    }

    if (first == "-1")
        quitf(_wa, "A valid string exists for this suffix array");

    string out = first;
    if ((int)out.size() != n)
        quitf(_wa, "String length is %d, expected %d", (int)out.size(), n);

    for (char c : out) {
        if (c < 'a' || c > 'z')
            quitf(_wa, "Output contains invalid character '%c'", c);
    }

    if (!valid_suffix_array(out, given))
        quitf(_wa, "Suffix array of output does not match input");

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid string for suffix array");
}
