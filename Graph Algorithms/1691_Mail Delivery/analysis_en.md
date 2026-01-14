# 1691 - Mail Delivery

Our task is to find an Euler cycle in the graph.
There is a cycle if every node has an even degree and
all edges are in the same connected component.

The following code uses backtracking to construct an Euler cycle.
It recursively creates cycles that begin and end at the same node,
and combines those cycles to form an Euler cycle.

The code works in $O(n+m \log n)$ time because sets are used to
store adjacency lists.
It would be possible to implement the same algorithm in $O(n+m)$ time
in a more complex way using vectors instead of sets.

```cpp
#include <iostream>
#include <set>
#include <vector>
using namespace std;

vector<set<int>> graph;
vector<int> cycle;

void fail() {
    cout << "IMPOSSIBLE\n";
    exit(0);
}

void find_cycle(int node) {
    while (!graph[node].empty()) {
        int next_node = *graph[node].begin();
        graph[node].erase(next_node);
        graph[next_node].erase(node);
        find_cycle(next_node);
    }
    cycle.push_back(node);
}

int main() {
    int n, m;
    cin >> n >> m;

    graph.resize(n + 1);
    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].insert(b);
        graph[b].insert(a);
    }

    for (int i = 1; i <= n; i++) {
        if (graph[i].size() % 2 != 0) fail();
    }

    find_cycle(1);
    if (cycle.size() != m + 1) fail();

    for (auto node : cycle) {
        cout << node << " ";
    }
    cout << "\n";
}
```

# References

* [CPHB (Competitive Programmer's Handbook)](http://cses.fi/book), Chapter 19