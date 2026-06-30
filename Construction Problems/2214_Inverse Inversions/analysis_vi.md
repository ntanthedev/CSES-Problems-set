# 2214 - Nghịch thế ngược

Có một chiến lược tham lam đơn giản cho bài toán này. Tuy nhiên, không hiển nhiên thấy ngay rằng nó luôn đúng.

Chúng ta sẽ xây dựng đáp án từ đầu, từng phần tử một. Ta duy trì hai con trỏ: số nhỏ nhất và lớn nhất chưa được sử dụng, và tại mỗi bước, thêm một trong hai số đó vào đáp án và cập nhật con trỏ tương ứng.

Thêm số nhỏ nhất chưa dùng sẽ không tạo ra nghịch thế mới với bất kỳ số nào đứng sau nó vì tất cả các số đó đều lớn hơn. Ngược lại, thêm số lớn nhất chưa dùng sẽ tạo ra nghịch thế với tất cả các số đứng sau nó.

Ý tưởng tham lam là luôn chọn số lớn hơn trong khi số lượng nghịch thế vẫn chưa vượt quá $k$. Bây giờ, ta cần chứng minh rằng thuật toán luôn tìm được một lời giải có chính xác $k$ nghịch thế. Tổng cộng, ta có $n-1$ lựa chọn: trong bước đầu tiên, ta có $n-1$ nghịch thế, sau đó $n-2$, và cứ thế cho đến bước áp chót ta có 1 nghịch thế. Tổng số lượng là $1+2+\dots+(n-1)=\frac{n(n-1)}2$, nghĩa là luôn có đủ nghịch thế để tạo thành $k$.

Có thể chứng minh rằng vì ta lấy các nghịch thế một cách tham lam, số nghịch thế cần thiết luôn không vượt quá $\frac {n(n-1)} 2$, với $n$ là số phần tử còn lại. Suy ra khi $n=1$, số nghịch thế cần là tối đa 0, do đó bằng 0. Thuật toán luôn tìm được lời giải có số nghịch thế không bao giờ lớn hơn $k$ và cũng không nhỏ hơn $k$.

```cpp
#include <iostream>
using namespace std;
using ll = long long;

int main() {
    int n;
    ll k;
    cin >> n >> k;

    int l = 1, r = n;
    for (int i = 1; i <= n; ++i) {
        int left = n - i;  // Số lượng số còn lại.
        // Vì r lớn hơn tất cả các số còn lại,
        // thêm nó sẽ tạo nghịch thế với mỗi số trong số đó.
        if (left <= k) {
            k -= left;
            cout << r-- << ' ';
        } else {
            cout << l++ << ' ';
        }
    }
    cout << '\n';
}
```
