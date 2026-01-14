# 2138 - Reachable Nodes

A directed acyclic graph does not contain cycles which means that we may use a
dynamic programming approach to solve the problem. Let us store a boolean array
for each node, which tells us which nodes are reachable from the node. A
straightforward solution would perform a DFS from each node and update the
arrays after each edge. Each edge would correspond to $O(n)$ operations and
thus, the solution would result in a time complexity of $O(nm)$ and would
perform roughly $5\cdot10^4\cdot10^5=5\cdot10^9$ operations, which makes the
solution a bit too slow.

Fortunately, the approach can be sped up using bitsets. Bitsets allow us to
update 64 positions of the array at once and thus, provide a factor of $1/64$ to
the number of operations, bringing the total down to the order of
$5\cdot10^4\cdot10^5\cdot\frac 1 {64}\approx7.8\cdot10^7$.

```cpp
#include <bitset>
#include <iostream>
#include <vector>
using namespace std;

const int N = 5e4 + 1;

vector<int> g[N];
bitset<N> reach[N];
bool visited[N];

void dfs(int node) {
    if (visited[node]) return;
    visited[node] = true;
    reach[node][node] = true;
    for (int nxt : g[node]) {
        dfs(nxt);
        reach[node] |= reach[nxt];
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= m; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
    }

    for (int i = 1; i <= n; ++i) {
        dfs(i);
        cout << reach[i].count() << ' ';
    }
    cout << '\n';
}
```