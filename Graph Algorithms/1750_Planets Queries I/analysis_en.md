# 1750 - Planets Queries I

We start solving the problem by precomputing the destinations for every planet
when the number of teleports is a power of two. We will store the destination
reached from planet $x$ after traveling through $2^l$ teleports in
$\mathrm{succ}[l][x]$. We fill the array layer by layer in the order of
increasing $l$. For $l = 0$ we simply set $\mathrm{succ}[0][x]$ to the planet
reached from $x$ by going through one teleport. For $l > 0$ we set
$\mathrm{succ}[l][x] = \mathrm{succ}[l-1][\mathrm{succ}[l-1][x]]$.

To solve the case where the number of teleports $k$ is not a power of two,
we will use the binary representation of $k$ to find powers of two
$s\_1, \dots, s\_m$ such that $\sum\_i s\_i = k$. We can then find the final
destination by using the $\mathrm{succ}$ array to take $s\_1$ steps, $s\_2$
steps, and so on.

Let's denote the maximum value of $k$ by $K$ ($K = 10^9$ in the task statement).
Building the $\mathrm{succ}$ array takes $O(n \log K)$ time and answering the
queries takes $O(q \log K)$. Therefore the total time complexity of the
solution is $O((n + q) \log K)$.

```cpp
#include <iostream>
using namespace std;

const int N = 200001;
const int M = 30;

int succ[M][N];

int main() {
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; ++i) {
        cin >> succ[0][i];
    }

    for (int i = 1; i < M; ++i) {
        for (int j = 1; j <= n; ++j) {
            succ[i][j] = succ[i - 1][succ[i - 1][j]];
        }
    }

    for (int i = 0; i < q; ++i) {
        int x, k;
        cin >> x >> k;
        for (int j = 0; j < M; ++j) {
            if (k & (1 << j)) {
                x = succ[j][x];
            }
        }
        std::cout << x << '\n';
    }
}
```

## References

* [CPHB (Competitive Programmer's Handbook)](http://cses.fi/book),
  Chapter 16.3