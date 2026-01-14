# 1668 - Building Teams

In this problem we are asked to check whether a graph is bipartite.

The key observation to solve the problem is that if we assign pupil
$x$ to team $1$, then we have to assign every friend of $x$ to
team $2$. We can continue this process to the friends of the friends
and so on. If we notice that two friends have been
assigned to the same team, we know that the division into two teams is
impossible. Otherwise we found a valid division for all pupils reachable
from $x$.

We start by going through all pupils. If pupil $x$ hasn't been
assigned to a team we run a depth-first search (DFS) assigning $x$ to
team $1$ and all reachable pupils according to the graph structure.

After this we go through the pupils and print the team assignments.

The time complexity of the solution is $O(n + m)$.

```cpp
#include <iostream>
#include <vector>
using namespace std;

const int N = 100001;
vector<int> graph[N];
int teams[N];

// The return value indicates whether the team assignments were successful
bool dfs(int x, int team) {
    if (teams[x] != 0) return teams[x] == team;
    teams[x] = team;
    for (int y : graph[x]) {
        if (!dfs(y, 3 - team)) return false;
    }
    return true;
}

int main() {
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    for (int i = 1; i <= n; ++i) {
        if (teams[i] != 0) continue;
        if (!dfs(i, 1)) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
    }

    for (int i = 1; i <= n; ++i) {
        cout << teams[i] << ' ';
    }
    cout << '\n';
}
```