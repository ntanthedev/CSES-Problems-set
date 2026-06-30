# 2220 - Đếm số

Trước tiên hãy đưa bài toán về một biến. Định nghĩa hàm
$\mathrm{count}(x)$ bằng số lượng số nguyên trên đoạn $[0, x]$
không có hai chữ số liền kề nào bằng nhau. Đáp án có thể được tìm bằng
cách tính $\mathrm{count}(b) - \mathrm{count}(a - 1)$.

Ta sẽ tính hàm này bằng cách đệ quy chọn từng chữ số của số nguyên
một. Các tham số của hàm đệ quy, hay ngữ cảnh cần thiết để
tính tổng số lượng số nguyên có thể chọn, là:

* $i$: Vị trí của chữ số tiếp theo, bắt đầu từ $0$ tại chữ số có
  ý nghĩa nhất trong $x$.
* $\mathrm{prev}$: Chữ số trước đó đã chọn (nếu có).
* $\mathrm{equal}$: Liệu tất cả các chữ số đã chọn trước đó có bằng
  các chữ số tương ứng trong $x$ hay không. Cần biết điều này để không
  đếm các số nguyên lớn hơn $x$. Sau chữ số khác biệt đầu tiên, không có
  giới hạn nào cho các chữ số còn lại có thể chọn.
* $\mathrm{empty}$: Liệu chưa có chữ số khác không nào được chọn hay chưa,
  nghĩa là tiền tố đang rỗng. Có thể có bất kỳ số lượng số 0 nào liền kề
  nhau trước khi phần đầu thực sự của số nguyên bắt đầu.

Sau đó ta thử từng lựa chọn cho chữ số tiếp theo, $0,\dots,9$, kiểm tra
rằng tổng số không vượt quá $x$, và đảm bảo chữ số không trùng với
chữ số trước đó. Các tham số được cập nhật phù hợp và ta đệ quy
đến chữ số tiếp theo và cộng kết quả vào tổng.

Trường hợp $i=n$, với $n$ là số lượng chữ số trong $x$, nghĩa là ta đã
đặt thành công tất cả các chữ số và tìm được một số nguyên hợp lệ.

Kết quả của hàm được ghi nhớ (memoize) trong một bảng tra cứu. Có tối đa
$(n + 1) \cdot 10 \cdot 2 \cdot 2$ tổ hợp tham số khác nhau cho hàm,
do đó độ phức tạp thời gian khi dùng `std::map` cho bảng tra cứu
là $O(\log x \log \log x)$.

```cpp
#include <array>
#include <iostream>
#include <map>
using namespace std;
using ll = long long;

string s;
map<array<int, 4>, ll> lookup;

ll recurse(int i, int prev, bool equal, bool empty) {
    if (i == (int)s.size()) return 1;

    array<int, 4> params{i, prev, equal, empty};
    if (lookup.count(params)) return lookup[params];

    ll result = 0;
    for (int d = 0; d < 10; ++d) {
        if (equal && d > s[i] - '0') break;
        if (!empty && d == prev) continue;
        result += recurse(i + 1, d, equal && d == s[i] - '0', empty && d == 0);
    }

    lookup[params] = result;
    return result;
}

ll count(ll x) {
    if (x < 0) return 0;
    s = to_string(x);
    lookup.clear();
    return recurse(0, 0, true, true);
}

int main() {
    ll a, b;
    cin >> a >> b;
    cout << count(b) - count(a - 1) << endl;
}
```
