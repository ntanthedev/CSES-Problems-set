/*

* Problem:      3225 Inverse Suffix Array
* Input read:   n; suffix array sa[1..n]
* Validity:     -1 iff jury says impossible; otherwise output a lowercase string of length n
* ```
            whose suffix array exactly matches the input permutation
* Optimality:   Feasibility is taken from ans; any valid string is accepted
* Complexity:   O(n log n) time, O(n) memory
  */
  #include "testlib.h"
  #include <bits/stdc++.h>
  using namespace std;

static vector<int> build_suffix_array(const string& original) {
string s = original;
s.push_back(char(0));

int n = (int)s.size();
const int ALPHA = 256;

vector<int> p(n), c(n);
vector<int> cnt(max(ALPHA, n), 0);

for (int i = 0; i < n; i++) {
    cnt[(unsigned char)s[i]]++;
}
for (int i = 1; i < ALPHA; i++) {
    cnt[i] += cnt[i - 1];
}
for (int i = 0; i < n; i++) {
    p[--cnt[(unsigned char)s[i]]] = i;
}

c[p[0]] = 0;
int classes = 1;
for (int i = 1; i < n; i++) {
    if (s[p[i]] != s[p[i - 1]]) classes++;
    c[p[i]] = classes - 1;
}

vector<int> pn(n), cn(n);

for (int h = 0; (1 << h) < n; h++) {
    int shift = 1 << h;

    for (int i = 0; i < n; i++) {
        pn[i] = p[i] - shift;
        if (pn[i] < 0) pn[i] += n;
    }

    fill(cnt.begin(), cnt.begin() + classes, 0);
    for (int i = 0; i < n; i++) {
        cnt[c[pn[i]]]++;
    }
    for (int i = 1; i < classes; i++) {
        cnt[i] += cnt[i - 1];
    }
    for (int i = n - 1; i >= 0; i--) {
        int x = pn[i];
        p[--cnt[c[x]]] = x;
    }

    cn[p[0]] = 0;
    int newClasses = 1;

    for (int i = 1; i < n; i++) {
        pair<int, int> cur = {c[p[i]], c[(p[i] + shift) % n]};
        pair<int, int> prev = {c[p[i - 1]], c[(p[i - 1] + shift) % n]};

        if (cur != prev) newClasses++;
        cn[p[i]] = newClasses - 1;
    }

    c.swap(cn);
    classes = newClasses;
}

vector<int> sa;
sa.reserve(n - 1);

for (int i = 1; i < n; i++) {
    sa.push_back(p[i]);
}

return sa;

}

int main(int argc, char* argv[]) {
registerTestlibCmd(argc, argv);

int n = inf.readInt();

vector<int> given(n);
for (int i = 0; i < n; i++) {
    given[i] = inf.readInt();
}

string ref = ans.readToken();

if (ref == "-1") {
    string out = ouf.readToken();

    if (out != "-1") {
        quitf(_wa, "jury answer is -1, but contestant printed '%s'",
              compress(out).c_str());
    }

    if (!ouf.seekEof())
        quitf(_wa, "extra information in the output file");

    quitf(_ok, "correctly reported -1");
}

string out = ouf.readToken();

if (out == "-1") {
    quitf(_wa, "a valid string exists, but contestant printed -1");
}

if ((int)out.size() != n) {
    quitf(_wa, "output string length is %d, expected %d", (int)out.size(), n);
}

for (int i = 0; i < n; i++) {
    if (out[i] < 'a' || out[i] > 'z') {
        quitf(_wa, "output contains invalid character '%c' at position %d",
              out[i], i + 1);
    }
}

vector<int> actual = build_suffix_array(out);

for (int i = 0; i < n; i++) {
    int pos = actual[i] + 1;
    if (pos != given[i]) {
        quitf(_wa, "suffix array mismatch at position %d: got %d, expected %d",
              i + 1, pos, given[i]);
    }
}

if (!ouf.seekEof())
    quitf(_wa, "extra information in the output file");

quitf(_ok, "valid string for the given suffix array");

}
