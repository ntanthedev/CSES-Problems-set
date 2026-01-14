# 1730 - Nim Game I

In this problem we are given a nim state and our task is to check if it is a
winning or losing position. To do that, we calculate the xor sum of heap sizes.

If the sum is nonzero, we are in a winning position because there is always a
move that makes the sum zero.

If the sum is zero, we are in a losing position because every move modifies the
sum so that it becomes nonzero.

```cpp
#include <iostream>
using namespace std;

int main() {
    int t;
    cin >> t;

    for (int ti = 1; ti <= t; ti++) {
        int n;
        cin >> n;
        int sum = 0;
        for (int i = 1; i <= n; i++) {
            int x;
            cin >> x;
            sum ^= x;
        }
        cout << (sum != 0 ? "first" : "second") << "\n";
    }
}
```

## References

* [Nim (Wikipedia)](https://en.wikipedia.org/wiki/Nim)