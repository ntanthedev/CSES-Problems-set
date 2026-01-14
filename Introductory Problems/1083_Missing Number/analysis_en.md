# 1083 - Missing Number

We can efficiently solve the problem using a vector that maintains a boolean value for each number between $1$ and $n$: have we seen that number? Then, we can find the only number we have not seen.

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<bool> seen(n + 1);
    for (int i = 1; i <= n - 1; i++) {
        int x;
        cin >> x;
        seen[x] = true;
    }
    for (int i = 1; i <= n; i++) {
        if (!seen[i]) {
            cout << i << "\n";
        }
    }
}
```

In fact, we can also solve the problem without a vector or any other data structure. The idea is to first calculate the sum $1+2+\dots+n$ and then subtract from the sum all numbers given in the input. The resulting value is the only missing number. Note that the sum may overflow when $n$ is large but the final result is still correct.

```cpp
#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += i;
    }
    for (int i = 1; i <= n - 1; i++) {
        int x;
        cin >> x;
        sum -= x;
    }
    cout << sum << "\n";
}
```