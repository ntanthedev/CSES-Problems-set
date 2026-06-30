# 1141 - Playlist

Chúng ta duyệt qua danh sách các bài hát và tính độ dài của đoạn dài nhất kết thúc tại mỗi vị trí.

Vì ta muốn mọi bài hát trong đoạn đều là duy nhất, ta cũng lưu vị trí cuối cùng đã thấy mỗi bài hát. Sử dụng thông tin này, ta có thể duy trì biên trái của đoạn.

```cpp
#include <iostream>
#include <map>
using namespace std;

int main() {
    int n;
    cin >> n;
    map<int, int> last;
    int left = 0;
    int best = 0;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        left = max(left, last[x]);
        best = max(best, i - left);
        last[x] = i;
    }
    cout << best << "\n";
}
```
