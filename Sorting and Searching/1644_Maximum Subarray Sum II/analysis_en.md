# 1644 - Maximum Subarray Sum II

Let $s(i)$ denote the prefix sum $x\_1+x\_2+\dots+x\_i$. Using this function, we can calculate the sum of any subarray as follows:
$$x\_j+x\_{j+1}+\dots+x\_i = s(i) - s(j-1)$$
To solve the problem, we go through the array and maintain a multiset of all prefix sums $s(k)$ where $i-b \le k \le i-a$ and $i$ is our current position. Then, the maximum sum of a subarray that ends at position $i$ is $s(i) - s(k')$ where $s(k')$ is the minimum prefix sum in the multiset.

The following code implements the above idea and works in $O(n \log n)$ time.

```cpp
#include <iostream>
#include <set>
#include <vector>
using namespace std;
using ll = long long;

int main() {
    int n, a, b;
    cin >> n >> a >> b;

    vector<ll> sums;
    sums.push_back(0);
    multiset<ll> order;

    ll sum = 0;
    ll answer = -1e18;

    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        sum += x;
        sums.push_back(sum);

        if (i >= a) {
            order.insert(sums[i - a]);
            answer = max(answer, sum - *order.begin());
        }

        if (i >= b) {
            order.erase(order.find(sums[i - b]));
        }
    }

    cout << answer << "\n";
}
```

We can also create a more efficient solution using a linear-time sliding window minimum algorithm instead of a multiset. The idea is to maintain an increasing sequence of values inside the window. The following code uses a deque structure and works in $O(n)$ time.

```cpp
#include <deque>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

int main() {
    int n, a, b;
    cin >> n >> a >> b;

    vector<ll> sums;
    sums.push_back(0);
    deque<ll> order;

    ll sum = 0;
    ll answer = -1e18;

    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        sum += x;
        sums.push_back(sum);

        if (i >= a) {
            while (!order.empty() && order.back() > sums[i - a]) {
                order.pop_back();
            }
            order.push_back(sums[i - a]);
            answer = max(answer, sum - order[0]);
        }

        if (i >= b) {
            if (order[0] == sums[i - b]) {
                order.pop_front();
            }
        }
    }

    cout << answer << "\n";
}
```

## References

* [Minimum stack / Minimum queue (CP-Algorithms)](https://cp-algorithms.com/data_structures/stack_queue_modification.html)