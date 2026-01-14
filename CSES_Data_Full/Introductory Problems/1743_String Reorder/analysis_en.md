# 1743 - String Reorder

Let us first analyze when is it possible construct a string such that no two
adjacent characters are the same. The maximum amount of occurrences for a single
character is reached when it appears in every other position, including the
first and the last. This leads to the inequality $2k\le n+1$, where $k$ is the
number of occurrences of the most common character and $n$ is the length of the
string. The construction is possible if and only if the above inequality holds.

Now, we may construct the answer, one character at a time. To get the
lexicographically smallest string, we will, at each step, choose the smallest
character greedily. The above condition is used to check if the string can be
completed by choosing a specific character.

```cpp
#include <iostream>
using namespace std;

int count[128];

int main() {
    string s;
    cin >> s;

    int n = s.size();

    for (auto c : s) {
        count[(int)c]++;
    }

    auto check = [&](int length) {
        for (int i = 'A'; i <= 'Z'; ++i) {
            if (count[i] * 2 > length + 1) {
                return false;
            }
        }
        return true;
    };

    if (!check(n)) {
        cout << -1 << '\n';
        return 0;
    }

    char prev = '$';
    for (int i = 1; i <= n; ++i) {
        for (int nxt = 'A'; nxt <= 'Z'; ++nxt) {
            if (!count[nxt]) continue;
            if (nxt == prev) continue;
            count[nxt]--;
            if (check(n - i)) {
                cout << (char)nxt;
                prev = nxt;
                break;
            }
            count[nxt]++;
        }
    }
    cout << '\n';
}
```