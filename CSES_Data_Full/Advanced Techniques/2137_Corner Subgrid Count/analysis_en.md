# 2137 - Corner Subgrid Count

Going through all possible corners of a subgrid would run in $O(n^4)$ and thus,
be too slow. There is, however, a way to calculate the number of subgrids by
only going through each pair of rows.

Let us go through each pair of rows and find each subgrid which spans from one
of the selected rows to another. For a pair of rows to form a subgrid, the rows
need to share two distinct positions which have black squares in both of the
rows. If we know the number of such positions is $c$, the number of subgrids the
rows form, is ${c \choose 2} = \frac{c(c-1)}{2}$, as we may choose any two of
them as the borders of the subgrid. This algorithm runs in $O(n^3)$ as we go
through each pair of rows in $O(n)$ time and there are in total $O(n^2)$ pairs
of rows.

With $n=3000$, the solution would perform roughly $3000^3\approx3\cdot10^{10}$
operations and would still be too slow. We may, however, use bitsets to improve
the constant factor of the solution. Bitsets allow us to check multiple
positions at once. On a Linux system, bitsets usually contain 64-bit integers.
This means that, with constant time bit operations, we can check 64 positions at
once. Thus, the number of operations becomes $3000^3\cdot\frac 1
{64}\approx4\cdot10^8$.

To find the positions where the two rows both have a black square, we will use
the bitwise AND operation as it discards the positions where only one or neither
of the squares are black. Finally, we will count the number of bits set in the
bitset using the method `.count()`. Note that even with the bitset optimization
the solution will turn out too slow without the line

```cpp
#pragma GCC target("popcnt")
```

which tells the compiler that our machine has an instruction for calculating the
popcount of an integer, that is, our processor is able to count the number of
bits set in an integer efficiently. The popcount instruction is available on
CSES judges and has been included in most of Intel's x86-64 processors since
2008.

```cpp
#pragma GCC target("popcnt")
#include <bitset>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
using B = bitset<3000>;

int main() {
    int n;
    cin >> n;

    vector<B> b(n);
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        for (int j = 0; j < n; ++j) {
            if (s[j] == '1') {
                b[i][j] = true;
            }
        }
    }

    ll r = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int c = (b[i] & b[j]).count();
            r += c * (c - 1) / 2;
        }
    }

    cout << r << '\n';
}
```