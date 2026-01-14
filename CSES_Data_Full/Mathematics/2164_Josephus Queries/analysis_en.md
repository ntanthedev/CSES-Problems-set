# 2164 - Josephus Queries

We can divide the process of removing children into rounds where we go through
the children in increasing order and remove every second of them. For example,
when $n=7$, the rounds are as follows:

* Round $1$: $[1,\underline{2},3,\underline{4},5,\underline{6},7]$
* Round $2$: $[\underline{1},3,\underline{5},7]$
* Round $3$: $[\underline{3},7]$
* Round $4$: $[\underline{7}]$

To efficiently find the $k$th removed child, we simulate the rounds using a
recursive function whose each call corresponds to a round.

Let $\textrm{child}(n,k,p)$ denote the $k$th child who will be removed when
there are $n$ children and the parity of the first child to be removed is $p$
($0$ means we first remove child $2$, and $1$ means we first remove child $1$).

The number of children removed on the first round is
$r = \lfloor n + p \rfloor / 2$. If $k \le r$, we remove the $k$th child on
the first round and just return the number of the child which is $2k - p$.

Otherwise we call the function recursively: we have $n-r$ children left and we
should find the $(k-r)$th child who will be removed. Here $u$ denotes the new
parity: if $n$ is even, the parity remains the same, and if $n$ is odd, the
parity changes. Since the numbering of the children changes in the subproblem,
we have to convert it after the recursive call.

Since we remove half of the children on each round, the number of rounds is
$O(\log n)$ and the function works in $O(\log n)$ time.

```cpp
#include <iostream>
using namespace std;

int child(int n, int k, int p) {
    int r = (n + p) / 2;
    if (k <= r) return k * 2 - p;
    int u = n % 2 == 0 ? p : 1 - p;
    return child(n - r, k - r, u) * 2 - 1 + p;
}

int main() {
    int q;
    cin >> q;

    for (int qi = 1; qi <= q; qi++) {
        int n, k;
        cin >> n >> k;
        cout << child(n, k, 0) << "\n";
    }
}
```

## References

* [Josephus problem (Wikipedia)](https://en.wikipedia.org/wiki/Josephus_problem)