# 1139 - Distinct Colors

We will create a `set` for each node. The set will contain all values in the
subtree of each node.

The set of each node will be constructed recursively from the sets of its
children. Merging the sets naïvely would be too slow. Fortunately, there is a
way to merge them efficiently.

If a set of a child is larger than the set of its parent, we swap the sets
before merging. We always move the elements from the smaller set to the larger
set, which ensures that each value will be moved $O(\log n)$ times. The total
time complexity of the solution $O(n\log^2 n)$.

Note that we use the standard library function `swap` for swapping the sets. It
is guaranteed to work in $O(1)$ time for standard library containers.

```cpp
#include <iostream>
#include <set>
#include <vector>
using namespace std;

const int N = 200001;
vector<int> g[N];
int answer[N], color[N];

set<int> dfs(int node, int parent) {
    set<int> colors{color[node]};
    for (int child : g[node]) {
        if (child == parent) continue;
        auto child_colors = dfs(child, node);
        // `swap` is guaranteed to work in O(1) for stl containers.
        if (child_colors.size() > colors.size()) {
            swap(colors, child_colors);
        }
        colors.merge(child_colors);
    }
    answer[node] = colors.size();
    return colors;
}

int main() {
    int n;
    cin >> n;

    for (int i = 1; i <= n; ++i) {
        cin >> color[i];
    }

    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    dfs(1, -1);

    for (int i = 1; i <= n; ++i) {
        cout << answer[i] << ' ';
    }
    cout << '\n';
}
```