# 1068 - Weird Algorithm

The following code implements the algorithm. Note that the numbers in the sequence may be much larger than the initial $n$ value. For $n \le 10^6$, it is enough to use a 64-bit integer type.

```cpp
#include <iostream>
using namespace std;
using ll = long long;

int main() {
    ll n;
    cin >> n;
    while (true) {
        cout << n << " ";
        if (n == 1) break;
        if (n % 2 == 0) {
            n = n / 2;
        } else {
            n = 3 * n + 1;
        }
    }
    cout << "\n";
}
```

## References

* [Collatz conjecture (Wikipedia)](https://en.wikipedia.org/wiki/Collatz_conjecture)