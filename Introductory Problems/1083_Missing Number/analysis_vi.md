# 1083 - Số bị thiếu

Ta có thể giải bài toán một cách hiệu quả bằng cách sử dụng một vector lưu giá trị boolean cho mỗi số từ $1$ đến $n$: ta đã thấy số đó chưa? Sau đó, ta tìm số duy nhất chưa thấy.

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<bool> seen(n + 1);
    for (int i = 1; i <= n - 1; i++) {
        int x;
        cin >> x;
        seen[x] = true;
    }
    for (int i = 1; i <= n; i++) {
        if (!seen[i]) {
            cout << i << "\n";
        }
    }
}
```

Thực tế, ta cũng có thể giải bài toán mà không cần vector hay bất kỳ cấu trúc dữ liệu nào khác. Ý tưởng là đầu tiên tính tổng $1+2+\dots+n$ và sau đó trừ khỏi tổng tất cả các số đã cho trong dữ liệu vào. Giá trị thu được chính là số bị thiếu duy nhất. Lưu ý rằng tổng có thể bị tràn khi $n$ lớn nhưng kết quả cuối cùng vẫn đúng.

```cpp
#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += i;
    }
    for (int i = 1; i <= n - 1; i++) {
        int x;
        cin >> x;
        sum -= x;
    }
    cout << sum << "\n";
}
```
