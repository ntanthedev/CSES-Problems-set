# 2214 - Inverse Inversions

There is a straightforward greedy approach to this problem. However, it is not
immediately clear that it works.

Let us construct the answer from the beginning, one element at a time. We will
maintain two pointers: the lowest and highest numbers that have not been used,
and at each point, append either of them to the answer and update the
corresponding pointer.

Adding the lowest number yet will not form new inversions with any number
following it as all of them will be larger. Adding the highest number yet, on
the other hand, forms inversions with all of the numbers following it.

The greedy idea is to always pick the larger number while the inversion count
remains under $k$. Now, we have to prove that the algorithm always finds a
solution with exactly $k$ inversions. In total, we have $n-1$ choices: during
the first step, we are offered $n-1$ inversions, then $n-2$ and so on until we
are offered to take 1 inversion during the second-to-last step. The sum of the
amounts is $1+2+\dots+(n-1)=\frac{n(n-1)}2$, which means there are always enough
inversions to form $k$.

It can be proven that because we take the inversions greedily, the amount of
inversions needed is at all times at most $\frac {n(n-1)} 2$, where $n$
represents the number of elements remaining. It follows that when $n=1$, the
number of inversions needed is at most 0, thus equal to 0. The algorithm always
finds a solution whose inversion count is never larger $k$ nor is it lower than
$k$.

```cpp
#include <iostream>
using namespace std;
using ll = long long;

int main() {
    int n;
    ll k;
    cin >> n >> k;

    int l = 1, r = n;
    for (int i = 1; i <= n; ++i) {
        int left = n - i;  // The amount of numbers left.
        // As r is larger than all remaining numbers,
        // adding it will form inversions with each one of them.
        if (left <= k) {
            k -= left;
            cout << r-- << ' ';
        } else {
            cout << l++ << ' ';
        }
    }
    cout << '\n';
}
```