# 1666 - Building Roads

In this problem we are asked to add edges to a graph so that the number of
connected components in the graph is one.

We start by finding the connected components in the starting situation.
This can be done by visiting each city at a time. If the current city $x$
has not already been assigned to a component, we create a new component $c$
and run depth-first search from $x$ assigning every encountered city to the
component $c$.

Building a road from one component to another merges these components and
reduces the number of components by one. Therefore if we have $p$ components,
we need to build $p-1$ roads.

Note that from the
point of view of merging the components, it doesn't matter which
exact cities we pick from each component. We decide to always pick the
city with the smallest index and store the indexes in the vector
`roots`.

Still, there are multiple ways
to construct the roads. Thinking each component as a node, any
tree suffices. We merge the components by building roads
between each pair of subsequent cities in the `roots` vector.

Finding the connected components takes $O(n + m)$ time. Adding the new roads takes
$O(n)$ time since there are at most $n$ components in the beginning.

The total time complexity is therefore $O(n + m)$.

```cpp
#include <iostream>
#include <vector>
using namespace std;

const int N = 100001;
vector<int> graph[N];
int component[N];

void mark_component(int x, int id) {
    if (component[x]) return;
    component[x] = id;
    for (int y : graph[x]) {
        mark_component(y, id);
    }
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

    int count = 0;
    vector<int> roots;
    for (int i = 1; i <= n; ++i) {
        if (component[i] == 0) {
            mark_component(i, ++count);
            roots.push_back(i);
        }
    }

    cout << count - 1 << '\n';
    for (int i = 0; i + 1 < roots.size(); ++i) {
        cout << roots[i] << ' ' << roots[i + 1] << '\n';
    }
}
```