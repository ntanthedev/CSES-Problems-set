# 1690 - Hamiltonian Flights

We solve the problem in $O(2^n n^2)$ time using dynamic programming.
We calculate, for each city $c$ and subset of cities $S$,
the number of ways we can reach city $c$ from city $1$
so that we visit every city in $S$ once.

We represent each subset of cities as a bitmask of $n$ bits.
For each such bitmask, we go through all possible ways to select
the last and previous city on the route.
There are $O(2^n)$ possible subsets of cities and
$O(n^2)$ possible ways to select the last and previous city.

```cpp
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

const int M = 1000000007;

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> count(n, vector<int>(n));

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        count[a][b]++;
    }

    vector<vector<ll>> ways(1 << n, vector<ll>(n));
    ways[1][0] = 1;

    for (int mask = 2; mask < (1 << n); mask++) {
        vector<int> nodes;
        for (int node = 0; node < n; node++) {
            if (mask & (1 << node)) {
                nodes.push_back(node);
            }
        }

        for (auto last : nodes) {
            for (auto prev : nodes) {
                ways[mask][last] +=
                    count[prev][last] * ways[mask ^ (1 << last)][prev];
            }
            ways[mask][last] %= M;
        }
    }

    cout << ways[(1 << n) - 1][n - 1] << "\n";
}
```