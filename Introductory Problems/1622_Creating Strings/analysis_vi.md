# 1622 - Tạo xâu

Đoạn mã sau sử dụng hàm `next_permutation` trong C++ để sinh tất cả các hoán vị phân biệt của một xâu theo thứ tự từ điển.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    string s;
    cin >> s;

    sort(s.begin(), s.end());
    vector<string> v;
    do {
        v.push_back(s);
    } while (next_permutation(s.begin(), s.end()));

    cout << v.size() << "\n";
    for (auto s : v) {
        cout << s << "\n";
    }
}
```
