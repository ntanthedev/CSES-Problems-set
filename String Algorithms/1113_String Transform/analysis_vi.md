# 1113 - Biến đổi xâu

Phép biến đổi được sử dụng trong bài toán này được gọi là biến đổi Burrows–Wheeler,
và nó được sử dụng trong các thuật toán nén.
Chính xác hơn, bài toán yêu cầu ta tính toán hiệu quả phép biến đổi
ngược.

Ta có thể coi danh sách đã sắp xếp các phép xoay như một lưới, trong đó mỗi hàng
là một phép xoay. Trong ví dụ đầu vào, lưới như sau:

```cpp
#babc
abc#b
babc#
bc#ba
c#bab
```

Ta biết cột cuối cùng của lưới vì nó là xâu đầu vào của ta.
Ta cũng có thể dễ dàng suy ra cột đầu tiên của lưới, vì nó
chứa tất cả các ký tự của xâu đầu vào theo thứ tự đã sắp xếp.

Sử dụng cột đầu tiên và cột cuối cùng, ta có thể tái tạo lại xâu ban đầu.
Vì `#` là ký tự nhỏ nhất,
ký tự cuối cùng của xâu ban đầu là ký tự đầu tiên trong cột cuối cùng.
Sau đó, ta có thể khám phá các ký tự khác từng bước theo thứ tự ngược lại.

Nhận xét quan trọng là nếu ta có hai phép xoay bắt đầu bằng cùng một
ký tự và ta xoay cả hai sang trái một bước, thứ tự từ điển của chúng
không thay đổi. Ví dụ, phép xoay `babc#` nhỏ hơn `bc#ba`,
và phép xoay `abc#b` nhỏ hơn `c#bab`.

Sử dụng tính chất này, ta có thể liên kết mỗi ký tự trong cột cuối cùng với
một ký tự khác trong cột đầu tiên, cho phép ta di chuyển từ một phép xoay
sang phép xoay tiếp theo sau khi xoay xâu sang phải một bước.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size();

    vector<pair<char, int>> chars;
    for (int i = 0; i < n; i++) {
        chars.emplace_back(s[i], i);
    }
    sort(chars.begin(), chars.end());

    vector<int> link(n);
    for (int i = 0; i < n; i++) {
        link[chars[i].second] = i;
    }

    int pos = 0;
    string res;
    for (int i = 0; i < n - 1; i++) {
        res += s[pos];
        pos = link[pos];
    }
    reverse(res.begin(), res.end());
    cout << res << "\n";
}
```

# Tài liệu tham khảo

* [Burrows–Wheeler transform](https://en.wikipedia.org/wiki/Burrows%E2%80%93Wheeler_transform) (Wikipedia)
