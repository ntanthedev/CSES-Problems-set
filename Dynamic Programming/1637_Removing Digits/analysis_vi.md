# 1637 - Xóa chữ số

Một giải pháp quy hoạch động trực tiếp cho bài toán này là duyệt qua tất cả các chữ số của một số và chọn chữ số nào cho tổng số bước ít nhất.

Biểu thức `number % 10` cho chữ số cuối cùng của số, và các chữ số có thể được dịch sang phải bằng phép chia nguyên. Quá trình này được lặp lại cho đến khi số bằng 0.

```cpp
#include <iostream>
#include <vector>
using namespace std;
const int INF = 1e9;

int main() {
    int n;
    cin >> n;

    vector<int> steps(n + 1);
    steps[0] = 0;
    for (int i = 1; i <= n; ++i) {
        steps[i] = INF;
        int number = i;
        while (number) {
            int digit = number % 10;
            steps[i] = min(steps[i], steps[i - digit] + 1);
            number /= 10;
        }
    }

    cout << steps[n] << "\n";
}
```

## Giải pháp tham lam thay thế

Hóa ra việc luôn trừ đi chữ số lớn nhất sẽ cho kết quả tối ưu.

Điều này giúp code đơn giản hơn, nhưng việc chứng minh đòi hỏi một số suy luận.

### Chứng minh tính đúng đắn

Gọi $\mathrm{steps}(n)$ là số bước tối thiểu cần để đạt đến $0$ khi bắt đầu từ $n$.

Ta sẽ chỉ ra rằng hàm này là không giảm. Tức là, với mọi số nguyên dương $n$, ta có $\mathrm{steps}(n) \ge \mathrm{steps}(n-1)$.

Nếu hàm không giảm trên đoạn $[0, n-1]$, thì việc trừ đi chữ số lớn nhất từ $n$ luôn là tối ưu, vì tổng số bước sẽ là $\mathrm{steps}(n-d) + 1$ với $d$ là chữ số được chọn. Điều này cũng có nghĩa là chiến lược tham lam là tối ưu.

Hàm này thực sự không giảm với $n\in[0, 1]$ vì $\mathrm{steps}(0)=0$ và $\mathrm{steps}(1)=1$.

Chứng minh được hoàn thành bằng quy nạp. Giả sử hàm không giảm trên đoạn $[0, n-1]$ với $n \ge 2$ nào đó. Giả thiết quy nạp là $\mathrm{steps}(n) \ge \mathrm{steps}(n-1)$ và do đó hàm cũng không giảm trên đoạn $[0, n]$.

Khi so sánh các chữ số của $n-1$ và $n$, nhận thấy rằng chữ số lớn nhất của $n$ có thể lớn hơn chữ số lớn nhất của $n-1$ nhiều nhất là 1.

Gọi $d$ là chữ số lớn nhất trong $n-1$. Điều này có nghĩa là

$$\mathrm{steps}(n-1) = \mathrm{steps}(n-1-d)+1.$$

Mặt khác, chữ số lớn nhất của $n$ nhiều nhất là $d+1$, do đó $\mathrm{steps}(n)$ ít nhất là

$$\mathrm{steps}(n-(d+1))+1=\mathrm{steps}(n-1-d)+1.$$

Đây chính bằng $\mathrm{steps}(n-1)$, xác nhận giả thiết quy nạp.

```cpp
#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    int steps = 0;
    while (n) {
        int number = n;
        int max_digit = 0;
        while (number) {
            int digit = number % 10;
            max_digit = max(max_digit, digit);
            number /= 10;
        }
        n -= max_digit;
        steps++;
    }

    cout << steps << "\n";
}
```
