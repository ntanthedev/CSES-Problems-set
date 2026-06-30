# 1645 - Nearest Smaller Values

Ý tưởng là tạo một ngăn xếp lưu dãy giá trị tăng dần của mảng. Ta duyệt qua mảng và với mỗi giá trị $x$, loại bỏ tất cả các giá trị trong ngăn xếp không nhỏ hơn $x$. Sau đó, phần tử trên cùng của ngăn xếp chính là giá trị nhỏ hơn gần nhất, hoặc ngăn xếp rỗng nghĩa là không có giá trị nhỏ hơn ở bên trái. Cuối cùng, ta thêm $x$ vào ngăn xếp.

Thuật toán chạy trong $O(n)$ thời gian vì mỗi giá trị được thêm và xóa khỏi ngăn xếp tối đa một lần.

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<pair<int, int>> stack;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        while (!stack.empty() && stack.back().first >= x) {
            stack.pop_back();
        }
        if (!stack.empty()) {
            cout << stack.back().second << " ";
        } else {
            cout << 0 << " ";
        }
        stack.emplace_back(x, i);
    }
    cout << "\n";
}
```

## Tài liệu tham khảo

* [All nearest smaller values (Wikipedia)](https://en.wikipedia.org/wiki/All_nearest_smaller_values)
