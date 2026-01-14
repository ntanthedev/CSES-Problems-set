# 1755 - Palindrome Reorder

Let $\textrm{count}(c)$ denote the number of times letter $c$ appears in the string. We can create a palindrome if $\textrm{count}(c)$ is odd for at most one letter $c$.

To create the palindrome, we first go from A to Z and add $\lfloor \textrm{count}(c)/2 \rfloor$ copies of each letter $c$ to the string. Then, if some letter appears an odd number of times, we add it as the center letter. Finally, we go from Z to A and add $\lfloor \textrm{count}(c)/2 \rfloor$ copies of each letter $c$ to the string.

```cpp
#include <iostream>
#include <map>
#include <vector>
using namespace std;

int main() {
    string s;
    cin >> s;

    map<char, int> count;
    for (auto c : s) {
        count[c]++;
    }

    int odds = 0;
    char center;
    for (char c = 'A'; c <= 'Z'; c++) {
        if (count[c] % 2 == 1) {
            odds++;
            center = c;
        }
    }

    if (odds > 1) {
        cout << "NO SOLUTION\n";
    } else {
        for (char c = 'A'; c <= 'Z'; c++) {
            cout << string(count[c] / 2, c);
        }
        if (odds) {
            cout << center;
        }
        for (char c = 'Z'; c >= 'A'; c--) {
            cout << string(count[c] / 2, c);
        }
        cout << "\n";
    }
}
```