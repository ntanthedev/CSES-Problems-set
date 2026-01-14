# 1726 - Moving Robots

We assume that the rows and columns are numbered from $0$ to $N-1$ and the
robots are numbered from $0$ to $N^2-1$. The robot that starts at square $(i,j)$
has number $i \cdot N+j$. In this problem $N=8$ in each test.

We solve the problem using dynamic programming: $p[m][r][i][j]$ denotes the
probability that robot $r$ is in square $(i,j)$ after $m$ turns.

As base cases, $p[0][i \cdot N+j][i][j]=1$ for each square $(i,j)$. Then, when
we know the value of $p[m][r][i][j]$, we find the squares where robot $r$ can
move from square $(i,j)$. For each such square $(i',j')$, we increase the value
of $p[m+1][r][i'][j']$ by $p[m][r][i][j]/c$ where $c$ is the total number of
squares where the robot can move.

After that, we go through the grid and calculate, for each square $(i,j)$, the
probability that the square is empty after $k$ turns. We calculate the
probability using the formula

$$\prod\_{r=0}^{N^2-1} (1-p[k][r][i][j])$$

which requires that no robot is in the square after $k$ turns. Due to linearity
of expectation, the sum of all such probabilities equals the expected number of
empty squares after $k$ turns.

The solution works in $O(k N^4)$ time.

```cpp
#include <iostream>
#include <vector>
using namespace std;

const int N = 8;
const int K = 100;
double p[K + 1][N * N][N][N];

int main() {
    int k;
    cin >> k;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            p[0][i * N + j][i][j] = 1;
        }
    }

    for (int m = 0; m < k; m++) {
        for (int r = 0; r < N * N; r++) {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    vector<pair<int, int>> moves;
                    if (i > 0) moves.emplace_back(i - 1, j);
                    if (j > 0) moves.emplace_back(i, j - 1);
                    if (i + 1 < N) moves.emplace_back(i + 1, j);
                    if (j + 1 < N) moves.emplace_back(i, j + 1);
                    double add = p[m][r][i][j] / moves.size();
                    for (auto d : moves) {
                        p[m + 1][r][d.first][d.second] += add;
                    }
                }
            }
        }
    }

    double answer = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            double e = 1;
            for (int r = 0; r < N * N; r++) {
                e *= (1 - p[k][r][i][j]);
            }
            answer += e;
        }
    }
    cout.precision(6);
    cout << fixed << answer << "\n";
}
```