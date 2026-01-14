# 1076 - Sliding Window Median

A convenient way to solve the problem is to maintain a policy-based indexed set that contains the elements of each window. Then we can use the `find_by_order` function to find the median.

Note that each element in a indexed set has to be distinct, so we store pairs where the first value is the element and second value is its index.

The algorithm works in $O(n \log n)$ time because we perform a constant number of $O(\log n)$ operations for each element.

```cpp
#include <iostream>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

template <typename T>
using indexed_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> x(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }

    indexed_set<pair<int, int>> s;

    for (int i = 0; i < n; i++) {
        s.insert({x[i], i});
        if (i >= k) {
            s.erase({x[i - k], i - k});
        }
        if (i >= k - 1) {
            int median = s.find_by_order((k - 1) / 2)->first;
            cout << median << " ";
        }
    }
    cout << "\n";
}
```