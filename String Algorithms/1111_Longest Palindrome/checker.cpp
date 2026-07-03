/*

* Problem:      1111 Longest Palindrome
* Input read:   string s
* Validity:     Output a nonempty lowercase string that is a palindromic substring of s
* Optimality:   Output length must equal the longest palindrome length from ans
* Complexity:   O(n) time, O(n) memory
  */
  #include "testlib.h"
  #include <bits/stdc++.h>
  using namespace std;

static bool is_palindrome(const string& t) {
int l = 0;
int r = (int)t.size() - 1;

while (l < r) {
    if (t[l] != t[r]) return false;
    l++;
    r--;
}

return true;

}

static bool contains_kmp(const string& s, const string& pat) {
int n = (int)s.size();
int m = (int)pat.size();

if (m == 0) return true;
if (m > n) return false;

vector<int> pi(m, 0);
for (int i = 1; i < m; i++) {
    int j = pi[i - 1];
    while (j > 0 && pat[i] != pat[j]) j = pi[j - 1];
    if (pat[i] == pat[j]) j++;
    pi[i] = j;
}

int j = 0;
for (int i = 0; i < n; i++) {
    while (j > 0 && s[i] != pat[j]) j = pi[j - 1];
    if (s[i] == pat[j]) j++;
    if (j == m) return true;
}

return false;

}

int main(int argc, char* argv[]) {
registerTestlibCmd(argc, argv);

string s = inf.readToken();
string ref = ans.readToken();

int n = (int)s.size();
int optimal = (int)ref.size();

string out = ouf.readToken(format("[a-z]{1,%d}", n), "palindrome");

if ((int)out.size() != optimal) {
    quitf(_wa, "output length is %d, but longest palindrome length is %d",
          (int)out.size(), optimal);
}

if (!is_palindrome(out)) {
    quitf(_wa, "output string is not a palindrome");
}

if (!contains_kmp(s, out)) {
    quitf(_wa, "output string is not a substring of the input");
}

if (!ouf.seekEof())
    quitf(_wa, "extra information in the output file");

quitf(_ok, "valid longest palindrome of length %d", optimal);

}
