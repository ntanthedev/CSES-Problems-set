# 1739 - Forest Queries II

This problem can be solved with a *2D segment tree*. In a *2D segment tree*,
each node contains a regular segment tree.

We query $O(\log n)$ nodes in the top level tree and answering each of
these queries in a second level tree takes $O(\log n)$ time. Thus,
answering a single query takes $O(\log^2 n)$ time.

The total time complexity is $O((n+q)\log^2n)$.

The tree consumes $O(n^2)$ memory in total as each of the
$O(n)$ nodes in the top level tree consume $O(n)$ memory.

```cpp
#include <iostream>
using namespace std;

const int TREE_SIZE = 1 << 10;
int trees[TREE_SIZE * 2][TREE_SIZE * 2];

// Adds d to the position x in the segment tree `tree`.
void add(int *tree, int x, int d) {
    x += TREE_SIZE;
    while (x > 0) {
        tree[x] += d;
        x /= 2;
    }
}

// Adds d to the position (i, j).
void add(int y, int x, int d) {
    y += TREE_SIZE;
    while (y > 0) {
        add(trees[y], x, d);
        y /= 2;
    }
}

// Returns the sum of value in range [x1, x2] in `tree`.
int query(int *tree, int x1, int x2) {
    x1 += TREE_SIZE;
    x2 += TREE_SIZE;
    int sum = 0;
    while (x1 <= x2) {
        if (x1 % 2 == 1) sum += tree[x1++];
        if (x2 % 2 == 0) sum += tree[x2--];
        x1 /= 2;
        x2 /= 2;
    }
    return sum;
}

// Returns the sum of value in the rectangle [y1, y2] x [x1, x2]
int query(int y1, int y2, int x1, int x2) {
    y1 += TREE_SIZE;
    y2 += TREE_SIZE;
    int sum = 0;
    while (y1 <= y2) {
        if (y1 % 2 == 1) sum += query(trees[y1++], x1, x2);
        if (y2 % 2 == 0) sum += query(trees[y2--], x1, x2);
        y1 /= 2;
        y2 /= 2;
    }
    return sum;
}

const int N = 1001;
int forest[N][N];

int main() {
    int n, q;
    cin >> n >> q;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            char c;
            cin >> c;
            if (c == '*') {
                forest[i][j] = 1;
                add(i, j, 1);
            }
        }
    }

    for (int qi = 0; qi < q; ++qi) {
        int t;
        cin >> t;
        if (t == 1) {
            int i, j;
            cin >> i >> j;
            if (forest[i][j]) {
                add(i, j, -1);
                forest[i][j] = 0;
            } else {
                add(i, j, 1);
                forest[i][j] = 1;
            }
        } else {
            int y1, x1, y2, x2;
            cin >> y1 >> x1 >> y2 >> x2;
            cout << query(y1, y2, x1, x2) << '\n';
        }
    }
}
```