# 1674 - Subordinates

Another way to formulate the problem:
We are given a rooted tree and
we have to find out, for each node,
the number of children in its subtree.

This task can be solved with a single pass of DFS (Depth-First Search).
The number of children is calculated by adding up the answers of each children with the number of children.

```cpp
#include <iostream>
#include <vector>
using namespace std;

const int N = 200001;
vector<int> g[N];
int subordinates[N];

void dfs(int node) {
    for (int child : g[node]) {
        dfs(child);
        subordinates[node] += subordinates[child] + 1;
    }
}

int main() {
    int n;
    cin >> n;

    for (int i = 2; i <= n; ++i) {
        int p;
        cin >> p;
        g[p].push_back(i);
    }

    dfs(1);

    for (int i = 1; i <= n; ++i) {
        cout << subordinates[i] << ' ';
    }
    cout << '\n';
}
```

## References

* [Depth first search (Wikipedia)](https://en.wikipedia.org/wiki/Depth-first_search)