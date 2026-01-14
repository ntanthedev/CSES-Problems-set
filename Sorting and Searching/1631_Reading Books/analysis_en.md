# 1631 - Reading Books

If there is a single long book and reading the book takes more time than to read all other books, the answer is $2x$ where $x$ is the time needed to read the book. In this case Kotivalo can first read the long book while Justiina reads all other books. After this, the roles are changed.

Otherwise, the answer is the sum of all reading times $t\_1+t\_2+\dots+t\_n$. In this case Kotivalo can read all the books sorted by reading time from longest to shortest. Justiina does almost the same but starts with the second longest book and reads the longest book as the last book. This ensures that they are never reading the same book at the same time.

```cpp
#include <iostream>
using namespace std;
using ll = long long;

int main() {
    int n;
    cin >> n;

    ll total = 0;
    ll longest = 0;
    for (int i = 1; i <= n; i++) {
        ll x;
        cin >> x;
        total += x;
        longest = max(longest, x);
    }

    cout << max(total, 2 * longest) << "\n";
}
```