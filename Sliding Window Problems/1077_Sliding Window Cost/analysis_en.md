# 1077 - Sliding Window Cost

It is known that we can achieve a minimum cost inside a window if we set each
element to be the median of the window. Thus, the remaining problem is how to
efficiently calculate this for each window.

## Solution 1

The following code uses two multisets `left` and `right` that contain the values
inside a window: `left` contains the median and all element before the median,
and `right` contains all elements after the median. In addition, `left_sum` and
`right_sum` have the sum of elements in `left` and `right`.

When the window moves, we update the multisets and sums, and then we can
calculate the minimum total cost using them. Each window move requires a fixed
number of $O(\log n)$ operations, so the algorithm works in $O(n \log n)$ time.

```cpp
#include <iostream>
#include <set>
#include <vector>
using namespace std;
using ll = long long;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> x(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }

    multiset<int> left, right;
    ll left_sum = 0, right_sum = 0;

    auto fix = [&] {
        if (left.size() > right.size() + 1) {
            auto v = *left.rbegin();
            left_sum -= v;
            right_sum += v;
            right.insert(v);
            left.erase(left.find(v));
        }
        if (right.size() > left.size()) {
            auto v = *right.begin();
            right_sum -= v;
            left_sum += v;
            left.insert(v);
            right.erase(right.find(v));
        }
    };

    auto add = [&](int v) {
        if (!left.empty() && *left.rbegin() > v) {
            left.insert(v);
            left_sum += v;
        } else {
            right.insert(v);
            right_sum += v;
        }
        fix();
    };

    auto rem = [&](int v) {
        if (*left.rbegin() >= v) {
            left.erase(left.find(v));
            left_sum -= v;
        } else {
            right.erase(right.find(v));
            right_sum -= v;
        }
        fix();
    };

    auto cost = [&] {
        ll median = *left.rbegin();
        ll left_cost = left.size() * median - left_sum;
        ll right_cost = right_sum - right.size() * median;
        return left_cost + right_cost;
    };

    for (int i = 0; i < n; i++) {
        add(x[i]);
        if (i >= k) {
            rem(x[i - k]);
        }
        if (i >= k - 1) {
            cout << cost() << " ";
        }
    }
    cout << "\n";
}
```

## Solution 2

Another way to solve the problem is to use segment trees. We first compress the
input values so that they are in the range $[0, n - 1]$. After that, we maintain
two segment trees: `tree` maintains the count of each value and `sum_tree`
maintains the sum of values.

We find the position of the median using `tree` and the sum of values before
and after the median using `sum_tree`. Each window move requires a constant
number of tree operations, so the algorithm works in $O(n \log n)$ time.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

const int N = 1 << 18;
int tree[N * 2];
ll sum_tree[N * 2];

// Adds x to position k in tree.
// Adds y to position k in sum_tree.
void change(int k, int x, int y) {
    k += N;
    while (k > 0) {
        tree[k] += x;
        sum_tree[k] += y;
        k /= 2;
    }
}

// Returns the sum of the values in range [l, r] in sum_tree.
ll query(int l, int r) {
    l += N;
    r += N;
    ll sum = 0;
    while (l <= r) {
        if (l % 2 == 1) sum += sum_tree[l++];
        if (r % 2 == 0) sum += sum_tree[r--];
        l /= 2;
        r /= 2;
    }
    return sum;
}

// Returns the first position in tree where prefix sum is at least sum.
int search(int sum) {
    int s = 1;
    while (s < N) {
        if (tree[s * 2] >= sum) {
            s = s * 2;
        } else {
            sum -= tree[s * 2];
            s = s * 2 + 1;
        }
    }
    return s - N;
}

int main() {
    int n, k;
    cin >> n >> k;

    vector<pair<int, int>> pairs;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        pairs.emplace_back(x, i);
    }

    sort(pairs.begin(), pairs.end());
    vector<int> pos(n);
    for (int i = 0; i < n; i++) {
        pos[pairs[i].second] = i;
    }

    for (int i = 0; i < n; i++) {
        change(pos[i], 1, pairs[pos[i]].first);

        if (i >= k) {
            change(pos[i - k], -1, -pairs[pos[i - k]].first);
        }

        if (i >= k - 1) {
            int m = (k + 1) / 2;
            int p = search(m);
            int median = pairs[p].first;

            ll left_cost = ll(m) * median - query(0, p);
            ll right_cost = query(p + 1, n) - ll(k - m) * median;

            cout << left_cost + right_cost << " ";
        }
    }
    cout << "\n";
}
```