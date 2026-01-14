# 1655 - Maximum Xor Subarray

Let us construct a new array $(S\_1, S\_2, S\_3, \dots, S\_n)$, where $S\_i$
represents the xor prefix sum of the first $i$ elements. Now, the xor sum of the
subarray from $i$ to $j$ is equal to $S\_j \oplus S\_{i-1}$.

If we check each possible ending position separately, we need to maximize the
expression $S\_j \oplus S\_{i-1}$ for a fixed $j$, in other words, find the $i$
which maximizes the expression. This may be done using a trie data structure.

Usually tries are used for storing strings but in this task, we will store the
numbers according to their binary representation. This way, we can find each
optimal starting position in logarithmic time. We will find the optimal prefix
sum one bit at a time, starting from the most significant bit. Because each bit
has a value larger than the sum of the bits following it, it is optimal to
decide the largest bit first.

```cpp
#include <iostream>
using namespace std;

const int N = 200001;
const int LOG_X = 30;
const int NODES = N * LOG_X;

int c[NODES][2], nodes = 1;

void add(int x) {
    int n = 0;
    for (int shift = LOG_X - 1; shift >= 0; --shift) {
        int bit = x >> shift & 1;
        if (!c[n][bit]) c[n][bit] = nodes++;
        n = c[n][bit];
    }
}

int query(int x) {
    int n = 0, ret = 0;
    for (int shift = LOG_X - 1; shift >= 0; --shift) {
        int bit = ~x >> shift & 1;
        if (!c[n][bit]) {
            n = c[n][!bit];
        } else {
            ret += 1 << shift;
            n = c[n][bit];
        }
    }
    return ret;
}

int x[N];

int main() {
    int n;
    cin >> n;

    int ans = 0, sum = 0;
    add(0);

    for (int i = 0; i < n; ++i) {
        cin >> x[i];
        sum ^= x[i];
        ans = max(ans, query(sum));
        add(sum);
    }

    cout << ans << '\n';
}
```