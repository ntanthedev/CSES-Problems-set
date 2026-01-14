# 1092 - Two Sets

We can calculate the sum of numbers using the well-known formula
$$s = 1+2+\dots+n = \frac{n(n+1)}{2}.$$
If $s$ is odd, it is clearly not possible to solve the problem. However, if $s$ is even, we can always solve the problem using a greedy algorithm.

We go through the numbers from $n$ to $1$ and create two sets that both have sum $s/2$. We add a number $x$ to the first set if the sum of numbers in the first set after adding $x$ is at most $s/2$. Otherwise, we add $x$ to the second set. Finally, we have processed all numbers and both sets have sum $s/2$.

Why does the algorithm work? In fact, the algorithm can create any sum between $0$ and $1+2+\dots+n$ using the numbers $\{1,2,\dots,n\}$ and we can prove it as follows using induction.

Case $n=1$: We can clearly create both sums $0$ and $1$ using the algorithm.

Case $n=k$: We want to create a sum $a$ where $0 \le a \le 1+2+\dots+k$ using the numbers $\{1,2,\dots,k\}$. If $a \ge k$, we use $k$ in the sum and then create a sum $a'=a-k$ using the numbers $\{1,2,\dots,k-1\}$. Otherwise $a<k$ and we create a sum $a'=a$ using the numbers $\{1,2,\dots,k-1\}$. In both cases $0 \le a' \le 1+2+\dots+k-1$, so the algorithm works.

Since $s/2$ is between $0$ and $s$, we can use the algorithm to solve the problem.

```cpp
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

int main() {
    int n;
    cin >> n;

    ll s = (ll)n * (n + 1) / 2;

    if (s % 2 == 1) {
        cout << "NO\n";
        return 0;
    }
    s /= 2;

    vector<int> set1, set2;
    for (int x = n; x >= 1; x--) {
        if (s >= x) {
            s -= x;
            set1.push_back(x);
        } else {
            set2.push_back(x);
        }
    }

    cout << "YES\n";
    cout << set1.size() << "\n";
    for (auto x : set1) cout << x << " ";
    cout << "\n";
    cout << set2.size() << "\n";
    for (auto x : set2) cout << x << " ";
    cout << "\n";
}
```