# 2169 - Đếm Đoạn Chứa Nhau

Bài này tương tự như bài trước, nhưng thay vì chỉ kiểm tra một đoạn có chứa đoạn khác hay không, ta phải đếm số lượng các đoạn.

Ở bài này ta cũng có thể dùng ý tưởng đã trình bày trong phân tích của bài trước. Điểm khác biệt duy nhất là thay vì duy trì vị trí tận cùng bên phải của một đầu mút, ta tạo một tập có chỉ số (indexed set) dựa trên chính sách (policy-based) chứa tất cả các đầu mút. Sau đó ta có thể dùng hàm `order_of_key` để tính số đầu mút sau một điểm nào đó.

Vì tập dựa trên chính sách không thể là đa tập (multiset), ta cần một thủ thuật nhỏ: thay vì chỉ lưu các đầu mút, ta lưu một cặp gồm đầu mút và chỉ số của đoạn tương ứng.

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
