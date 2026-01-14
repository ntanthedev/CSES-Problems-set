# 1094 - Increasing Array

The following code goes through the array from left to right. If a number is smaller than the previous number, we have to increase it, and the optimal way to do that is by setting it equal to the previous number.

```cpp
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

int main() {
    int n;
    cin >> n;
    vector<int> x(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> x[i];
    }
    ll res = 0;
    for (int i = 2; i <= n; i++) {
        if (x[i] < x[i - 1]) {
            res += x[i - 1] - x[i];
            x[i] = x[i - 1];
        }
    }
    cout << res << "\n";
}
```