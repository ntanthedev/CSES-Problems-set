# 1653 - Đi thang máy

## Các cách tiếp cận tham lam sai

Ban đầu có vẻ như một cách tiếp cận tham lam có thể giải quyết bài toán: chọn người vào một lượt thang máy chừng nào còn có người vừa. Tuy nhiên, không có cách đơn giản nào để chọn người tiếp theo hoạt động tối ưu trong mọi trường hợp.

Ví dụ, xét dữ liệu vào

$$\begin{align\*}
x &= 8 \\
w &= 4, 3, 3, 2, 2, 2.
\end{align\*}$$

Cả chiến lược luôn chọn người nặng nhất còn vừa, cũng như chiến lược chọn người nhẹ nhất, đều không tìm được lời giải tối ưu, đó là hai thang máy đầy:

$$(4, 2, 2), (3, 3, 2)$$

## Hoán vị

Duyệt qua tất cả các hoán vị của mọi người là đủ để giải bài toán. Ý tưởng là thêm người vào thang máy lần lượt chừng nào người tiếp theo còn vừa, và bắt đầu một lượt mới nếu không. Mọi cách phân chia thang máy sẽ tương ứng với một hoán vị nào đó mà từ đó có thể tái tạo lời giải.

Có tối đa $20! \approx 10^{18}$ hoán vị khác nhau, vì vậy không thể kiểm tra từng hoán vị riêng lẻ. Ý tưởng có thể được tối ưu bằng cách sử dụng quy hoạch động trên tập con của người, còn gọi là quy hoạch động bitmask.

## Từ hoán vị đến tập con

Khi chọn người lần lượt, thông tin duy nhất cần xem xét là *tập con* những người đã được xếp vào thang máy. Thứ tự mà những người trước đó được chọn không quan trọng miễn là nó tối ưu.

Gọi hàm $\mathrm{best}$ có giá trị dạng $\mathrm{best}(S) = (r, l)$ trong đó cặp $(r, l)$ mô tả số lượt thang máy tối ưu $r$ và trọng lượng đã sử dụng từ lượt cuối $l$ cho một tập con $S$ bất kỳ. Trong số các lời giải có cùng số lượt, lời giải nào có $l$ nhỏ hơn được coi là tốt hơn.

Hàm này có thể được tính đệ quy bằng cách thử lần lượt từng người trong tập con là người cuối cùng được xét.

$$\mathrm{best}(S) = \min\_{p\in S} \mathrm{add}(\mathrm{best}(S \setminus \{p\}), w\_p)$$

Ở đây, $\mathrm{add}((r, l), w\_p)$ cố gắng thêm người $p$ vào lượt thang máy cuối cùng thành $(r, l + w\_p)$, hoặc tạo một lượt mới thành $(r+1, w\_p)$ nếu $l + w\_p > x$.

Ta đặt $\mathrm{best}(\emptyset)=(1, 0)$ làm trường hợp cơ sở để các giá trị còn lại được chính xác mặc dù thực tế không cần lượt đi nào.

Cũng có thể biến số lượt thang máy thành một biến của hàm, dạng $\mathrm{best}(S, r) = l$, và chỉ tối thiểu hóa tổng trọng lượng của lượt thang máy cuối. Tuy nhiên, điều này không cần thiết vì không bao giờ có sự mơ hồ khi so sánh các cặp $(r, l)$. Nghĩa là, một cặp có ít lượt hơn luôn luôn tốt hơn một cặp có nhiều lượt hơn. Điều này cho phép ta tìm cặp tối ưu giống như cách tối ưu hóa một số duy nhất với quy hoạch động. Thực tế, các toán tử so sánh mặc định của `std::pair` hoạt động đúng theo cách này.

Tập con $S$ được biểu diễn thuận tiện dưới dạng mặt nạ bit (bitmask) trong lời giải dưới đây. Duyệt qua các mặt nạ bit theo thứ tự giá trị số đảm bảo rằng mọi tập con nhỏ hơn được tính trước tập hiện tại. Lời giải có độ phức tạp thời gian $O(n 2^n)$.

```cpp
#include <iostream>
#include <vector>
using namespace std;

const int N = 20;
pair<int, int> best[1 << N];

int main() {
    int n, x;
    cin >> n >> x;

    vector<int> w(n);
    for (int i = 0; i < n; ++i) cin >> w[i];

    best[0] = {1, 0};
    for (int s = 1; s < (1 << n); ++s) {
        best[s] = {n + 1, 0};

        for (int p = 0; p < n; ++p) {
            if (s & (1 << p)) {
                auto [r, l] = best[s ^ (1 << p)];
                pair<int, int> added;
                if (l + w[p] <= x) {
                    added = {r, l + w[p]};
                } else {
                    added = {r + 1, w[p]};
                }
                best[s] = min(best[s], added);
            }
        }
    }

    cout << best[(1 << n) - 1].first << endl;
}
```

## Tài liệu tham khảo

* [CPHB (Sổ tay lập trình viên)](https://cses.fi/book), Chương 10, Từ hoán vị đến tập con
