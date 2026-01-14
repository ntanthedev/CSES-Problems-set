# 1682 - Flight Routes Check

To solve the problem it is enough to check, for every city $x$, if it is
possible to travel from $x$ to $1$ and from $1$ to $x$. This can be done by
running two depth-first searches from $1$, one in the original graph and one
in a graph generated from the original graph by reversing all edges.

If we find a city $x$ for which one of the conditions does not hold, then
it is not possible to travel from every city to every other city. If the
conditions hold for any $x$, then we can travel between any pair of cities
$a$ and $b$ by first traveling from $a$ to $1$ and then from $1$ to $b$.

The time complexity of the solution is $O(n + m)$.

```cpp
#include <iostream>
#include <vector>

using namespace std;
const int N = 100001;

vector<int> g[N];
vector<int> rev_g[N];

bool visited1[N];
bool visited2[N];

void dfs1(int x) {
    if (visited1[x]) return;
    visited1[x] = true;
    for (int y : g[x]) {
        dfs1(y);
    }
}

void dfs2(int x) {
    if (visited2[x]) return;
    visited2[x] = true;
    for (int y : rev_g[x]) {
        dfs2(y);
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        rev_g[b].push_back(a);
    }

    dfs1(1);
    dfs2(1);

    for (int i = 1; i <= n; ++i) {
        if (!visited1[i]) {
            cout << "NO\n";
            cout << 1 << ' ' << i << '\n';
            return 0;
        }
        if (!visited2[i]) {
            cout << "NO\n";
            cout << i << ' ' << 1 << '\n';
            return 0;
        }
    }

    cout << "YES\n";
}
```