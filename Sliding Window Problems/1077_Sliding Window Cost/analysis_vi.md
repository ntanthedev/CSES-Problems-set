# 1077 - Chi phí cửa sổ trượt

Ta biết rằng có thể đạt được chi phí nhỏ nhất trong một cửa sổ nếu ta đặt mỗi phần tử bằng trung vị của cửa sổ đó. Do đó, bài toán còn lại là làm thế nào để tính toán điều này một cách hiệu quả cho mỗi cửa sổ.

## Cách giải 1

Đoạn mã sau sử dụng hai multiset `left` và `right` chứa các giá trị trong một cửa sổ: `left` chứa trung vị và tất cả các phần tử đứng trước trung vị, còn `right` chứa tất cả các phần tử đứng sau trung vị. Ngoài ra, `left_sum` và `right_sum` lưu tổng các phần tử trong `left` và `right`.

Khi cửa sổ di chuyển, ta cập nhật các multiset và tổng, sau đó có thể tính tổng chi phí nhỏ nhất bằng cách sử dụng chúng. Mỗi lần di chuyển cửa sổ cần một số lượng hằng định các thao tác $O(\log n)$, do đó thuật toán chạy trong $O(n \log n)$ thời gian.

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

## Cách giải 2

Một cách khác để giải bài toán là sử dụng cây phân đoạn. Đầu tiên, ta nén các giá trị đầu vào để chúng nằm trong khoảng $[0, n - 1]$. Sau đó, ta duy trì hai cây phân đoạn: `tree` lưu số lượng của mỗi giá trị và `sum_tree` lưu tổng các giá trị.

Ta tìm vị trí của trung vị bằng `tree` và tổng các giá trị trước và sau trung vị bằng `sum_tree`. Mỗi lần di chuyển cửa sổ cần một số lượng hằng định các thao tác trên cây, do đó thuật toán chạy trong $O(n \log n)$ thời gian.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

const int N = 1 << 18;
int tree[N * 2];
ll sum_tree[N * 2];

// Thêm x vào vị trí k trong tree.
// Thêm y vào vị trí k trong sum_tree.
void change(int k, int x, int y) {
    k += N;
    while (k > 0) {
        tree[k] += x;
        sum_tree[k] += y;
        k /= 2;
    }
}

// Trả về tổng các giá trị trong đoạn [l, r] của sum_tree.
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

// Trả về vị trí đầu tiên trong tree có tổng tiền tố ít nhất là sum.
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
