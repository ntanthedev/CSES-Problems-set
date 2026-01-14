# 2183 - Missing Coin Sum

Suppose that we can create all sums $1,2,\dots,k$ using a subset of coins. Then, if we add a new coin whose value $x$ is at most $k+1$, we can create all sums $1,2,\dots,k+x$, but if the value is more than $k+1$, we can't create the sum $k+1$ after adding the coin.

We can start with an empty subset, go through the coins in increasing order of their values and try to extend the subset at each coin. Either we can add the coin to the subset and increase the sum, or detect that no more coins can be added and we have found the solution.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

int main() {
    int n;
    cin >> n;

    vector<int> values(n);
    for (int i = 0; i < n; i++) {
        cin >> values[i];
    }
    sort(values.begin(), values.end());

    ll largest = 0;
    for (int i = 0; i < n; i++) {
        if (values[i] > largest + 1) {
            break;
        }
        largest += values[i];
    }
    cout << largest + 1 << "\n";
}
```