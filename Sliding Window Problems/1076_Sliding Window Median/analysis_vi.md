# 1076 - Trung vị cửa sổ trượt

Một cách thuận tiện để giải bài toán này là duy trì một policy-based indexed set chứa các phần tử của mỗi cửa sổ. Sau đó, ta có thể sử dụng hàm `find_by_order` để tìm trung vị.

Lưu ý rằng mỗi phần tử trong indexed set phải là phân biệt, vì vậy ta lưu các cặp trong đó giá trị đầu tiên là phần tử và giá trị thứ hai là chỉ số của nó.

Thuật toán chạy trong $O(n \log n)$ thời gian vì ta thực hiện một số lượng hằng định các thao tác $O(\log n)$ cho mỗi phần tử.

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
