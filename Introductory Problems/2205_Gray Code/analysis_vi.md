# 2205 - Gray Code

Một cách để tạo mã Gray độ dài $n$ là sử dụng đệ quy. Giả sử ta đã có một danh sách các xâu là mã Gray độ dài $n-1$. Sử dụng danh sách đó, ta có thể tạo mã Gray độ dài $n$ như sau:

* Duyệt qua danh sách và, với mỗi xâu $s$, thêm xâu $0s$ vào mã.
* Đảo ngược danh sách.
* Duyệt qua danh sách và, với mỗi xâu $s$, thêm xâu $1s$ vào mã.

Ví dụ, cho mã Gray $[00, 01, 11, 10]$ độ dài $2$, ta có thể tạo mã Gray $[000, 001, 011, 010, 110, 111, 101, 100]$ độ dài $3$.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

vector<string> create(int n) {
    if (n == 1) {
        return {"0", "1"};
    }
    vector<string> code;
    auto prev = create(n - 1);
    for (auto s : prev) {
        code.push_back("0" + s);
    }
    reverse(prev.begin(), prev.end());
    for (auto s : prev) {
        code.push_back("1" + s);
    }
    return code;
}

int main() {
    int n;
    cin >> n;
    auto code = create(n);
    for (auto s : code) {
        cout << s << "\n";
    }
}
```

## Tài liệu tham khảo

* [Gray code (Wikipedia)](https://en.wikipedia.org/wiki/Gray_code)
