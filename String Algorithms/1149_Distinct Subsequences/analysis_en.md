# 1149 - Distinct Subsequences

We go through the string from left to right and for each character $c$, maintain
the number of distinct subsequences whose last character is $c$.
This can be efficiently done using dynamic programming.
Finally, the answer to the problem is the sum of all those values.

```cpp
#include <iostream>
#include <map>
using namespace std;
using ll = long long;

const int M = 1000000007;

int main() {
    string s;
    cin >> s;
    int n = s.size();

    map<char, int> count;
    for (int i = 0; i < n; i++) {
        int sum = 1;
        for (int c = 'a'; c <= 'z'; c++) {
            sum += count[c];
            sum %= M;
        }
        count[s[i]] = sum;
    }

    ll ans = 0;
    for (int c = 'a'; c <= 'z'; c++) {
        ans += count[c];
        ans %= M;
    }

    cout << ans << "\n";
}
```

Here is another more concise implementation that uses an additional variable to
store the sum of all dynamic programming values.
Using this technique we do not need loops to calculate the sums.

```cpp
#include <iostream>
#include <map>
using namespace std;
using ll = long long;

const int M = 1000000007;

int main() {
    string s;
    cin >> s;
    int n = s.size();

    map<char, int> count;
    int total_sum = 0;
    for (int i = 0; i < n; i++) {
        int old = count[s[i]];
        count[s[i]] = total_sum + 1;
        total_sum += count[s[i]] - old;
        total_sum = (total_sum % M + M) % M;
    }

    cout << total_sum << "\n";
}
```