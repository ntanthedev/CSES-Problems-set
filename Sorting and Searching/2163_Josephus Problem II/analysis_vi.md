# 2163 - Josephus Problem II

Một cách thuận tiện để giải bài toán này là sử dụng cấu trúc dữ liệu tập chỉ mục (policy-based indexed set). Cấu trúc dữ liệu này có hàm `find_by_order` để tìm phần tử tại một chỉ mục cho trước trong tập đã được sắp xếp.

Ở mỗi bước, ta tính vị trí tiếp theo, in ra và xóa phần tử tại vị trí đó. Mỗi bước cần $O(\log n)$ thời gian, do đó thuật toán chạy trong $O(n \log n)$ thời gian.

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

    indexed_set<int> s;
    for (int i = 1; i <= n; i++) {
        s.insert(i);
    }

    int pos = 0;
    for (int i = 1; i <= n; i++) {
        pos = (pos + k) % (n - i + 1);
        auto it = s.find_by_order(pos);
        cout << *it << " ";
        s.erase(it);
    }
    cout << "\n";
}
```

## Tài liệu tham khảo

* [Josephus problem (Wikipedia)](https://en.wikipedia.org/wiki/Josephus_problem)
