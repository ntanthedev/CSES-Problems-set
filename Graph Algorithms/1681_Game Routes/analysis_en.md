# 1681 - Game Routes

We solve this program by dynamic programming in a directed acyclic graph.

We start by formulating the problem recursively. Let's denote
by $f(x)$ the number of ways to complete the game when starting from level $x$.

We have two base cases:

* If $x = n$, then $f(x) = 1$ because there are no directed cycles in the
  teleport network.
* If $x \not= n$ and there are no teleports from $x$, then $f(x) = 0$.

Otherwise we will define the function recursively. Let's denote the direct
teleport destinations from $x$ by $d\_1, \dots, d\_k$. Now
$f(x) = \sum\_i f(d\_i)$.
We note that because the teleport network is acyclic, the recursion is
well-defined. We also need to remember to do all calculations modulo
$10^9 + 7$, as requested in the problem statement.

We then apply dynamic programming to the recursion by storing the calculated
values of $f(x)$ in the `n_ways` array.

The time complexity of the solution is $O(n + m)$.

```cpp
#include <iostream>
#include <vector>

using namespace std;

const int N = 100001;
const int MOD = 1000000007;

vector<int> g[N];

bool ready[N];
int n_ways[N];
int n;

int f(int x) {
    if (ready[x]) return n_ways[x];
    ready[x] = true;
    if (x == n) {
        return n_ways[x] = 1;
    }
    for (int y : g[x]) {
        n_ways[x] = (n_ways[x] + f(y)) % MOD;
    }
    return n_ways[x];
}

int main() {
    int m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
    }

    cout << f(1) << endl;
}
```

## References

* [CPHB (Competitive Programmer's Handbook)](http://cses.fi/book),
  Chapter 7.4.2