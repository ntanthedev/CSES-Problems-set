# 2168 - Nested Ranges Check

We can solve this problem by using a clever way to sort the ranges, and it turns out that both the subproblems can be solved using the same idea.

Let us first focus on the first subproblem of finding ranges that contain some other range. We sort the ranges in increasing order by right endpoint, and secondarily in decreasing order by left endpoint. Then we go through the ranges and maintain a value $p$: the rightmost position of a left endpoint. A range $[x,y]$ contains some other range exactly when $p \ge x$.

Then consider the second subproblem of finding ranges that are contained in other ranges. This time we sort the ranges in increasing order by left endpoint, and secondarily in decreasing order by right endpoint. We maintain a value $p$ that stores the rightmost position of a right endpoint, and some other range contains range $[x,y]$ exactly when $y \le p$.

In the following code we use the function `solve` for both subproblems. There is a small implementation trick: we use negative endpoints to easily sort the ranges secondarily in decreasing order.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int n;

void solve(vector<vector<int>> ranges) {
    vector<int> check(n + 1);

    int pos = 0;
    for (auto r : ranges) {
        if (pos >= -r[1]) {
            check[r[2]] = 1;
        }
        pos = max(pos, -r[1]);
    }

    for (int i = 1; i <= n; i++) {
        cout << check[i] << " ";
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