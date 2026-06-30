# 1619 - Khách Hàng Nhà Hàng

Chúng ta tạo hai sự kiện cho mỗi khách hàng: một sự kiện đến và một sự kiện rời đi. Mỗi sự kiện là một cặp hai giá trị: một thời gian và sự thay đổi số lượng khách hàng ($1$ cho đến và $-1$ cho rời đi).

Sau đó, chúng ta sắp xếp các sự kiện theo thời gian và duyệt qua chúng. Khi các sự kiện đã được sắp xếp, ta dễ dàng theo dõi số lượng khách hàng và ghi nhận số lượng lớn nhất.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<pair<int, int>> events;
    for (int i = 1; i <= n; i++) {
        int a, b;
        cin >> a >> b;
        events.emplace_back(a, 1);
        events.emplace_back(b, -1);
    }
    sort(events.begin(), events.end());

    int count = 0;
    int high = 0;
    for (auto [t, d] : events) {
        count += d;
        high = max(high, count);
    }
    cout << high << "\n";
}
```
