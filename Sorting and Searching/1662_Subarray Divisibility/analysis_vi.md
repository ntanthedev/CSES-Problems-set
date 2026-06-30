# 1662 - Subarray Divisibility

Gọi $s(i)$ là tổng tiền tố $a\_1+a\_2+\dots+a\_i$. Tổng của một đoạn con $a\_l,a\_{l+1},\dots,a\_r$ chia hết cho $n$ khi và chỉ khi
$$s(r) \bmod n = s(l-1) \bmod n,$$
do đó ta có thể giải bài toán bằng cách đếm số lần đã gặp mỗi tổng tiền tố modulo $n$.

Vì mỗi tổng tiền tố modulo $n$ nằm trong khoảng từ $0$ đến $n-1$, ta có thể sử dụng một vector để lưu các bộ đếm. Lưu ý rằng cần cẩn thận trong tính toán modulo vì tổng có thể âm. Thuật toán chạy trong $O(n)$ thời gian.

```cpp
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

int main() {
    int n;
    cin >> n;

    vector<int> sums(n);
    sums[0] = 1;

    ll sum = 0;
    ll count = 0;
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        sum += a;
        sum = (sum % n + n) % n;
        count += sums[sum];
        sums[sum]++;
    }

    cout << count << "\n";
}
```
