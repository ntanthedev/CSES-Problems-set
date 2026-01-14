# 1195 - Flight Discount

We create a graph that consists of $2n$ nodes arranged in two layers.

Each city is represented by two nodes.
Node $i$ corresponds to city $i$ before using the coupon,
and node $n+i$ corresponds to city $i$ after using the coupon.

For each flight, we create three edges.
When there is a flight from city $a$ to city $b$ with weight $x$,
we create the edges $(a,b,x)$, $(a,n+b,\lfloor x/2 \rfloor)$ and $(n+a,n+b,x)$.
The second edge allows us to use the coupon once.

In the above graph, the length of the shortest path from node $1$ to node $2n$
represents the shortest route with the flight discount.

```cpp
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
using ll = long long;

const ll INF = 1e18;

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> graph(2 * n + 1);

    for (int i = 1; i <= m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        graph[a].emplace_back(b, c);
        graph[n + a].emplace_back(n + b, c);
        graph[a].emplace_back(n + b, c / 2);
    }

    vector<ll> distance(2 * n + 1, INF);
    vector<bool> visited(2 * n + 1);

    priority_queue<pair<ll, int>> queue;
    queue.emplace(0, 1);
    distance[1] = 0;

    while (!queue.empty()) {
        int node = queue.top().second;
        queue.pop();

        if (visited[node]) continue;
        visited[node] = true;

        for (auto [next_node, weight] : graph[node]) {
            ll new_distance = distance[node] + weight;
            if (new_distance < distance[next_node]) {
                distance[next_node] = new_distance;
                queue.emplace(-new_distance, next_node);
            }
        }
    }

    cout << distance[2 * n] << "\n";
}
```