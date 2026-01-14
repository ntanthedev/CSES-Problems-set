# 1133 - Tree Distances II

Let us root the tree.
Rather than solving the whole problem, let us start by figuring out
how to calculate the answer for the root node.

We will do it recursively with a single DFS.
For each node $x$, we will store the size of the $x$'s subtree, $\texttt{subtree}\_x$, and the sum distances from $x$ to
each node in its subtree.

How much does the distance sum increase when we move from a node to its parent?
It is clear that the distance to each node in the subtree increases by exactly one. So, it suffices to take the sum of
children's distance sums and to that add the increase, i.e. the number of nodes in the subtree.

Now we know, for each node, the sum of distances to all nodes in its subtree.
In the case of the root, this is the final answer.

Now, let us do another pass of DFS from the root and, at the same time, keep track
of the answer for our current node.
The last thing to figure out is how much the answer
changes when we move from a node to one of its children (in the case of the picture, from $a$ to $b$).

![](0a80aa6a59f73d8e22b0773be762940c37b854360a4baa1d733073a49fdec369)

Let the answer for $a$ be $\texttt{ans}\_a$. There are $\texttt{subtree}\_b$ nodes in the subtree of $b$.
The red edge, from $a$ to $b$, partitions the graph into two parts: $a$'s part and $b$'s part.

Clearly, the individual distance to each node in $b$'s part of the graph
decreases by one. There are $\texttt{subtree}\_b$ of these nodes.

Similarly, the individual distance to each node in in $a$'s part increases by one.
There are $\left(n - \texttt{subtree}\_b\right)$ of these nodes.

Therefore, $b$'s answer is equal to
$\texttt{ans}\_a - \texttt{subtree}\_b + \left(n - \texttt{subtree}\_b\right)$.

```cpp
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const int N = 200001;

int n;
vector<int> g[N];
int subtree[N];  // subtree sizes

ll dfs(int node, int parent) {
    subtree[node] = 1;
    ll distance_sum = 0;
    for (int child : g[node]) {
        if (child == parent) continue;
        distance_sum += dfs(child, node);
        subtree[node] += subtree[child];
    }
    distance_sum += subtree[node] - 1;
    return distance_sum;
}

ll ans[N];

void calc(int node, int parent) {
    for (int child : g[node]) {
        if (child == parent) continue;
        ans[child] = ans[node] - subtree[child] + (n - subtree[child]);
        calc(child, node);
    }
}

int main() {
    cin >> n;

    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    ans[1] = dfs(1, 1);
    calc(1, 1);

    for (int i = 1; i <= n; ++i) {
        cout << ans[i] << ' ';
    }
    cout << '\n';
}
```