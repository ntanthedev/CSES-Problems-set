# 2186 - Special Substrings

In this analysis, we assume that each character from $\texttt{a}$ to
$\texttt{z}$ appears in the string. If this is not the case, some extra work is
required to ignore the missing characters.

Let $C\_{i, c}$ be the number of occurrences of character $c$ among the first $i$
characters. Now, character $c$ appears in the substring of characters at indices
$[i, j)$ exactly $C\_{j, c} - C\_{i, c}$ times.

For a substring to be special, every character needs to appear a constant amount
of times. We're not interested in the specific constant, which means we can keep
a state of character occurrences relative to some reference character, say
$\texttt{a}$:
$$\begin{align\*}
\big( & C\_{i,\texttt{a}}-C\_{i,\texttt{a}}, \\
& C\_{i,\texttt{b}}-C\_{i,\texttt{a}}, \\
& \dots, \\
& C\_{i,\texttt{z}}-C\_{i,\texttt{a}}
\big),
\end{align\*}$$
Let us look at any character $x$. Note that if
we add a constant amount of occurrences of both $x$ and the reference character
$\texttt{a}$, the relative count stays constant, which means it suffices to
count the number of previous occurrences of the same state.

We will store the current state in an `array<int, 26>` and previous states to a
`map`. The time complexity of a map operation is $O(\log n \cdot \Sigma)$, where
$\Sigma$ represents the alphabet size. The time complexity of the complete
solution is $O(n \log n \cdot \Sigma)$.

```cpp
#include <array>
#include <iostream>
#include <map>
using namespace std;
using ll = long long;

using A = array<int, 26>;

int main() {
    string s;
    cin >> s;

    bool seen[26]{};
    char reference_char = s[0];

    for (char c : s) seen[c - 'a'] = true;

    map<A, int> m;
    A cur{};
    m[cur] = 1;
    ll ans = 0;

    for (char c : s) {
        if (c == reference_char) {
            for (int i = 0; i < 26; ++i) {
                if (seen[i]) cur[i]--;
            }
        }
        cur[c - 'a']++;
        ans += m[cur];
        m[cur]++;
    }

    cout << ans << '\n';
}
```