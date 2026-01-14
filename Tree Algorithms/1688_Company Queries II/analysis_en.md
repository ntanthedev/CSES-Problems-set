# 1688 - Company Queries II

The problem of the finding the LCA (lowest common ancestor) of two nodes in a tree is
one of the most important tree problems in competitive programming.
That is why it is worth discussing a few different approaches to
this essential problem.

## First approach: Binary lifting

The first approach is based on a technique called *binary lifting*.
First, we construct a jump table that can answer queries of the form
"which node is $2^k$ nodes higher than node $x$?" in $O(1)$
time.

It is not clear how to answer LCA queries once the jump table has been constructed.
The steps are as follows.

First, take the node which is further away from the root and
lift it so that it is as far from the root as the second node is.

Now that the nodes are on the same 'level', we should lift them both
simultaneously. Turns out that a greedy algorithm works here:
we lift the nodes as high as possible as long as the two pointers
point to two distinct nodes.

Constructing the jump table takes $O(n\log n)$ time.
Answering a single query takes $O(\log n)$ time which means
that answering all queries takes in total $O(q\log n)$ time.
Thus, the total time complexity of the solution is $O(n\log n+q\log n)$.

```cpp
#include <iostream>
#include <vector>
using namespace std;

const int N = 200000;
int jmp[N][20];
int depth[N];
vector<int> g[N];

void dfs(int node) {
    for (int child : g[node]) {
        depth[child] = depth[node] + 1;
        dfs(child);
    }
}

int lca(int a, int b) {
    if (depth[a] < depth[b]) {
        swap(a, b);
    }
    int depth_difference = depth[a] - depth[b];
    for (int j = 19; j >= 0; --j) {
        if ((1 << j) & depth_difference) {
            a = jmp[a][j];
        }
    }
    if (a == b) {
        return a;
    } else {
        for (int j = 19; j >= 0; --j) {
            if (jmp[a][j] != jmp[b][j]) {
                a = jmp[a][j];
                b = jmp[b][j];
            }
        }
        return jmp[a][0];
    }
}

int main() {
    int n, q;

    cin >> n >> q;

    for (int i = 1; i < n; ++i) {
        cin >> jmp[i][0];
        jmp[i][0]--;
        g[jmp[i][0]].push_back(i);
    }

    for (int j = 0; (1 << j) <= n; ++j) {
        for (int i = 0; i < n; ++i) {
            jmp[i][j + 1] = jmp[jmp[i][j]][j];
        }
    }

    dfs(0);

    for (int qi = 0; qi < q; ++qi) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        cout << lca(a, b) + 1 << '\n';
    }
}
```

### Resources for binary lifting

* [CP-Algorithms, *Lowest Common Ancestor - Binary Lifting*](https://cp-algorithms.com/graph/lca_binary_lifting.html)
* [CPHB (Competitive Programmer's Handbook)](http://cses.fi/book), Chapter 18

### Side note

[*Heavy-light decomposition*](https://codeforces.com/blog/entry/53170) or
the technique known as [*jump pointers*](https://codeforces.com/blog/entry/74847)
could be used to improve the space complexity of this solution to $O(n)$.

## Second approach: Euler tour

Another way to solve this problem is using a technique called *Euler tour*.
This technique is a based on a special array. This array is constructed
during the depth-first search traversal. Each time a node is visited,
it is added to the array. That is when the traversal first arrives
at the node, in-between visiting children and when the traversal
leaves the node.

![](3db66a4f519505ac0d96e65246625d03c3a8b26e790daa32ed50dbf73882f0a4)

For example, this array corresponds to the above picture.

![](5d1ec467300ee5c0c2dd62b3623057739394d6d9e67b45aa96f5083d9bca7cfe)

This array can be used to find the lowest common ancestor of two nodes.
We start by finding the positions where the nodes first
appear in the array. Then, the LCA corresponds to the
node with the minimum depth between these positions.
We have, thus, reduced the LCA problem to a RMQ (range minimum query)
problem.

We can answer the queries using, for example, a segment tree.

```cpp
#include <iostream>
#include <vector>
using namespace std;
const int INF = 1e9;

struct Tree {
    int n;
    vector<pair<int, int>> t;
    // Constructs the segment tree in linear time
    Tree(vector<pair<int, int>> &v) {
        n = 1;
        while (n <= (int)size(v)) {
            n *= 2;
        }
        t.resize(n * 2);
        for (int i = 0; i < (int)size(v); ++i) {
            t[n + i] = v[i];
        }
        for (int i = n - 1; i > 0; --i) {
            t[i] = min(t[i * 2], t[i * 2 + 1]);
        }
    }
    // Returns the minimum value in range [l, r]
    pair<int, int> query(int l, int r) {
        pair<int, int> ans{INF, INF};
        l += n;
        r += n;
        while (l <= r) {
            if (l % 2 == 1) ans = min(ans, t[l++]);
            if (r % 2 == 0) ans = min(ans, t[r--]);
            l /= 2;
            r /= 2;
        }
        return ans;
    }
};

const int N = 200000;
int depth[N];
vector<int> g[N];

void dfs(int node, vector<pair<int, int>> &tour) {
    tour.emplace_back(depth[node], node);
    for (int child : g[node]) {
        depth[child] = depth[node] + 1;
        dfs(child, tour);
        tour.emplace_back(depth[node], node);
    }
}

int main() {
    int n, q;

    cin >> n >> q;

    for (int i = 1; i < n; ++i) {
        int p;
        cin >> p;
        p--;
        g[p].push_back(i);
    }

    vector<pair<int, int>> tour;

    dfs(0, tour);

    vector<int> position(n, -1);

    for (int i = 0; i < (int)tour.size(); ++i) {
        int id = tour[i].second;
        if (position[id] < 0) {
            position[id] = i;
        }
    }

    Tree tree(tour);

    for (int qi = 0; qi < q; ++qi) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        a = position[a];
        b = position[b];
        if (b < a) {
            swap(a, b);
        }
        cout << tree.query(a, b).second + 1 << '\n';
    }
}
```

Constructing the array and the segment tree takes in total
$O(n)$ time.
A single segment tree query takes $O(\log n)$ time.
Thus, the total time complexity of the solution is $O(n+q\log n)$.

We may use a sparse table in place of the segment tree.

```cpp
#include <iostream>
#include <vector>
using namespace std;

struct RMQ {
    vector<vector<pair<int, int>>> table;
    // Constructs the sparse table in O(n log n)
    RMQ(vector<pair<int, int>> &v) : table{v} {
        for (int j = 0; (1 << j) < (int)size(v); ++j) {
            table.emplace_back(size(v) - (1 << j));
            for (int i = 0; i < (int)size(table.back()); ++i) {
                table[j + 1][i] = min(table[j][i], table[j][i + (1 << j)]);
            }
        }
    }
    pair<int, int> query(int l, int r) {
        int len = r - l + 1;
        int lvl = __lg(len);
        return min(table[lvl][l], table[lvl][r - (1 << lvl) + 1]);
    }
};

const int N = 200000;
int depth[N];
vector<int> g[N];

void dfs(int node, vector<pair<int, int>> &tour) {
    tour.emplace_back(depth[node], node);
    for (int child : g[node]) {
        depth[child] = depth[node] + 1;
        dfs(child, tour);
        tour.emplace_back(depth[node], node);
    }
}

int main() {
    int n, q;

    cin >> n >> q;

    for (int i = 1; i < n; ++i) {
        int p;
        cin >> p;
        p--;
        g[p].push_back(i);
    }

    vector<pair<int, int>> tour;

    dfs(0, tour);

    vector<int> position(n, -1);

    for (int i = 0; i < (int)tour.size(); ++i) {
        int id = tour[i].second;
        if (position[id] < 0) {
            position[id] = i;
        }
    }

    RMQ rmq(tour);

    for (int qi = 0; qi < q; ++qi) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        a = position[a];
        b = position[b];
        if (b < a) {
            swap(a, b);
        }
        cout << rmq.query(a, b).second + 1 << '\n';
    }
}
```

A sparse table has a construction time of $O(n\log n)$ and query
time of $O(1)$. Thus, the total time complexity of the
solution is $O(n\log n+q)$.

### Resources for Euler tour technique

* [CP-Algorithms, *Lowest Common Ancestor*](https://cp-algorithms.com/graph/lca.html)
* [CPHB (Competitive Programmer's Handbook)](http://cses.fi/book), Chapter 18

There actually exists a variant of the sparse table which can be built in
linear time. With such a data structure the asymptotically optimal time
complexity of $O(n + q)$ can be achieved.
More information can be found from the links below.

### Resources for the linear time RMQ data structure

* [Codeforces, *Range minimum query in O(1) with linear time construction* by brunomont](https://codeforces.com/blog/entry/78931)
* [Codeforces, *Simple rmq O(n)/O(1) method* by Allvik06Range](https://codeforces.com/blog/entry/92310)

## Third approach: *Farach-Colton and Bender Algorithm*

An implementation of an algorithm called the
*Farach-Colton and Bender Algorithm*
can be found below.
This algorithm has the asymptotically
optimal time complexity of
$O(n + q)$, that is,
the precalculation takes linear time
and answering a query can be done in constant time.

As the original paper (linked below) is clear and easy to understand,
the details for the algorithm will not be repeated here.

In outline, the algorithm works as follows:

1. First, the Euler tour array gets divided into chunks of
   $\frac{\log n}{2}$ elements.
2. A regular sparse table is built upon
   the array formed by the chunks.
   As there are $\frac{2n-1}{0.5\log n}$ blocks,
   the construction of the sparse table
   takes only
   $$O\left(\frac{2n-1}{
   0.5\log n}\log\left(\frac{2n-1}{
   0.5\log n}\right)\right)=O(n)$$
   time.
3. Answers for queries inside the blocks are all precalculated.
   A few clever tricks are used to reduce the precomputation
   time significantly.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int N = 200000;
vector<int> g[N];
int depth[N];

// This depth-first search constructs the Euler tour.
vector<int> tour;

void dfs(int node) {
    tour.push_back(node);
    for (int child : g[node]) {
        depth[child] = depth[node] + 1;
        dfs(child);
        tour.push_back(node);
    }
}

int main() {
    int n, q;
    cin >> n >> q;

    for (int i = 1; i < n; ++i) {
        int p;
        cin >> p;
        p--;
        g[p].push_back(i);
    }

    // Construct the tour using depth-first search.
    // This takes O(n) time.
    // The tour has n + (n - 1) elements as each node and each edge
    // contributes one element to the array.
    tour.reserve(n + n - 1);
    dfs(0);

    // A helper function works which works with standard library
    // functions like `std::min` and `std::min_element`.
    auto min_by_depth = [&](int a, int b) {
        return depth[a] < depth[b];
    };

    // Set block size equal to log(n) / 2.
    const int block_size = max(1, __lg(n) / 2);
    const int m = (2 * n - 1) / block_size;

    vector<int> block_min;
    block_min.reserve(m);
    vector<int> block_id;
    block_id.reserve(m);

    // This loop runs in O(n) time as each element is visited exactly two times.
    for (int i = 0; i < 2 * n - 1; i += block_size) {
        // Calculate the min value inside the block.
        int j = *min_element(tour.begin() + i,
                             tour.begin() + min(2 * n - 1, i + block_size),
                             min_by_depth);
        block_min.push_back(j);
        // Encode the block type.
        block_id.push_back(0);
        for (int j = 0; j < block_size - 1; ++j) {
            if (i + j + 1 < 2 * n - 1) {
                int diff = depth[tour[i + j + 1]] - depth[tour[i + j]];
                block_id.back() += (1 << j) * (diff == 1);
            } else {
                block_id.back() += 1 << j;
            }
        }
    }

    // Constructs a sparse table for the `block_min` array.
    // Takes O(n / (0.5 log n) * log(n / (0.5 log n))) = O(n) time.
    vector<vector<int>> block_sparse{block_min};
    for (int j = 0; (2 << j) <= m; ++j) {
        block_sparse.emplace_back(m - (1 << j));
        for (int i = 0; i + (2 << j) <= m; ++i) {
            int a = block_sparse[j][i];
            int b = block_sparse[j][i + (1 << j)];
            block_sparse[j + 1][i] = min(a, b, min_by_depth);
        }
    }

    // Returns the minimum value in the `block_min` array in range [l, r].
    // Works in O(1) time.
    // We'll assume here that the logarithm function, __lg, works in
    // constant time. To avoid calling the function, it is also possible to
    // precalculate the logarithms of all possible inputs without
    // changing the overall time complexity.
    auto block_sparse_query = [&](int l, int r) {
        int lvl = __lg(r - l + 1);
        int a = block_sparse[lvl][l];
        int b = block_sparse[lvl][r - (1 << lvl) + 1];
        return min(a, b, min_by_depth);
    };

    // This array stores the first position in which each node first appears in
    // the tour.
    vector<int> position(n, -1);
    for (auto &i : tour) {
        if (position[i] < 0) {
            position[i] = &i - tour.data();
        }
    }

    // This array is used for memoizing query answers for each
    // possible block and query combination.
    vector<vector<vector<int>>> blocks(1 << (block_size - 1));
    for (auto &t : blocks) {
        t.assign(block_size, vector<int>(block_size));
    }

    // Precalculates the answers for each possible block and query combination.
    // As the difference in depth between subsequent elements in the Euler tour
    // array is always either +1 or -1, there are in total
    // O(2^block_size) = O(2^{0.5 log n}) = O(sqrt(n))
    // distinct 'normalized' blocks.
    // This loop runs in O(sqrt(n) * log^2 n) = O(n) time.
    vector<int> block(block_size);
    for (int j = 0; j < (1 << (block_size - 1)); ++j) {
        for (int i = 0; i < block_size - 1; ++i) {
            block[i + 1] = block[i] + (j >> i & 1 ? +1 : -1);
        }
        for (int l = 0; l < block_size; ++l) {
            int min_node = l;
            for (int r = l; r < block_size; ++r) {
                if (block[r] < block[min_node]) {
                    min_node = r;
                }
                blocks[j][l][r] = min_node;
            }
        }
    }

    for (int qi = 0; qi < q; ++qi) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        a = position[a];
        b = position[b];
        if (b < a) {
            swap(a, b);
        }

        int ans = tour[a];

        // This helper function updates the answer if necessary.
        auto offer = [&](int node) {
            ans = min(ans, node, min_by_depth);
        };

        int ai = a / block_size;
        int bi = b / block_size;

        if (ai + 1 <= bi - 1) {
            offer(block_sparse_query(ai + 1, bi - 1));
        }

        a %= block_size;
        b %= block_size;

        if (ai == bi) {
            offer(tour[ai * block_size + blocks[block_id[ai]][a][b]]);
        } else {
            offer(tour[ai * block_size + blocks[block_id[ai]][a].back()]);
            offer(tour[bi * block_size + blocks[block_id[bi]][0][b]]);
        }

        cout << ans + 1 << '\n';
    }
}
```

### Side note

Although, this solution has a quite lot of precomputation – which causes
it to have a large constant factor – in practice, it is
surprisingly fast and in our testing, with a few optimizations,
it way noticeably faster than other better-known algorithms.

### Resources for the *Farach-Colton and Bender Algorithm*

* [Bender M.A., Farach-Colton M. (2000) "*The LCA Problem Revisited*" (PDF)](http://www.ics.uci.edu/~eppstein/261/BenFar-LCA-00.pdf).
  In: Gonnet G.H., Viola A. (eds) LATIN 2000: Theoretical Informatics. LATIN 2000. Lecture Notes in Computer Science, vol 1776. Springer, Berlin, Heidelberg.
* [CP-Algorithms, Lowest Common Ancestor - Farach-Colton and Bender Algorithm](https://cp-algorithms.com/graph/lca_farachcoltonbender.html)