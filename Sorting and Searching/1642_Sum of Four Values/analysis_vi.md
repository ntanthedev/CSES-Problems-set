# 1642 - Tổng Bốn Giá Trị

Chúng ta duy trì một tập hợp ban đầu chứa tất cả các tổng dạng $a\_i+a\_j$ với $i < j$. Sau đó, ta duyệt qua các vị trí $i=1,2,\dots,n$. Tại mỗi vị trí, trước tiên ta loại bỏ khỏi tập hợp tất cả các tổng có phần tử đầu tiên là $a\_i$. Sau đó, ta kiểm tra xem có thể tạo tổng $x$ sao cho hai phần tử đầu tiên là $a\_i$ và $a\_j$ với $j < i$ và hai phần tử còn lại lấy từ tập hợp hay không.

Thuật toán chạy trong thời gian $O(n^2 \log n)$ vì có $O(n^2)$ thao tác trên tập hợp và mỗi thao tác mất $O(\log n)$ thời gian.

```cpp
#include <iostream>
#include <set>
#include <tuple>
#include <vector>
using namespace std;

int main() {
    int n, x;
    cin >> n >> x;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    set<tuple<int, int, int>> sums;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            sums.emplace(a[i] + a[j], i, j);
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            sums.erase({a[i] + a[j], i, j});
        }
        for (int j = i - 1; j >= 1; j--) {
            int diff = x - a[i] - a[j];
            auto it = sums.lower_bound({diff, 0, 0});
            if (it == sums.end()) continue;
            auto [sum, a, b] = *it;
            if (sum != diff) continue;
            cout << i << " " << j << " " << a << " " << b << "\n";
            return 0;
        }
    }
    cout << "IMPOSSIBLE\n";
}
```
