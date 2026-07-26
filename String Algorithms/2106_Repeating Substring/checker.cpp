/*

* Problem:      2106 Repeating Substring
* Input read:   string s
* Validity:     -1 iff jury says no repeating substring; otherwise output a nonempty lowercase
* ```
            substring of s that occurs at least twice
* Optimality:   Output length must equal the longest repeating substring length from ans
* Complexity:   O(n) time, O(n) memory
  */
  #include "testlib.h"
  #include <bits/stdc++.h>
  using namespace std;

static int count_occurrences_at_least_two_kmp(const string& s, const string& pat) {
int n = (int)s.size();
int m = (int)pat.size();

if (m == 0 || m > n) return 0;

vector<int> pi(m, 0);
for (int i = 1; i < m; i++) {
    int j = pi[i - 1];
    while (j > 0 && pat[i] != pat[j]) j = pi[j - 1];
    if (pat[i] == pat[j]) j++;
    pi[i] = j;
}

int cnt = 0;
int j = 0;

for (int i = 0; i < n; i++) {
    while (j > 0 && s[i] != pat[j]) j = pi[j - 1];
    if (s[i] == pat[j]) j++;

    if (j == m) {
        cnt++;
        if (cnt >= 2) return cnt;
        j = pi[j - 1];
    }
}

return cnt;

}

int main(int argc, char* argv[]) {
registerTestlibCmd(argc, argv);

string s = inf.readToken();
int n = (int)s.size();

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
    quitf(_wa, "a repeating substring exists, but contestant printed -1");
}

if (out.empty()) {
    quitf(_wa, "output substring must be nonempty");
}

if ((int)out.size() > n) {
    quitf(_wa, "output length is %d, greater than input length %d",
          (int)out.size(), n);
}

for (int i = 0; i < (int)out.size(); i++) {
    if (out[i] < 'a' || out[i] > 'z') {
        quitf(_wa, "output contains invalid character '%c' at position %d",
              out[i], i + 1);
    }
}

int optimal = (int)ref.size();

if ((int)out.size() != optimal) {
    quitf(_wa, "output length is %d, but longest repeating substring length is %d",
          (int)out.size(), optimal);
}

if (count_occurrences_at_least_two_kmp(s, out) < 2) {
    quitf(_wa, "output substring occurs fewer than two times in the input");
}

if (!ouf.seekEof())
    quitf(_wa, "extra information in the output file");

quitf(_ok, "valid longest repeating substring of length %d", optimal);

}
