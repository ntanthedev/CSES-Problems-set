# 3398 - Permutation Rounds

We can present the permutation as a set of cycles. For example, the permutation $[5,3,2,6,4,1,8,7]$ consists of the following cycles:

* $1 \rightarrow 5 \rightarrow 4 \rightarrow 6 \rightarrow 1$ (length $4$)
* $2 \rightarrow 3 \rightarrow 2$ (length $2$)
* $7 \rightarrow 8 \rightarrow 7$ (length $2$)

The answer to the problem is the least common multiple (lcm) of all cycle lengths. In the above permutation, the answer is $\textrm{lcm}(4,2,2)=4$.

The following solution determines all cycle lengths and finds the prime factorization of each cycle length. We calculate the lcm by going through all primes that appear in the cycle lengths. For each prime $x$, we multiply the result by $x^k$ where $x^k$ is the greatest power that divides any of the cycle lengths.

```cpp
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const int M = 1000000007;

int main() {
    int n;
    cin >> n;

    vector<int> order(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> order[i];
    }

    vector<int> max_count(n + 1);

    for (int i = 1; i <= n; i++) {
        if (order[i] == 0) {
            continue;
        }

        int pos = i;
        int length = 0;
        do {
            length++;
            int new_pos = order[pos];
            order[pos] = 0;
            pos = new_pos;
        } while (pos != i);

        for (int x = 2; x * x <= length; x++) {
            int count = 0;
            while (length % x == 0) {
                length /= x;
                count++;
            }
            max_count[x] = max(max_count[x], count);
        }
        if (!max_count[length]) {
            max_count[length] = 1;
        }
    }

    ll result = 1;
    for (int x = 2; x <= n; x++) {
        for (int i = 0; i < max_count[x]; i++) {
            result *= x;
            result %= M;
        }
    }
    cout << result << "\n";
}
```