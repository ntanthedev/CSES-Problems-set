# 2184 - Truy vấn tổng tiền xu bị thiếu

Chúng ta xử lý mỗi truy vấn trong $B$ bước với $B=\lfloor \log\_2 10^9 \rfloor = 30$.
Trong mỗi bước $b=0,1,\dots,B-1$, chúng ta xét tất cả các đồng xu trong đoạn truy vấn
có bit có nghĩa lớn nhất của giá trị đồng xu nằm ở vị trí $b$.

Với mỗi truy vấn $i$, chúng ta duy trì một giá trị $\textrm{result}[i]$,
cho biết chúng ta có thể tạo ra tất cả các tổng đồng xu
từ $1$ đến $\textrm{result}[i]$ bằng các đồng xu đang có.
Ban đầu $\textrm{result}[i]=0$ với mỗi $i=1,2,\dots,q$.

Trong mỗi bước, chúng ta cập nhật kết quả cho mỗi truy vấn.
Gọi $\textrm{sum}(i,b)$ và $\textrm{min}(i,b)$
lần lượt là tổng và giá trị nhỏ nhất của các đồng xu trong đoạn của truy vấn $i$
có bit có nghĩa lớn nhất ở vị trí $b$.
Bất cứ khi nào $\textrm{min}(i,b) \le \textrm{result}[i]+1$,
chúng ta có thể mở rộng phạm vi các tổng có thể tạo ra
bằng cách cộng $\textrm{sum}(i,b)$ vào $\textrm{result}[i]$.
Cuối cùng, $\textrm{result}[i]+1$ là tổng tiền xu bị thiếu nhỏ nhất.

Chúng ta sử dụng các cấu trúc dữ liệu cho truy vấn tổng đoạn và truy vấn nhỏ nhất đoạn hiệu quả.
Sử dụng các cấu trúc dữ liệu này,
chúng ta có thể xử lý truy vấn tổng đoạn trong $O(1)$ thời gian sau khi tiền xử lý $O(n)$ thời gian
và truy vấn nhỏ nhất đoạn trong $O(1)$ thời gian sau khi tiền xử lý $O(n \log n)$ thời gian.

Thuật toán kết quả hoạt động trong $O(B(n \log n + q))$ thời gian.

```cpp
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

const int INF = 1e9 + 1;
const int B = 30;
const int K = 18;

int main() {
    int n, q;
    cin >> n >> q;

    vector<int> x(n + 1);
    vector<int> bit(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> x[i];
        bit[i] = 31 - __builtin_clz(x[i]);
    }

    vector<pair<int, int>> query(q + 1);
    for (int i = 1; i <= q; i++) {
        cin >> query[i].first >> query[i].second;
    }

    vector<ll> result(q + 1);
    vector<ll> sumq(n + 1);
    vector<vector<int>> minq(K, vector<int>(n + 1));

    for (int b = 0; b < B; b++) {
        for (int i = 1; i <= n; i++) {
            sumq[i] = sumq[i - 1];
            if (bit[i] == b) {
                sumq[i] += x[i];
            }
        }

        for (int i = 1; i <= n; i++) {
            minq[0][i] = bit[i] == b ? x[i] : INF;
        }
        for (int k = 1; k < K; k++) {
            for (int i = 1; i <= n - (1 << (k - 1)); i++) {
                minq[k][i] =
                    min(minq[k - 1][i], minq[k - 1][i + (1 << (k - 1))]);
            }
        }

        for (int i = 1; i <= q; i++) {
            auto [a, b] = query[i];
            int level = 31 - __builtin_clz(b - a + 1);
            int min_x = min(minq[level][a], minq[level][b - (1 << level) + 1]);
            if (min_x <= result[i] + 1) {
                result[i] += sumq[b] - sumq[a - 1];
            }
        }
    }

    for (int i = 1; i <= q; i++) {
        cout << result[i] + 1 << "\n";
    }
}
```
