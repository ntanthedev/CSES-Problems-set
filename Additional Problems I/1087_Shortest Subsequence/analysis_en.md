# 1087 - Shortest Subsequence

We will present a greedy approach and another, simplified version of the same
algorithm.

Start by creating a two dimensional array. Populate this array for each character
and position with the next position at which the character appears in the string.
With this array, we may check if a subsequence appears in the string. This may be
done by going through the subsequence one character at a time and jumping to the
next occurrence of the character. If at any point there is no such occurrence,
then the string is not a subsequence of the original string.

If the original string contains all of the four characters, the answer will
always have a prefix that is a subsequence of the string. A prefix of the
optimal length may be found with a greedy algorithm, that is, we always add the
character whose next occurrence has the greatest index. It is always optimal to
jump as far as possible because the occurrence arrays are increasing. Whenever
one of the characters has no next occurrence, we add the character to the string
and have an answer.

```cpp
#include <algorithm>
#include <iostream>
using namespace std;

const int N = 1e6;
const int INF = 1e9;

int nxt[N + 1][4];

int main() {
    string s;
    cin >> s;

    int n = s.size();

    for (int j = 0; j < 4; ++j) {
        nxt[n][j] = INF;
    }

    for (int i = n; i > 0; --i) {
        for (int j = 0; j < 4; ++j) {
            nxt[i - 1][j] = nxt[i][j];
        }
        int idx = string("ACGT").find(s[i - 1]);
        nxt[i - 1][idx] = i;
    }

    int i = 0;
    string ans;
    while (i < INF) {
        int c = max_element(nxt[i], nxt[i] + 4) - nxt[i];
        ans += "ACGT"[c];
        i = nxt[i][c];
    }

    cout << ans << '\n';
}
```

This solution may be greatly simplified. Remember that, at any time, the next
character picked will be the one whose next occurrence has the greatest index.
Now, this character may be found by maintaining a set of seen characters.
Whenever we have seen three of the characters and come across the fourth one,
we know the fourth one is the one with the greatest distance from the index of
the last picked character.

```cpp
#include <iostream>
#include <set>
using namespace std;

int main() {
    string s;
    cin >> s;

    string ans;
    set<char> seen;

    for (char c : s) {
        seen.insert(c);
        if (seen.size() == 4) {
            ans += c;
            seen.clear();
        }
    }

    for (char c : "ACGT") {
        if (!seen.count(c)) {
            ans += c;
            break;
        }
    }

    cout << ans << '\n';
}
```