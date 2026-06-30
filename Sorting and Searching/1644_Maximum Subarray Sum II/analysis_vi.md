# 1644 - Tổng Đoạn Con Lớn Nhất II

Gọi $s(i)$ là tổng tiền tố $x\_1+x\_2+\dots+x\_i$. Sử dụng hàm này, ta có thể tính tổng của bất kỳ đoạn con nào như sau:
$$x\_j+x\_{j+1}+\dots+x\_i = s(i) - s(j-1)$$
Để giải bài toán, ta duyệt qua mảng và duy trì một multiset chứa tất cả các tổng tiền tố $s(k)$ với $i-b \le k \le i-a$ trong đó $i$ là vị trí hiện tại. Khi đó, tổng lớn nhất của một đoạn con kết thúc tại vị trí $i$ là $s(i) - s(k')$ với $s(k')$ là tổng tiền tố nhỏ nhất trong multiset.

Đoạn code sau đây cài đặt ý tưởng trên và chạy trong thời gian $O(n \log n)$.

```cpp
#include <iostream>
#include <set>
#include <vector>
using namespace std;
using ll = long long;

int main() {
    int n, a, b;
    cin >> n >> a >> b;

    vector<ll> sums;
    sums.push_back(0);
    multiset<ll> order;

    ll sum = 0;
    ll answer = -1e18;

    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        sum += x;
        sums.push_back(sum);

        if (i >= a) {
            order.insert(sums[i - a]);
            answer = max(answer, sum - *order.begin());
        }

        if (i >= b) {
            order.erase(order.find(sums[i - b]));
        }
    }

    cout << answer << "\n";
}
```

Chúng ta cũng có thể tạo một lời giải hiệu quả hơn sử dụng thuật toán cửa sổ trượt tìm giá trị nhỏ nhất trong thời gian tuyến tính thay vì dùng multiset. Ý tưởng là duy trì một dãy tăng dần các giá trị bên trong cửa sổ. Đoạn code sau sử dụng cấu trúc deque và chạy trong thời gian $O(n)$.

```cpp
#include <deque>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

int main() {
    int n, a, b;
    cin >> n >> a >> b;

    vector<ll> sums;
    sums.push_back(0);
    deque<ll> order;

    ll sum = 0;
    ll answer = -1e18;

    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        sum += x;
        sums.push_back(sum);

        if (i >= a) {
            while (!order.empty() && order.back() > sums[i - a]) {
                order.pop_back();
            }
            order.push_back(sums[i - a]);
            answer = max(answer, sum - order[0]);
        }

        if (i >= b) {
            if (order[0] == sums[i - b]) {
                order.pop_front();
            }
        }
    }

    cout << answer << "\n";
}
```

## Tài liệu tham khảo

* [Minimum stack / Minimum queue (CP-Algorithms)](https://cp-algorithms.com/data_structures/stack_queue_modification.html)
