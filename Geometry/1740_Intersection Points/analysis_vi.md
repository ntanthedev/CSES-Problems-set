# 1740 - Điểm Giao Nhau

Bài toán này có thể được giải bằng thuật toán quét dòng (sweep line). Ta sẽ quét qua các tọa độ $x$ theo thứ tự tăng dần, và đồng thời duy trì các đoạn thẳng nằm ngang đang hoạt động trong một cây phân đoạn (segment tree). Cây phân đoạn cho phép ta truy vấn số lượng điểm giao nhau của một đoạn thẳng dọc.

Ta sẽ nén các tọa độ $y$ về khoảng $[0, 2n)$. Điều này cho phép ta xây dựng một cây phân đoạn có kích thước $O(n)$. Thuật toán có độ phức tạp thời gian $O(n\log n)$ vì mỗi sự kiện trong số $O(n)$ sự kiện tương ứng với một truy vấn cây phân đoạn mất $O(\log n)$ thời gian.

```cpp
#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>
using namespace std;
using ll = long long;

// Cấu trúc dữ liệu cây phân đoạn
//  - Hỗ trợ thay đổi giá trị đơn lẻ và truy vấn tổng trên đoạn.
struct Tree {
    int n;
    vector<int> tree;

    Tree(int k) {
        n = 1;
        while (n < k) n *= 2;
        tree.assign(n * 2, 0);
    }

    // Thêm x vào vị trí k.
    void add(int k, int x) {
        k += n;
        tree[k] += x;
        while (k > 1) {
            k /= 2;
            tree[k] = tree[k * 2] + tree[k * 2 + 1];
        }
    }

    // Trả về tổng các giá trị trên đoạn [l, r].
    int query(int l, int r) {
        int sum = 0;
        for (l += n, r += n; l <= r; l /= 2, r /= 2) {
            if (l % 2 == 1) sum += tree[l++];
            if (r % 2 == 0) sum += tree[r--];
        }
        return sum;
    }
};

// Các loại sự kiện
enum { QUERY, ADD, REMOVE };

int main() {
    int n;
    cin >> n;

    vector<int> y_values;
    vector<tuple<int, int, int, int>> events;

    for (int i = 0; i < n; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        y_values.push_back(y1);
        y_values.push_back(y2);

        if (y1 == y2) {
            events.emplace_back(x1, ADD, y1, y2);
            events.emplace_back(x2, REMOVE, y1, y2);
        } else {
            events.emplace_back(x1, QUERY, y1, y2);
        }
    }

    sort(events.begin(), events.end());
    sort(y_values.begin(), y_values.end());
    y_values.erase(unique(y_values.begin(), y_values.end()), y_values.end());

    auto index = [&](int y) {
        auto it = lower_bound(y_values.begin(), y_values.end(), y);
        return distance(y_values.begin(), it);
    };

    Tree tree(y_values.size());
    ll ans = 0;

    for (auto [x, type, y1, y2] : events) {
        y1 = index(y1);
        y2 = index(y2);
        if (type == ADD) {
            tree.add(y1, 1);
        } else if (type == REMOVE) {
            tree.add(y1, -1);
        } else {
            ans += tree.query(y1, y2);
        }
    }

    cout << ans << '\n';
}
```
