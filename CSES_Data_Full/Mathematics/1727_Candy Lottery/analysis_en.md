# 1727 - Candy Lottery

Let $f(i)$ denote the probability that each child gets at most $i$ candies.
Since the probability that a single child gets at most $i$ candies is $i/k$,
we can calculate the probablity using the formula

$$f(i)=(i/k)^n.$$

Then, the probability that the maximum number of candies equals $i$ is

$$f(i)-f(i-1)$$

because we want that at least one child gets exactly $i$ candies and no child
gets more than $i$ candies. We calculate this probability for each possible
maximum number of candies to get the expected maximum.

```cpp
#include <cmath>
#include <iostream>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    auto f = [&](int i) {
        return pow(1.0 * i / k, n);
    };

    double answer = 0;
    for (int i = k; i >= 1; i--) {
        answer += i * (f(i) - f(i - 1));
    }
    cout.precision(6);
    cout << fixed << answer << "\n";
}
```