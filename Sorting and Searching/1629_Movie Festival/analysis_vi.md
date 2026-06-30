# 1629 - Liên Hoan Phim

Một phương án tối ưu là luôn chọn một bộ phim bắt đầu sau bộ phim cuối cùng ta đã xem và có thời gian kết thúc sớm nhất trong tất cả các bộ phim như vậy. Điều này có thể thực hiện bằng cách sắp xếp các bộ phim theo thời gian kết thúc, sau đó duyệt qua chúng và chọn một cách tham lam bộ phim tiếp theo.

Thuật toán hoạt động đúng vì việc chọn bộ phim tiếp theo có thời gian kết thúc sớm nhất luôn là an toàn. Nếu ta chọn một bộ phim khác, nó sẽ kết thúc muộn hơn và hạn chế nhiều hơn các lựa chọn trong tương lai.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<pair<int, int>> movies;
    for (int i = 1; i <= n; i++) {
        int a, b;
        cin >> a >> b;
        movies.emplace_back(b, a);
    }
    sort(movies.begin(), movies.end());

    int count = 0;
    int end = 0;
    for (auto [b, a] : movies) {
        if (a >= end) {
            end = b;
            count++;
        }
    }
    cout << count << "\n";
}
```
