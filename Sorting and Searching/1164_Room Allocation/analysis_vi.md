# 1164 - Phân Phòng

Chúng ta tạo hai sự kiện cho mỗi khách hàng: một sự kiện đến và một sự kiện đi. Sau đó ta sắp xếp các sự kiện theo thời gian và xử lý chúng.

Chúng ta duy trì một cấu trúc dữ liệu chứa tất cả các phòng trống. Khi một khách hàng đến, ta cho họ một phòng trống bất kỳ. Tuy nhiên, nếu không có phòng trống, ta tăng số phòng lên một trước khi cho phòng. Sau đó, khi khách hàng rời đi, phòng của họ lại trống.

Trong đoạn mã sau, chúng ta sử dụng một vector để lưu danh sách các phòng trống và luôn chọn phòng cuối cùng trong vector vì nó dễ dàng loại bỏ.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<vector<int>> events;
    for (int i = 1; i <= n; i++) {
        int a, b;
        cin >> a >> b;
        events.push_back({a, 1, i});
        events.push_back({b, 2, i});
    }

    sort(events.begin(), events.end());

    vector<int> rooms;
    int count = 0;
    vector<int> choice(n + 1);

    for (auto e : events) {
        if (e[1] == 1) {
            if (rooms.empty()) {
                count++;
                rooms.push_back(count);
            }
            choice[e[2]] = rooms.back();
            rooms.pop_back();
        }
        if (e[1] == 2) {
            rooms.push_back(choice[e[2]]);
        }
    }

    cout << count << "\n";
    for (int i = 1; i <= n; i++) {
        cout << choice[i] << " ";
    }
    cout << "\n";
}
```
