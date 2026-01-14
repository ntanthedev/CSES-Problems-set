# 1725 - Dice Probability

We solve the problem using dynamic programming: $p[i][j]$ denotes the
probability of having sum $j$ after throwing a dice $i$ times.

As a base case $p[0][0]=1$, because the sum is certainly $0$ if there are no
throws. Then, when we know a value of $p[i][j]$, we go through the possible
throws whose outcomes are $k=1,2,\dots,6$. For each such throw, we increase
$p[i+1][j+k]$ by $p[i][j]/6$. Finally, we calculate the sum of probabilities
$p[n][i]$ where $i$ is between $a$ and $b$.

The solution works in $O(n^2)$ time.

```cpp
#include <iostream>
using namespace std;

const int N = 100;
double p[N + 1][6 * N + 1];

int main() {
    int n, a, b;
    cin >> n >> a >> b;

    p[0][0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = i; j <= 6 * i; j++) {
            for (int k = 1; k <= 6; k++) {
                p[i + 1][j + k] += p[i][j] / 6;
            }
        }
    }

    double answer = 0;
    for (int i = a; i <= b; i++) {
        answer += p[n][i];
    }
    cout.precision(6);
    cout << fixed << answer << "\n";
}
```