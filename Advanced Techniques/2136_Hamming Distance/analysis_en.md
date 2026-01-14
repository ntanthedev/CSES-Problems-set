# 2136 - Hamming Distance

If we were to store each bit separately in a `bool` for example, and then go
through each of the bits when comparing two bit strings, the code would turn out
way too slow. This solution has a time complexity of $O(n^2k)$, as it goes
through each bit in each pair of strings. Fortunately, there is a much more
efficient way of storing the bit strings. What would be a better way to store
them than regular integers?

A C++ `int` has a width of 32 bits, which is more than enough for this task.
The most important observation is that the hamming distance between two bit
strings can be calculated efficiently using the bitwise xor operation. In fact,
the hamming distance corresponds to the amount of bits set in the bitwise xor.
Note that in a bitwise xor, matching bits will result in a zero and differing
bits in a one bit. This is clearly visible in the sample input.

$$\begin{array}{c}
\phantom{\oplus9}101000\\
\underline{\oplus\phantom{9}001000}\\
\phantom{\oplus9}100000\\
\end{array}$$

As each set bit corresponds to a position of differing bits, the amount of bits
set corresponds to the hamming distance. In the example, the number of bits set
is 1 and thus, the answer in 1 as well.

An important function to know is `__builtin_popcount`, which calculates the
popcount of an `int` efficiently. The aforementioned function works even faster
if the compiler knows that we are on a machine which has an instruction for
calculating the popcount. Most modern processors have this instruction,
including the CSES judges, and the following line may be used to convey this
information to the compiler.

```cpp
#pragma GCC target("popcnt")
```

If we assume that $k$ is proportional to the machine word size, we can say that
xor and popcount operations take $O(1)$ time, resulting in a time complexity of
$O(n^2)$.

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    vector<int> b(n);
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        for (int j = 0; j < k; ++j) {
            if (s[j] == '1') {
                b[i] += 1 << j;
            }
        }
    }

    int r = 1e9;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            r = min(r, __builtin_popcount(b[i] ^ b[j]));
        }
    }

    cout << r << '\n';
}
```