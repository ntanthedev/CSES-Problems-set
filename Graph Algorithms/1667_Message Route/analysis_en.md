# 1667 - Message Route

The computer network defines an undirected graph with unit length
edges. In such a graph, the length of the shortest path can be found with the
breadth-first search (BFS).

We are also asked to construct the shortest path. To do this we
modify the BFS a bit.
When processing a computer $x$ and adding a new computer $y$ to the
BFS queue, we also associate the index of $x$ with $y$. This is stored in the
`parent` array and corresponds to the second last computer
in the shortest path from $A$ to $y$.

After this we construct the shortest path in reverse order by following
the route defined by the `parent` array from `B` to `A`.

The time complexity of the solution is $O(n + m)$.

```cpp
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
const int N = 100001;

vector<int> graph[N];
bool visited[N];
int parent[N];

int main() {
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    queue<int> queue;
    queue.push(1);
    visited[1] = true;

    while (!queue.empty()) {
        int x = queue.front();
        queue.pop();
        for (int y : graph[x]) {
            if (visited[y]) continue;
            visited[y] = true;
            parent[y] = x;
            queue.push(y);
        }
    }

    if (!visited[n]) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    vector<int> ans;
    int x = n;
    while (x != 0) {
        ans.push_back(x);
        x = parent[x];
    }
    reverse(ans.begin(), ans.end());

    cout << ans.size() << '\n';
    for (int x : ans) {
        cout << x << ' ';
    }
    cout << '\n';
}
```