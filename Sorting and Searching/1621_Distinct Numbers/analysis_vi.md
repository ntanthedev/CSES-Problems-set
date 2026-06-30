# 1621 - Các Số Phân Biệt

Một cách để giải bài toán là thêm các số vào một tập hợp (set) và sau đó in kích thước của tập hợp:

```cpp
#include <iostream>
#include <set>
using namespace std;

int main() {
    int n;
    cin >> n;
    set<int> s;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        s.insert(x);
    }
    cout << s.size() << "\n";
}
```

Một cách tiếp cận khác là sắp xếp các số, sau đó các số bằng nhau sẽ nằm cạnh nhau. Hàm `unique` của C++ sau đó có thể được sử dụng để chọn phần tử đầu tiên của mỗi nhóm các phần tử bằng nhau.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    sort(v.begin(), v.end());
    auto pos = unique(v.begin(), v.end());
    cout << pos - v.begin() << "\n";
}
```
