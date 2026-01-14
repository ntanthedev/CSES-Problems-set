# 1620 - Factory Machines

We use a function `check` that goes through the machines and counts the total number of products they can make in $x$ time units. The function returns true if the number of products is at least the required number of products.

We can efficiently solve the problem using binary search and calling the above function. We find the largest time $k$ such that it is not possible to make enough products. Then $k+1$ is the answer to the problem.

The algorithm works in $O(n \log M)$ time where $M$ is the maximum possible answer. In the following code $M=10^{18}$ which works for the bounds given in the problem statement.

```cpp
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

int main() {
    int n, t;
    cin >> n >> t;

    vector<int> times(n);
    for (int i = 0; i < n; i++) {
        cin >> times[i];
    }

    auto check = [&](ll x) {
        ll total = 0;
        for (int i = 0; i < n; i++) {
            total += x / times[i];
            if (total >= t) return true;
        }
        return false;
    };

    ll k = 0;
    for (ll b = 1e18; b >= 1; b /= 2) {
        while (!check(k + b)) k += b;
    }
    cout << k + 1 << "\n";
}
```