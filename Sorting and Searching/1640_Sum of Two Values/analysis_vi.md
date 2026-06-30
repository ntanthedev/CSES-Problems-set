# 1640 - Tổng Hai Giá Trị

Một cách để giải bài toán là duyệt qua mảng và sử dụng cấu trúc map để lưu chỉ số của mỗi giá trị. Khi giá trị hiện tại là $a$, ta có thể kiểm tra xem đã gặp giá trị $x-a$ hay chưa, nếu có thì ta đã tìm được lời giải.

```cpp
#include <iostream>
#include <map>
using namespace std;

int main() {
    int n, x;
    cin >> n >> x;
    map<int, int> m;
    for (int i = 1; i <= n; i++) {
        int a;  
        cin >> a;
        if (m[x - a]) {
            cout << m[x - a] << " " << i << "\n";
            return 0;
        }
        m[a] = i;
    }
    cout << "IMPOSSIBLE\n";
}
```

Một cách tiếp cận khác là tạo một vector các cặp, mỗi phần tử gồm giá trị và chỉ số của nó trong mảng. Sau đó, sau khi sắp xếp vector, ta có thể giải bài toán bằng kỹ thuật hai con trỏ.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, x;
    cin >> n >> x;

    vector<pair<int, int>> v;
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        v.emplace_back(a, i);
    }
    sort(v.begin(), v.end());

    int i = 0;
    int j = n - 1;
    while (i < j) {
        int s = v[i].first + v[j].first;
        if (s == x) {
            cout << v[i].second << " " << v[j].second << "\n";
            return 0;
        } else if (s > x) {
            j--;
        } else {
            i++;
        }
    }
    cout << "IMPOSSIBLE\n";
}
```
