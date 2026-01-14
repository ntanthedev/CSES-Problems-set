# 3421 - Distinct Values Subsequences

If a number $x$ appears $c$ times in the array, we can either include one of the occurrences in the subsequence or not include the number at all. Thus, there are $c+1$ possible ways to choose how the number $x$ appears in the subsequence.

Using this idea, we can handle each number separately and calculate the answer. Finally, we should subtract one from the answer because we don't want to include the empty subsequence.

```cpp
#include <iostream>
#include <map>
using namespace std;
using ll = long long;
const int M = 1000000007;

int main() {
    int n;
    cin >> n;

    map<int, int> counts;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        counts[x]++;
    }

    ll answer = 1;
    for (auto [value, count] : counts) {
        answer *= (count + 1);
        answer %= M;
    }
    answer = (answer - 1 + M) % M;
    cout << answer << "\n";
}
```