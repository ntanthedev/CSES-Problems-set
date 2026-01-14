# 1081 - Common Divisors

We first create a vector `count` that stores for each number between $1$ and
$N$ the number of times it appears in the input.

After that, we perform a sieve of Eratosthenes style search that determines the
maximum divisor that divides at least two numbers. The search takes
$O(N \log N)$ time, because the total number of steps corresponds to the
harmonic sum

$$N + N/2 + N/3 + \dots = O(N \log N).$$

Thus, the solution works in $O(n + N \log N)$ time.

```cpp
#include <iostream>
#include <vector>
using namespace std;
const int N = 1000000;

int main() {
    vector<int> count(N + 1);

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        count[x]++;
    }

    for (int i = N; i >= 1; i--) {
        int total = 0;
        for (int j = i; j <= N; j += i) {
            total += count[j];
        }
        if (total >= 2) {
            cout << i << "\n";
            break;
        }
    }
}
```