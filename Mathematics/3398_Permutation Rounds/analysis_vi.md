# 3398 - Vòng Hoán Vị

Ta có thể biểu diễn hoán vị dưới dạng một tập các chu trình. Ví dụ, hoán vị $[5,3,2,6,4,1,8,7]$ gồm các chu trình sau:

* $1 \rightarrow 5 \rightarrow 4 \rightarrow 6 \rightarrow 1$ (độ dài $4$)
* $2 \rightarrow 3 \rightarrow 2$ (độ dài $2$)
* $7 \rightarrow 8 \rightarrow 7$ (độ dài $2$)

Kết quả của bài toán là bội chung nhỏ nhất (lcm) của tất cả độ dài các chu trình. Trong hoán vị trên, kết quả là $\textrm{lcm}(4,2,2)=4$.

Đoạn mã sau xác định tất cả độ dài chu trình và tìm phân tích thừa số nguyên tố của mỗi độ dài chu trình. Ta tính lcm bằng cách duyệt qua tất cả các số nguyên tố xuất hiện trong độ dài các chu trình. Với mỗi số nguyên tố $x$, ta nhân kết quả với $x^k$ trong đó $x^k$ là lũy thừa lớn nhất chia hết một trong các độ dài chu trình.

```cpp
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const int M = 1000000007;

int main() {
    int n;
    cin >> n;

    vector<int> order(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> order[i];
    }

    vector<int> max_count(n + 1);

    for (int i = 1; i <= n; i++) {
        if (order[i] == 0) {
            continue;
        }

        int pos = i;
        int length = 0;
        do {
            length++;
            int new_pos = order[pos];
            order[pos] = 0;
            pos = new_pos;
        } while (pos != i);

        for (int x = 2; x * x <= length; x++) {
            int count = 0;
            while (length % x == 0) {
                length /= x;
                count++;
            }
            max_count[x] = max(max_count[x], count);
        }
        if (!max_count[length]) {
            max_count[length] = 1;
        }
    }

    ll result = 1;
    for (int x = 2; x <= n; x++) {
        for (int i = 0; i < max_count[x]; i++) {
            result *= x;
            result %= M;
        }
    }
    cout << result << "\n";
}
```
