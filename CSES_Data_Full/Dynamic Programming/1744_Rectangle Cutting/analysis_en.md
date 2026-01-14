# 1744 - Rectangle Cutting

A greedy solution to this problem could always cut off a square from the
rectangle, by choosing the shorter side of the rectangle. However, this is not
necessarily optimal:

![counterexample](6e005441ab10fe7fca636271212d8f858064580a87e78a0bef552eed4c7656db)

Instead, we use dynamic programming to exhaustively check every possible move
and choose the optimal one.

The function $\gdef \m {{\mathrm{moves}}} \m(i, j)$ represents the minimum
number of moves to cut an $i \times j$ rectangle into squares.

If the rectangle is already a square, then $i=j$ and $\m(i, j)=0$.

Otherwise, find the optimum among all horizontal and vertical cuts:

$$\m(i, j) = \min
\begin{cases}
\min\_{x=1}^{i-1} (\m(x, j) + \m(i - x, j) + 1) \\[4pt]
\min\_{y=1}^{j-1} (\m(i, y) + \m(i, j - y) + 1)
\end{cases}$$

Considering the maximum of the two sides, $n=\max(a, b)$, the time complexity
of this solution is $O(n^3)$.

```cpp
#include <iostream>
#include <vector>
using namespace std;
const int INF = 1e9;

int main() {
    int a, b;
    cin >> a >> b;

    vector<vector<int>> moves(a + 1, vector<int>(b + 1));
    for (int i = 1; i <= a; ++i) {
        for (int j = 1; j <= b; ++j) {
            if (i == j) {
                moves[i][j] = 0;
            } else {
                moves[i][j] = INF;
                for (int x = 1; x < i; ++x) {
                    moves[i][j] =
                        min(moves[i][j], moves[x][j] + moves[i - x][j] + 1);
                }
                for (int y = 1; y < j; ++y) {
                    moves[i][j] =
                        min(moves[i][j], moves[i][y] + moves[i][j - y] + 1);
                }
            }
        }
    }

    cout << moves[a][b] << "\n";
}
```