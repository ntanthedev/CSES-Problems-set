# 1676 - Road Construction

We solve the problem with the union-find structure. We maintain the number of
distinct components and the size of the largest component. When constructing
a new road between two cities $a$ and $b$, we first check if they are already
in the same component. If they are not, we merge the corresponding components,
decrease the number of distinct components by one and check if the newly
created component is larger than the previous largest component.

The time complexity of the solution is $O(n + m \alpha(n))$, where $\alpha(n)$
is the inverse Ackermann function.

```cpp
#include <algorithm>
#include <iostream>
#include <numeric>

using namespace std;
const int N = 100001;

int sz[N];
int link[N];

int find(int x) {
    if (link[x] == x) {
        return x;
    }
    return link[x] = find(link[x]);
}

bool same(int x, int y) {
    return find(x) == find(y);
}

void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (sz[x] < sz[y]) {
        swap(x, y);
    }
    sz[x] += sz[y];
    link[y] = x;
}

int main() {
    int n, m;
    cin >> n >> m;

    fill(sz, sz + n + 1, 1);
    iota(link, link + n + 1, 0);

    int n_components = n;
    int largest_size = 1;

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        if (!same(a, b)) {
            unite(a, b);
            --n_components;
            largest_size = max(sz[find(a)], largest_size);
        }
        cout << n_components << ' ' << largest_size << '\n';
    }
}
```

## References

* [CPHB (Competitive Programmer's Handbook)](http://cses.fi/book),
  Chapter 15.2
* [CP-Algorithms, Disjoint Set Union / Union Find](https://cp-algorithms.com/data_structures/disjoint_set_union.html)