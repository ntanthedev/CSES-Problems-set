# 1661 - Subarray Sums II

Gọi $s(i)$ là tổng tiền tố $a\_1+a\_2+\dots+a\_i$. Sử dụng hàm này, ta có thể tính tổng của bất kỳ đoạn con nào như sau:
$$a\_l+a\_{l+1}+\dots+a\_r = s(r) - s(l-1)$$
Để đếm số lượng đoạn con kết thúc tại vị trí $i$ và có tổng bằng $x$, ta cần tìm tất cả các giá trị $j<i$ sao cho
$$s(i) - s(j) = x$$
tương đương với
$$s(j) = s(i) - x.$$
Ta có thể lưu số lần đã gặp mỗi tổng tiền tố và sau đó tìm hiệu quả số lượng đoạn con. Đoạn mã sau sử dụng cấu trúc bảng băm (map) để đếm các tổng tiền tố và chạy trong $O(n \log n)$ thời gian.

```cpp
#include <iostream>
#include <map>
using namespace std;
using ll = long long;

int main() {
    int n, x;
    cin >> n >> x;

    map<ll, int> sums;
    sums[0] = 1;

    ll sum = 0;
    ll count = 0;
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        sum += a;
        count += sums[sum - x];
        sums[sum]++;
    }

    cout << count << "\n";
}
```
