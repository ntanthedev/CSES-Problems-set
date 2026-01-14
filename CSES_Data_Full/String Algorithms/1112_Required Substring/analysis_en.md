# 1112 - Required Substring

## Solution 1

Suppose we read characters of a string one after another and have to detect when
the last $m$ characters form the pattern. To do that, we have to remember the
longest prefix of the pattern that is also a suffix of our current string.

For example, if the pattern is `ABABC` and we have read the string `CAABAB`, the
prefix is `ABAB` (length $4$). Consider what can happen when we read the next
character:

* If we read `A`, the prefix becomes `ABA` (length $3$).
* If we read `B`, the prefix becomes empty (length $0$).
* If we read `C`, the prefix becomes `ABABC` (length $5$).
* If we read any other character, the prefix becomes empty (length $0$).

We define a transition function $\textrm{step}[i][c]$: if the length of the
prefix is $i$ and we read character $c$, what is the length of the prefix after
that? For example, in the above situation $\textrm{step}[4][\textrm{A}]=3$,
$\textrm{step}[4][B]=0$, and $\textrm{step}[4][\textrm{C}]=5$. We also define
that $\textrm{step}[m][c]=m$ for any character $c$ because in that case the
pattern is a subtring of the string, regardless of what characters will come
after that.

After that, we use dynamic programming to solve the problem. We calculate values
of $\textrm{ways}[i][j]$: in how many ways can we create a string of length $i$
that ends with a prefix whose length is $j$ (or contains the whole pattern if
$j=m$)?

The answer to the problem is $\textrm{ways}[n][m]$, and the algorithm works in
$O(nmk)$ time where $k$ is the size of the alphabet.

```cpp
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const int M = 1000000007;

int step[101][128];
ll ways[1001][101];

int main() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    int m = s.size();

    for (int i = 0; i < m; i++) {
        for (int c = 'A'; c <= 'Z'; c++) {
            string u = s.substr(0, i) + (char)c;
            while (s.substr(0, u.size()) != u) {
                u = u.substr(1);
            }
            step[i][c] = u.size();
        }
    }
    for (int c = 'A'; c <= 'Z'; c++) {
        step[m][c] = m;
    }

    ways[0][0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= m; j++) {
            for (int c = 'A'; c <= 'Z'; c++) {
                ways[i + 1][step[j][c]] += ways[i][j];
                ways[i + 1][step[j][c]] %= M;
            }
        }
    }

    cout << ways[n][m] << '\n';
}
```

## Solution 2: prefix function

The construction of the finite state machine can be sped up by utilizing the
prefix function. It allows us to construct the transitions in $O(nk)$ time.

The prefix function $\pi(i)$ of a string is defined as follows: each $\pi(i)$
denotes the maximum length of a substring that ends at position $i$ and is a
strict prefix of the string. The prefix function might be familiar from the KMP
algorithm.

```cpp
#include <algorithm>
#include <array>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const int M = 1000000007;

// Returns the values of the prefix function for string s.
// The prefix function pi(i) is defined as follows: each pi(i) denotes the
// maximum length of a substring that ends at position i and is a strict prefix
// of the string.
vector<int> prefix_function(string &s) {
    const int n = (int)s.size();
    vector<int> r(n);
    for (int i = 1; i < n; ++i) {
        int j = r[i - 1];
        while (j > 0 && s[i] != s[j]) j = r[j - 1];
        r[i] = j + (s[i] == s[j]);
    }
    return r;
}

int step[101][128];
ll ways[1001][101];

int main() {
    int n;
    cin >> n;

    string s;
    cin >> s;

    int m = s.size();
    auto links = prefix_function(s);

    for (int i = 0; i < m; i++) {
        for (int c = 'A'; c <= 'Z'; c++) {
            if (s[i] == c) {
                step[i][c] = i + 1;
            } else if (i > 0) {
                step[i][c] = step[links[i - 1]][c];
            }
        }
    }
    for (int c = 'A'; c <= 'Z'; c++) {
        step[m][c] = m;
    }

    ways[0][0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= m; j++) {
            for (int c = 'A'; c <= 'Z'; c++) {
                ways[i + 1][step[j][c]] += ways[i][j];
                ways[i + 1][step[j][c]] %= M;
            }
        }
    }

    cout << ways[n][m] << '\n';
}
```

## References

* [Wikipedia (Knuth–Morris–Pratt algorithm)](https://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm)