# 1069 - Đoạn lặp

Đoạn mã sau duyệt xâu từ trái sang phải và duy trì hai biến: `cur` là độ dài của đoạn lặp kết thúc tại vị trí hiện tại, và `res` là độ dài đoạn lặp lớn nhất đã thấy.

```cpp
#include <iostream>
using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size();
    int cur = 1;
    int res = 1;
    for (int i = 1; i < n; i++) {
        if (s[i - 1] != s[i]) cur = 0;
        cur++;
        res = max(res, cur);
    }
    cout << res << "\n";
}
```
