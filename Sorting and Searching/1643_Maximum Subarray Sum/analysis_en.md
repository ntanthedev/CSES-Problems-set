# 1643 - Maximum Subarray Sum

We go through the array and maintain two values:

* `sum`: the maximum subarray sum that ends at our current position
* `best`: the maximum subarray sum seen so far

Let us assume that the value at position $i$ is $x$ and we want to calculate the maximum subarray sum that ends at position $i$. We can do this efficiently when we know the previous maximum subarray sum that ends at position $i-1$: either we add $x$ to the previous sum or then just create a sum using $x$.

Note that the problem statement requires that the subarray is nonempty, so we have to remember that the maximum sum can also be negative.

```cpp
#include <iostream>
using namespace std;
using ll = long long;

int main() {
    int n;
    cin >> n;

    ll sum = -1e9;
    ll best = -1e9;
    for (int i = 1; i <= n; i++) {
        ll x;
        cin >> x;
        sum = max(sum + x, x);
        best = max(best, sum);
    }
    cout << best << "\n";
}
```

## References

* [Maximum subarray problem (Wikipedia)](https://en.wikipedia.org/wiki/Maximum_subarray_problem)