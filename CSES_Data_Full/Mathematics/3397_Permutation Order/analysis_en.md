# 3397 - Permutation Order

# First task

We are given $n$ and $k$, and our task is to find $p(n,k)$, i.e., the $k$th permutation (in lexicographical order) of $1 \dots n$.

If $k$ is between $1$ and $(n-1)!$, the first number is $1$. If $k$ is between $(n-1)!+1$ and $2(n-1)!$, the first number is $2$. In general, the first number is
$$\left\lfloor \frac{k-1}{(n-1)!} \right\rfloor + 1.$$

We can find the numbers one by one using the same idea. After every step, we remove the chosen number from the list of possible numbers.

# Second task

We are given $n$ and $p(n,k)$ and our task is to find $k$.

Initially $k=1$. If the first number is $1$, we don't change $k$. If the first number is $2$, we increase $k$ by $(n-1)!$. If the first number is $3$, we increase $k$ by $2(n-1)!$. In general, if the first number is $x$, we increase $k$ by
$$(x-1)(n-1)!.$$

We can process the numbers one by one and increase the value of $k$ using the same idea. After every step, we remove $x$ from the list of numbers.

```cpp
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;
using ll = long long;
const int N = 20;

int main() {
    int t;
    cin >> t;

    vector<ll> fact(N + 1);
    fact[0] = 1;
    for (int i = 1; i <= N; i++) {
        fact[i] = fact[i - 1] * i;
    }

    while (t--) {
        int op;
        cin >> op;

        int n;
        cin >> n;

        ll f = fact[n];
        vector<int> numbers(n);
        iota(numbers.begin(), numbers.end(), 1);

        if (op == 1) {
            ll k;
            cin >> k;
            k--;
            for (int i = 0; i < n; i++) {
                f /= n - i;
                cout << numbers[k / f] << " ";
                numbers.erase(numbers.begin() + (k / f));
                k %= f;
            }
            cout << "\n";
        }

        if (op == 2) {
            ll k = 1;
            for (int i = 0; i < n; i++) {
                int x;
                cin >> x;
                f /= n - i;
                auto it = find(numbers.begin(), numbers.end(), x);
                k += (it - numbers.begin()) * f;
                numbers.erase(it);
            }
            cout << k << "\n";
        }
    }
}
```