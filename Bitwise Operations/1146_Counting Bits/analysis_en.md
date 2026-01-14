# 1146 - Counting Bits

It is useful to analyze the pattern of each bit individually. Here are the
binary representations of the integers $1 \dots 15$.

$$\begin{array}{l|l}
1 & 0001 \\
2 & 0010 \\
3 & 0011 \\
4 & 0100 \\
5 & 0101 \\
6 & 0110 \\
7 & 0111 \\
8 & 1000 \\
9 & 1001 \\
10 & 1010 \\
11 & 1011 \\
12 & 1100 \\
13 & 1101 \\
14 & 1110 \\
15 & 1111
\end{array}$$

If we examine bit $2 ^ i$, it looks like the first $2 ^ i - 1$ numbers have the bit
set as $0$, then the next $2 ^ i$ have it set as $1$, then $2 ^ i$ numbers have
it again set as a zero bit, and so on. It may be proven that this is, in fact,
the case for all bits.

Now, we can loop through each bit individually and count the number of one bits
in the corresponding position in the numbers $1 \dots n$. Let us call a complete
set of $2 ^ i$ zeros followed by $2 ^ i$ ones a cycle. First, we will count the
number of complete cycles, and then, count the number of one bits in the last
cycle, which may not be a complete one.

This solution has a time complexity of $O(\log n)$.

```cpp
#include <iostream>
using namespace std;
using ll = long long;

int main() {
    ll n;
    cin >> n;

    ll sum = 0;
    for (int j = 60; j >= 0; --j) {
        ll bit = 1ll << j;
        sum += n / (bit * 2) * bit;
        sum += max(0ll, n % (bit * 2) - (bit - 1));
    }

    cout << sum << '\n';
}
```