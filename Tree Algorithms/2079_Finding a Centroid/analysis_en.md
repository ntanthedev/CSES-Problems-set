# 2079 - Finding a Centroid

## First approach

The problem becomes easier to solve when we root the tree arbitrarily. After
that, we calculate the size of the subtree of each node and the maximum subtree
size among the children of each node.

The arrays `sz` and `max_child` store the size of the
subtree of each node and the maximum subtree size among the children of each
node, respectively.

When we remove a node from the tree, a number of separate components will
remain. Throughout this analysis we will refer to the component corresponding to
the parent of a node as the *parent's component* of the node.

Note that the parent's component can be the largest of the remaining components.
The array `max_child` does not take this case into account and thus, it needs to
be checked separately. The size of the parent's component is equal to
$n-$`sz`$[i]$ for any node $i$ as each of the $n$ nodes of the tree is part
of either the subtree of $i$ or the parent's component.

```cpp
#include <iostream>
#include <vector>
using namespace std;

const int N = 200001;
vector<int> g[N];
int sz[N], max_child[N];

void dfs(int node, int parent) {
    sz[node] = 1;
    for (int child : g[node]) {
        if (child == parent) continue;
        dfs(child, node);
        sz[node] += sz[child];
        max_child[node] = max(max_child[node], sz[child]);
    }
}

int main() {
    int n;
    cin >> n;

    for (int i = 1; i <= n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    dfs(1, -1);

    for (int i = 1; i <= n; ++i) {
        if (max(max_child[i], n - sz[i]) <= n / 2) {
            cout << i << '\n';
            break;
        }
    }
}
```

## Second approach

There exists a recursive approach for this problem where we keep track of the
size of the parent's component as we traverse the tree.

This approach is useful in the case that we do not know the exact set of nodes
the tree consists of as is sometimes the case when constructing a centroid
decomposition of the tree.

```cpp
#include <iostream>
#include <vector>
using namespace std;

const int N = 200001;
vector<int> g[N];
int sz[N], max_child[N];
int n;

void dfs(int node, int parent) {
    sz[node] = 1;
    for (int child : g[node]) {
        if (child == parent) continue;
        dfs(child, node);
        sz[node] += sz[child];
        max_child[node] = max(max_child[node], sz[child]);
    }
}

int centroid(int node, int parent, int above) {
    if (max(above, max_child[node]) <= n / 2) {
        return node;
    }
    for (int child : g[node]) {
        if (child == parent) continue;
        int ans = centroid(child, node, above + sz[node] - sz[child]);
        if (ans != -1) return ans;
    }
    return -1;
}

int main() {
    cin >> n;

    for (int i = 1; i <= n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    dfs(1, -1);

    cout << centroid(1, -1, 0) << '\n';
}
```

## Third approach

The previous solution can be improved even further. Turns out a greedy approach
works.

First, we root the tree. Then, starting from the root, we recursively move to a
child with a subtree size larger than $\left \lfloor{\frac n 2}\right \rfloor$.
When we arrive to a node which has no such children, the node is a centroid of
the tree.

### Proof for the algorithm

As the size of the current subtree decreases with each move, the traversal will
eventually arrive to a node with no child with a subtree size larger than $\left
\lfloor{\frac n 2}\right \rfloor$. We just have to prove that the found node is,
in fact, a centroid of the tree.

We know that no child of the chosen node has a child with a subtree size too
large, which means that the only case in which the chosen node is not a centroid
is when the size of the parent's component is too large.

![](6dc9d2874f0ad14006e9b43a6f0bfefe30d702bc57b82cfd39e932b3d2c20917)

If the traversal consists of only one node, then the root is a centroid node as
it does not have a parent. Otherwise, let us analyze the very last step of the
search, moving from the previous node to the last node (in the figure from $2$
to $4$).

Let the subtree size of the last node ($4$ in the figure) be $S$. Then, the
size of the parent's component has a size of $n-S$. By definition, we know that
$S>\left \lfloor{\frac n 2}\right \rfloor$. From these pieces of information, we
can work out that

$$S>\left \lfloor{\frac n 2}\right \rfloor \iff n-S < n -
\left \lfloor{\frac n 2}\right \rfloor
\implies
n-S\le\left \lfloor{\frac n 2}\right \rfloor.\ \square$$

```cpp
#include <iostream>
#include <vector>
using namespace std;

const int N = 200001;
vector<int> g[N];
int sz[N];
int n;

void dfs(int node, int parent) {
    sz[node] = 1;
    for (int child : g[node]) {
        if (child == parent) continue;
        dfs(child, node);
        sz[node] += sz[child];
    }
}

int centroid(int node, int parent) {
    for (int child : g[node]) {
        if (child != parent && sz[child] > n / 2) {
            return centroid(child, node);
        }
    }
    return node;
}

int main() {
    cin >> n;

    for (int i = 1; i <= n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    dfs(1, -1);

    cout << centroid(1, -1) << '\n';
}
```