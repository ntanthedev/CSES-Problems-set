# 1728 - Inversion Probability

We consider each index pair $(a,b)$ where $a<b$ and calculate the probability
that $x\_a > x\_b$ which corresponds to an inversion.

Using linearity of expectation, the sum of the probabilities equals the expected
number of inversions.

# C++ solution

Here is a C++ solution for the problem:

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> r(n);
    for (int i = 0; i < n; i++) {
        cin >> r[i];
    }

    double answer = 0;
    for (int a = 0; a < n; a++) {
        for (int b = a + 1; b < n; b++) {
            for (int x_a = 1; x_a <= r[a]; x_a++) {
                for (int x_b = 1; x_b <= min(x_a - 1, r[b]); x_b++) {
                    answer += 1.0 / (r[a] * r[b]);
                }
            }
        }
    }
    cout.precision(6);
    cout << fixed << answer << "\n";
}
```

Unfortunately, there are test cases where this solution fails due to precision issues.
In general, it is difficult to create a correct solution in C++.

# Python solution

In Python, we can use the `Fraction` class to avoid precision issues:

```cpp
from fractions import Fraction

n = int(input())
r = [int(x) for x in input().split(" ")]

answer = Fraction(0, 1)
for a in range(n):
    for b in range(a + 1, n):
        for x_a in range(1, r[a] + 1):
            for x_b in range(1, min(x_a, r[b] + 1)):
                answer += Fraction(1, r[a] * r[b])

answer = float(round(answer, 6))
print(f"{answer:06f}")
```

The above solution works correctly but it is too slow.
However, we can optimize the solution as follows:

```cpp
from fractions import Fraction

n = int(input())
r = [int(x) for x in input().split(" ")]

answer = Fraction(0, 1)
for a in range(n):
    for b in range(a + 1, n):
        count = 0
        for x_a in range(1, r[a] + 1):
            count += min(x_a - 1, r[b])
        answer += Fraction(count, r[a] * r[b])

answer = float(round(answer, 6))
print(f"{answer:06f}")
```

This solution works both correctly and efficiently enough.