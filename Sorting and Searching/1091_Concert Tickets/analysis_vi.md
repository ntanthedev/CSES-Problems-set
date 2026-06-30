# 1091 - Concert Tickets

Ta thêm tất cả các giá vé vào một multiset, sau đó ta có thể tìm và xóa hiệu quả giá vé tương ứng với giá mà khách hàng đưa ra.

Vì ta cần tìm giá vé lớn nhất không vượt quá giá đã đưa ra, ta sử dụng hàm `upper_bound` để tìm giá vé nhỏ nhất lớn hơn giá đã đưa ra. Sau đó, ta giảm iterator đi một để tìm giá vé mong muốn, rồi xóa nó.

Nếu iterator ban đầu trỏ tới giá vé nhỏ nhất, tức là tất cả các giá vé đều lớn hơn giá đã đưa ra và ta không thể đưa vé cho khách hàng đó.

```cpp
#include <iostream>
#include <set>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    multiset<int> prices;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        prices.insert(x);
    }

    for (int i = 1; i <= m; i++) {
        int x;
        cin >> x;
        auto it = prices.upper_bound(x);
        if (it == prices.begin()) {
            cout << "-1\n";
        } else {
            it--;
            cout << *it << "\n";
            prices.erase(it);
        }
    }
}
```
