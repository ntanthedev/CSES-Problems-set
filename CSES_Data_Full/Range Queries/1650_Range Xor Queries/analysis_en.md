# 1650 - Range Xor Queries

A simple prefix (xor) sum array suffices for this problem.

Note, the xor operation has an interesting property:
Xor is its own inverse operation. That is,
for any $x$ it is true that $x \oplus x = 0$, where
$\oplus$ represents the xor operation.
This is in contrast to, say, the addition operation
whose inverse operation is subtraction.

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;

    vector<int> x(n);
    for (int &t : x) {
        cin >> t;
    }

    vector<int> prefix_sums(n + 1);
    for (int i = 0; i < n; ++i) {
        prefix_sums[i + 1] = prefix_sums[i] ^ x[i];
    }

    for (int qi = 0; qi < q; ++qi) {
        int l, r;
        cin >> l >> r;
        l--;
        // Output the xor sum for range [l, r)
        cout << (prefix_sums[r] ^ prefix_sums[l]) << '\n';
    }
}
```