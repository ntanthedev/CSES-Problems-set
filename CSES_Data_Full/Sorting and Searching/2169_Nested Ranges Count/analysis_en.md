# 2169 - Nested Ranges Count

This problem is like the previous problem, but instead of just checking if a range contains another range, we have to count the number of ranges.

Also in this problem we can use the idea that is explained in the analysis of the previous problem. The only difference is that instead of maintaining a rightmost position of an endpoint, we create a policy-based indexed set that contains all the endpoints. Then we can use the function `order_of_key` to calculate the number of endpoints after some point.

Since policy-based sets can't be multisets, we need a small trick: instead of just storing endpoints, we store a pair of an endpoint and the index of the corresponding range.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

template <typename T>
using indexed_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

int n;

void solve(vector<vector<int>> ranges) {
    vector<int> count(n + 1);
    indexed_set<pair<int, int>> points;

    for (auto r : ranges) {
        count[r[2]] = points.size() - points.order_of_key({-r[1], 0});
        points.insert({-r[1], r[2]});
    }

    for (int i = 1; i <= n; i++) {
        cout << count[i] << " ";
    }
    cout << "\n";
}

int main() {
    cin >> n;

    vector<vector<int>> ranges1;
    vector<vector<int>> ranges2;

    for (int i = 1; i <= n; i++) {
        int x, y;
        cin >> x >> y;
        ranges1.push_back({y, -x, i});
        ranges2.push_back({x, -y, i});
    }

    sort(ranges1.begin(), ranges1.end());
    sort(ranges2.begin(), ranges2.end());

    solve(ranges1);
    solve(ranges2);
}
```