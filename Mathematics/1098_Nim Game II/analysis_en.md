# 1098 - Nim Game II

We calculate the Grundy number of each heap and then calculate the xor sum of
the numbers to determine the winner.

It turns out that the Grundy numbers form a cycle $0,1,2,3,0,1,2,3,\dots$, so
if a heap has $x$ sticks, its Grundy number is $x \bmod 4$.

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
            sum ^= (x % 4);
        }
        cout << (sum != 0 ? "first" : "second") << "\n";
    }
}
```

## References

* [Nim (Wikipedia)](https://en.wikipedia.org/wiki/Nim)