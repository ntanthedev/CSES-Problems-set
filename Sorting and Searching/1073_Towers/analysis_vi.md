# 1073 - Towers

Chúng ta duyệt qua các khối lập phương và duy trì một multiset các tòa tháp. Với mỗi tòa tháp, ta lưu kích thước của khối trên cùng.

Khi xử lý một khối, ta mở rộng một tòa tháp có khối trên cùng lớn hơn khối mới nhưng nhỏ nhất có thể. Nếu không có tòa tháp nào có thể mở rộng, ta tạo một tòa tháp mới.

Đây là thuật toán tối ưu vì nếu ta mở rộng một tòa tháp có khối trên cùng lớn hơn hoặc tạo một tòa tháp mới thay vì mở rộng tòa tháp phù hợp, ta sẽ không thể đạt được số lượng tòa tháp nhỏ hơn.

```cpp
#include <iostream>
#include <set>
using namespace std;

int main() {
    int n;
    cin >> n;
    multiset<int> towers;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        auto it = towers.upper_bound(x);
        if (it == towers.end()) {
            towers.insert(x);
        } else {
            towers.erase(it);
            towers.insert(x);
        }
    }
    cout << towers.size() << "\n";
}
```

Ta cũng có thể giải bài toán chỉ bằng một vector và tìm kiếm nhị phân. Ý tưởng là duy trì một dãy tăng dần các tòa tháp và sử dụng tìm kiếm nhị phân để tìm tòa tháp sẽ được mở rộng. Việc mở rộng sẽ không bao giờ làm thay đổi thứ tự của các tòa tháp.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> towers;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        if (towers.empty() || x >= towers.back()) {
            towers.push_back(x);
        } else {
            auto it = upper_bound(towers.begin(), towers.end(), x);
            *it = x;
        }
    }
    cout << towers.size() << "\n";
}
```
