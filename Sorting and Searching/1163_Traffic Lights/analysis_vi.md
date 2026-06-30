# 1163 - Đèn Giao Thông

Chúng ta duy trì một tập hợp (set) chứa tất cả các vị trí của đèn và một đa tập hợp (multiset) chứa tất cả độ dài đoạn đường giữa hai đèn.

Đầu tiên ta thêm hai đèn giả với vị trí $0$ và $x$ để việc cài đặt dễ dàng hơn, cùng với một đoạn đường duy nhất có độ dài $x$. Sau đó ta cập nhật các cấu trúc dữ liệu sau khi thêm mỗi đèn mới. Điều này có thể thực hiện bằng cách tìm đèn kế tiếp và đèn trước đó của đèn mới và cập nhật độ dài các đoạn đường.

```cpp
#include <iostream>
#include <set>
using namespace std;

int main() {
    int x, n;
    cin >> x >> n;

    set<int> lights;
    multiset<int> lengths;
    lights.insert(0);
    lights.insert(x);
    lengths.insert(x);

    for (int i = 1; i <= n; i++) {
        int p;
        cin >> p;
        auto it2 = lights.upper_bound(p);
        auto it1 = it2;
        it1--;
        lights.insert(p);
        lengths.erase(lengths.find(*it2 - *it1));
        lengths.insert(p - *it1);
        lengths.insert(*it2 - p);
        cout << *lengths.rbegin() << " ";
    }
    cout << "\n";
}
```
