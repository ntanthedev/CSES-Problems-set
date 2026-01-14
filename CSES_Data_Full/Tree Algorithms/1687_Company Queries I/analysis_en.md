# 1687 - Company Queries I

## First approach

This problem can be solved with a technique called *binary lifting*.

For each node, we will precalculate the answers for jumps of sizes $2^k$, where $2^k\le n$.
The next layer of jumps can be constructed in linear time from the previous one.
For example, to calculate jumps of length two, we do two consecutive jumps of length one.

There are $O(\log n)$ of these jumps for each node
which means that the precalculation takes $O(n \log n)$ time and space.

When answering queries, the binary representation of $k$ tells us which jumps to make.
Answering a single query takes $O(\log(n))$ time which means
that answering all queries takes in total $O(q\log n)$ time.

```cpp
#include <iostream>
using namespace std;

const int N = 200001;

int jmp[N][20];

int main() {
    int n, q;

    cin >> n >> q;

    for (int i = 2; i <= n; ++i) {
        cin >> jmp[i][0];
    }

    for (int j = 0; (1 << j) <= n; ++j) {
        for (int i = 1; i <= n; ++i) {
            jmp[i][j + 1] = jmp[jmp[i][j]][j];
        }
    }

    for (int qi = 0; qi < q; ++qi) {
        int x, k;
        cin >> x >> k;

        for (int j = 19; j >= 0; --j) {
            if (k >> j & 1) {
                x = jmp[x][j];
            }
        }

        cout << (x ? x : -1) << '\n';
    }
}
```

## Second approach

To achieve better space complexity one could one heavy-light decomposition.
Here, though, I would like to present another solution, one using
a lesser-known technique sometimes called *jump pointers*.

This technique was first introduced in a 1983 paper by Eugene W. Myers titled
*An applicative random-access stack*. In 2020, it was popularized among
the competitive programmers by the *Codeforces* user Urbanowicz through
his blog post "Binary Lifting, No Memory Wasted".

The improved space complexity of $O(n)$ comes from the fact that
we store only one jump for each node rather than $O(\log n)$ jumps.
These jumps are constructed in a special way. Hopefully, you can make out
the general pattern from the following picture.

![](333be7d0375a2686f8b85fe4fe5974aefcbb44b12e89661512b9b8e81fb1462d)

The idea is to make a longer jump when the two consecutive jumps from the parent node have the same length.
Done this way, the jumps will have lengths of $1, 3, 7\dots$ i.e. $2^n-1$.
The exponential nature of the jump lengths makes the time complexity for answering a query logarithmic.
Full proof of this can be found in the paper.

An implementation using the technique of *jump pointers* can be found below.
For each node, we need to store:

* the depth of the node
* the parent of the node
* the node where we land when we jump from the node
* the size of the jump.

When answering a query, we should greedily take the longest possible jump which does not jump over our destination.

```cpp
#include <iostream>
#include <vector>
using namespace std;

const int N = 200001;

int parent[N];
int depth[N];
int jump[N];
int jump_size[N];
vector<int> g[N];

void dfs(int node) {
    for (int child : g[node]) {
        depth[child] = depth[node] + 1;
        parent[child] = node;
        jump[child] = node;
        jump_size[child] = 1;
        if (jump[node] && jump[jump[node]] &&
            jump_size[node] == jump_size[jump[node]]) {
            jump[child] = jump[jump[node]];
            jump_size[child] = jump_size[node] * 2 + 1;
        }
        dfs(child);
    }
}

int make_jumps(int x, int k) {
    if (depth[x] < k) {
        return -1;
    }
    while (k) {
        if (jump_size[x] <= k) {
            k -= jump_size[x];
            x = jump[x];
        } else {
            k--;
            x = parent[x];
        }
    }
    return x;
}

int main() {
    int n, q;

    cin >> n >> q;

    for (int i = 2; i <= n; ++i) {
        int p;
        cin >> p;
        g[p].push_back(i);
    }

    dfs(1);

    for (int qi = 0; qi < q; ++qi) {
        int x, k;
        cin >> x >> k;

        cout << make_jumps(x, k) << '\n';
    }
}
```

You can learn more about the technique and its various applications from the blog
post or the original paper both of which are linked below.

### Side note

The original paper only proved that the algorithm works for one-dimensional arrays – not trees.
In the case of trees, the jump pattern will spread out to leaves and work in exactly the same
way as for arrays.

### Further reading

* [Eugene W. Myers,
  *An applicative random-access stack*,
  Information Processing Letters,
  Volume 17, Issue 5,
  1983.](https://www.sciencedirect.com/science/article/abs/pii/0020019083901060)
* [Codeforces, "Binary Lifting, No Memory Wasted" By Urbanowicz](https://codeforces.com/blog/entry/74847)