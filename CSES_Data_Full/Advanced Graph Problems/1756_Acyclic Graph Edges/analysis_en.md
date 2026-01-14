# 1756 - Acyclic Graph Edges

There is a surprisingly simple solution to this problem. If we direct each edge from the
smaller index towards the larger index, the resulting graph will be acyclic.
There will be no cycles because each edge goes to a larger index and there are
no edges which move to a smaller index.

```cpp
#include <iostream>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= m; ++i) {
        int a, b;
        cin >> a >> b;
        cout << min(a, b) << ' ' << max(a, b) << '\n';
    }
}
```