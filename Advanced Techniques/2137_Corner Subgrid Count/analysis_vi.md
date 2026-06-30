# 2137 - Đếm ô lưới góc

Duyệt qua tất cả các góc có thể của một ô lưới con sẽ chạy trong $O(n^4)$ và do đó
sẽ quá chậm. Tuy nhiên, có một cách để tính số lượng ô lưới con chỉ bằng cách
duyệt qua từng cặp hàng.

Chúng ta hãy duyệt qua từng cặp hàng và tìm mỗi ô lưới con kéo dài từ một
trong các hàng được chọn đến hàng còn lại. Để một cặp hàng tạo thành một ô lưới con, các hàng
cần có chung hai vị trí phân biệt có ô màu đen ở cả hai hàng.
Nếu số lượng vị trí như vậy là $c$, thì số lượng ô lưới con mà cặp hàng đó
tạo thành là ${c \choose 2} = \frac{c(c-1)}{2}$, vì ta có thể chọn hai vị trí bất kỳ trong số
chúng làm biên của ô lưới con. Thuật toán này chạy trong $O(n^3)$ vì ta duyệt
qua từng cặp hàng trong thời gian $O(n)$ và có tổng cộng $O(n^2)$ cặp
hàng.

Với $n=3000$, lời giải sẽ thực hiện khoảng $3000^3\approx3\cdot10^{10}$
phép toán và vẫn sẽ quá chậm. Tuy nhiên, chúng ta có thể sử dụng bitset để cải thiện
hệ số hằng số của lời giải. Bitset cho phép chúng ta kiểm tra nhiều
vị trí cùng một lúc. Trên hệ thống Linux, bitset thường chứa các số nguyên 64-bit.
Điều này có nghĩa là, với các thao tác bit thời gian hằng số, chúng ta có thể kiểm tra 64 vị trí cùng
một lúc. Do đó, số lượng phép toán trở thành $3000^3\cdot\frac 1
{64}\approx4\cdot10^8$.

Để tìm các vị trí mà cả hai hàng đều có ô màu đen, chúng ta sẽ sử dụng
phép toán AND bit vì nó loại bỏ các vị trí chỉ có một hoặc không
có ô nào màu đen. Cuối cùng, chúng ta sẽ đếm số lượng bit được bật trong
bitset bằng phương thức `.count()`. Lưu ý rằng ngay cả với tối ưu hóa bitset,
lời giải sẽ vẫn quá chậm nếu thiếu dòng

```cpp
#pragma GCC target("popcnt")
```

dòng này báo cho trình biên dịch biết rằng máy của chúng ta có lệnh tính
popcount của một số nguyên, tức là bộ xử lý của chúng ta có thể đếm số lượng
bit được bật trong một số nguyên một cách hiệu quả. Lệnh popcount có sẵn trên
các máy chấm CSES và đã được tích hợp trong hầu hết các bộ xử lý x86-64 của Intel từ
năm 2008.

```cpp
#pragma GCC target("popcnt")
#include <bitset>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
using B = bitset<3000>;

int main() {
    int n;
    cin >> n;

    vector<B> b(n);
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        for (int j = 0; j < n; ++j) {
            if (s[j] == '1') {
                b[i][j] = true;
            }
        }
    }

    ll r = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int c = (b[i] & b[j]).count();
            r += c * (c - 1) / 2;
        }
    }

    cout << r << '\n';
}
```
