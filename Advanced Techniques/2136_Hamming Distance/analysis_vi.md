# 2136 - Khoảng Cách Hamming

Nếu chúng ta lưu trữ từng bit riêng lẻ trong một biến `bool` chẳng hạn, và sau đó duyệt qua từng bit khi so sánh hai xâu nhị phân, code sẽ chạy quá chậm. Cách giải này có độ phức tạp thời gian là $O(n^2k)$, vì nó duyệt qua từng bit trong mỗi cặp xâu. May mắn thay, có một cách lưu trữ xâu nhị phân hiệu quả hơn nhiều. Cách nào tốt hơn để lưu trữ chúng so với các số nguyên thông thường?

Kiểu `int` trong C++ có độ rộng 32 bit, quá đủ cho bài toán này. Nhận xét quan trọng nhất là khoảng cách Hamming giữa hai xâu nhị phân có thể được tính một cách hiệu quả bằng phép toán xor trên bit. Thực tế, khoảng cách Hamming tương ứng với số lượng bit được bật trong phép xor trên bit. Lưu ý rằng trong phép xor trên bit, các bit giống nhau sẽ cho kết quả 0 và các bit khác nhau sẽ cho kết quả 1. Điều này có thể thấy rõ trong đầu vào mẫu.

$$\begin{array}{c}
\phantom{\oplus9}101000\\
\underline{\oplus\phantom{9}001000}\\
\phantom{\oplus9}100000\\
\end{array}$$

Vì mỗi bit được bật tương ứng với một vị trí có các bit khác nhau, số lượng bit được bật tương ứng với khoảng cách Hamming. Trong ví dụ, số lượng bit được bật là 1 và do đó kết quả cũng là 1.

Một hàm quan trọng cần biết là `__builtin_popcount`, hàm này tính toán popcount của một số `int` một cách hiệu quả. Hàm nói trên hoạt động thậm chí còn nhanh hơn nếu trình biên dịch biết rằng chúng ta đang chạy trên một máy có lệnh tính popcount. Hầu hết các bộ vi xử lý hiện đại đều có lệnh này, bao gồm cả máy chấm của CSES, và dòng lệnh sau đây có thể được sử dụng để truyền đạt thông tin này đến trình biên dịch.

```cpp
#pragma GCC target("popcnt")
```

Nếu chúng ta giả sử rằng $k$ tỷ lệ với kích thước từ máy, chúng ta có thể nói rằng các thao tác xor và popcount mất $O(1)$ thời gian, dẫn đến độ phức tạp thời gian là $O(n^2)$.

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    vector<int> b(n);
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        for (int j = 0; j < k; ++j) {
            if (s[j] == '1') {
                b[i] += 1 << j;
            }
        }
    }

    int r = 1e9;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            r = min(r, __builtin_popcount(b[i] ^ b[j]));
        }
    }

    cout << r << '\n';
}
```
