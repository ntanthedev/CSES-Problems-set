# 1093 - Two Sets II

The problem can be equivalently stated as finding the number of subsets among
$\{1, \dots, n\}$ that sum to half of the total sum, which is $\frac
{n(n+1)}{4}$. Complement sets should not be counted twice, however.

If half of the total is not an integer, then there are no solutions. Otherwise
we use dynamic programming to find the answer.

Define the function $\mathrm{sets}(x, s)$ as the number of subsets of $\{1,
\dots, x\}$ that have sum equal to $s$.

When considering the number $x$, we can either choose it in the subset, in which
case smaller numbers have to form the sum $s-x$, or not, so the smaller numbers
have to form the whole sum $s$.

$$\mathrm{sets}(x, s) = \mathrm{sets}(x-1, s) + \mathrm{sets}(x-1, s-x)$$

As the base case we set that only the sum $0$ is can be formed from an empty
set.

$$\mathrm{sets}(0, s) = \begin{cases}
1 & \text{if } s = 0
0 & \text{otherwise}
\end{cases}$$

The answer is found at $\mathrm{sets}(n-1, h)$, where $h$ is half the total sum.
The element $n$ is not considered in order to differentiate complement sets from
each other and avoid counting them twice. A one-dimensional DP array is
sufficient because the recursion only references $\mathrm{sets}$ at $x-1$, the
number considered previously.

The time complexity of this solution is $O(n^3)$. Half of the total sum is
$O(n^2)$ and $O(n)$ different numbers are considered.

```cpp
#include <iostream>
using namespace std;
const int N = 500 * 501 / 4;
const int M = 1000000007;

int sets[N + 1];

int main() {
    int n;
    cin >> n;

    int total = n * (n + 1) / 2;
    if (total % 2 != 0) {
        cout << 0 << endl;
        return 0;
    }
    int half = total / 2;

    sets[0] = 1;
    for (int x = 1; x < n; ++x) {
        for (int s = half; s - x >= 0; --s) {
            sets[s] = (sets[s] + sets[s - x]) % M;
        }
    }

    cout << sets[half] << endl;
}
```