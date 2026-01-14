# 1637 - Removing Digits

A straightforward dynamic programming solution to this problem is to iterate
through all the digits in a number and choose the one which results in the
least total steps.

The expression `number % 10` gives the last digit of the number, and the digits
can be shifted to the right with integer division. This is repeated until the
number is zero.

```cpp
#include <iostream>
#include <vector>
using namespace std;
const int INF = 1e9;

int main() {
    int n;
    cin >> n;

    vector<int> steps(n + 1);
    steps[0] = 0;
    for (int i = 1; i <= n; ++i) {
        steps[i] = INF;
        int number = i;
        while (number) {
            int digit = number % 10;
            steps[i] = min(steps[i], steps[i - digit] + 1);
            number /= 10;
        }
    }

    cout << steps[n] << "\n";
}
```

## Alternative greedy solution

It turns out that always subtracting the largest digit leads to an optimal
solution.

This makes for a simpler code, but the proof requires some thought.

### Proof of correctness

Let $\mathrm{steps}(n)$ be the minimum amount of steps needed to reach $0$ when
starting from $n$.

We will show that the function is non-decreasing. That is, for every positive
integer $n$, it holds that $\mathrm{steps}(n) \ge \mathrm{steps}(n-1)$.

If the function is non-decreasing on the interval $[0, n-1]$, then it is always
optimal to subtract the largest digit from $n$, because the total number of
steps will be $\mathrm{steps}(n-d) + 1$ where $d$ is the chosen digit. This
would also mean that the greedy strategy is optimal.

The function is indeed non-decreasing for $n\in[0, 1]$ since
$\mathrm{steps}(0)=0$ and $\mathrm{steps}(1)=1$.

The proof is completed by induction. Assume that the function is non-decreasing
on the interval $[0, n-1]$ for some $n \ge 2$. The induction hypothesis is that
$\mathrm{steps}(n) \ge \mathrm{steps}(n-1)$ and so the function is
non-decreasing on the interval $[0, n]$ as well.

When comparing the digits of $n-1$ and $n$, notice that the maximum digit of
$n$ can be at most one greater than that of $n-1$.

Let $d$ be the maximum digit in $n-1$. This means that

$$\mathrm{steps}(n-1) = \mathrm{steps}(n-1-d)+1.$$

On the other hand, the maximum digit of $n$ is at most $d+1$, so
$\mathrm{steps}(n)$ is at least

$$\mathrm{steps}(n-(d+1))+1=\mathrm{steps}(n-1-d)+1.$$

This is the same as $\mathrm{steps}(n-1)$, confirming the induction
hypothesis.

```cpp
#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    int steps = 0;
    while (n) {
        int number = n;
        int max_digit = 0;
        while (number) {
            int digit = number % 10;
            max_digit = max(max_digit, digit);
            number /= 10;
        }
        n -= max_digit;
        steps++;
    }

    cout << steps << "\n";
}
```