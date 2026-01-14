# 2428 - Distinct Values Subarrays II

We go through the array from left to right and calculate at each position $i$ the number of valid subarrays that end at position $i$.

We maintain a data structure `rank` that contains pairs of the form $(p, x)$: we have last seen element $x$ at position $p$. We also use a data structure `prev` that stores the previous position of each element. We make sure that `rank` has at most $k+1$ pairs and if it has more pairs, we remove the pair whose $p$ is smallest.

If `rank` has at most $k$ pairs, then all subarrays that end at position $i$ are valid. Otherwise, `rank` has $k+1$ pairs and the first pair gives us the last position that does not belong to a valid subarray.

We can update both data structures in $O(\log n)$ time, so the algorithm works in $O(n \log n)$ time.

```cpp
#include <iostream>
#include <map>
#include <set>
using namespace std;
using ll = long long;

int main() {
    int n, k;
    cin >> n >> k;

    map<int, int> prev;
    set<pair<int, int>> rank;
    ll count = 0;

    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;

        rank.erase({prev[x], x});
        rank.insert({i, x});
        prev[x] = i;

        if (rank.size() > k + 1) {
            rank.erase(rank.begin());
        }

        if (rank.size() <= k) {
            count += i;
        } else {
            count += i - rank.begin()->first;
        }
    }

    cout << count << "\n";
}
```