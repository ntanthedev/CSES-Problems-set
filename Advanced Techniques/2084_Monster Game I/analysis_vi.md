# 2084 - Monster Game I

Với mỗi $i$, ta sẽ tìm thời gian tối thiểu để tiêu diệt con quái vật thứ $i$
và có thể một số con quái vật khác trước nó. Hãy tập trung vào con quái vật thứ $i$.
Giả sử ta đã tính được thời gian tối thiểu cho mỗi con quái vật trước đó, ta có
$i-1$ đề xuất dạng $(t\_j, f\_j)$, trong đó $t\_j$ là thời gian tối thiểu để
tiêu diệt con quái vật thứ $j$ và $f\_j$ là hệ số kỹ năng của người chơi sau khi
tiêu diệt con quái vật thứ $j$.

Với bất kỳ đề xuất $j < i$ nào, cần thêm $s\_i\cdot f\_j$ thời gian để tiêu diệt
con quái vật thứ $i$ và do đó tổng thời gian là $t = t\_j + s\_i \cdot f\_j$.
Chú ý rằng các đề xuất có thể được xem xét về mặt hình học như các đường thẳng
$y = ax + b$, trong đó độ cao của một đường thẳng tại điểm $x$ tương ứng với
tổng thời gian cần để tiêu diệt một con quái vật có sức mạnh $x$.

Ta quan tâm đến việc tìm thời gian tối thiểu có thể để tiêu diệt con quái vật
thứ $i$. Nói cách khác, độ cao nhỏ nhất của một đường thẳng tại điểm $x=s\_i$.

![](6bdbfb9f8178d82c4e9c632f32f494b981c6d884a47e2260f532859b335c2b34)

Các đề xuất hiện có không thay đổi tùy theo vị trí của ta trong mảng, nghĩa là
chúng không phụ thuộc vào $i$. Điều này có nghĩa là nếu ta có thể tìm một cấu
trúc dữ liệu hiệu quả để chèn và lưu trữ các đường thẳng, nó có thể được dùng để
tính thời gian tốt nhất cho mỗi $i$.

![](52a65a8e853fb3b46db50e1a921a85bc5ce82892182f88a12c396998cb8b31d7)

Chú ý rằng đường thẳng nhỏ nhất thay đổi tùy theo $x$. Thực tế, các đường thẳng
chia trục $x$ thành các đoạn mà một đường thẳng nhất định là thấp nhất. Như có
thể thấy từ hình ảnh, mỗi đường thẳng tương ứng với nhiều nhất một đoạn, nghĩa
là trục $x$ được chia thành nhiều nhất $n$ đoạn.

Hãy phân tích sâu hơn một chút. Nhắc lại từ đề bài rằng
các hệ số góc của các đường thẳng ($f\_i$) đang giảm dần và các điểm mà tại đó
ta truy vấn đường thẳng tốt nhất ($s\_i$) đang tăng dần. Hệ số góc của các đường
thẳng nhỏ nhất cũng theo thứ tự giảm dần. Điều này có nghĩa là mỗi đề xuất mới
sẽ là đường thẳng nhỏ nhất cuối cùng mới. Điều này cho phép ta duy trì một mảng
đơn giản các đường thẳng và đẩy mỗi đề xuất mới vào cuối mảng.

Chú ý rằng một số đường thẳng có thể không bao giờ đạt giá trị nhỏ nhất. Đây là
trường hợp của đường thẳng thứ tư trong hình. Khi thêm một đường thẳng mới vào
cuối mảng, ta cần kiểm tra xem nó có làm cho đường thẳng trước đó trở nên dư
thừa hay không. Nếu đúng như vậy, ta có thể loại bỏ đường thẳng trước đó khỏi
mảng trước khi thêm đường thẳng mới.

Có một cách đơn giản để kiểm tra xem đường thẳng mới có làm cho đường thẳng
trước đó trở nên dư thừa hay không. Chỉ cần so sánh hai điểm giao nhau. Gọi
$x\_1$ là giao điểm của đường thẳng cuối cùng và đường thẳng liền trước nó,
và $x\_2$ là giao điểm của đường thẳng cuối cùng và đường thẳng mới. Đường
thẳng cuối cùng sẽ trở nên dư thừa nếu $x\_1\ge x\_2$. Điều này là do đường
thẳng cuối cùng có giá trị nhỏ nhất trên đoạn $[x\_1, x\_2]$.

![](7f7105ef40e859ae11b940f615f6dad16e83a0d34b70494ccac6b8eff285476c)

Để tìm đường thẳng nhỏ nhất tại vị trí $x$, ta có thể sử dụng tìm kiếm nhị phân.
Tuy nhiên, vì dãy các điểm truy vấn đang tăng dần, ta cũng có thể chỉ cần duy trì
một con trỏ đến mảng các đường thẳng, điều này làm cho chi phí khấu hao của việc
truy vấn là $O(1)$. Tổng cộng, giải pháp có độ phức tạp thời gian là $O(n)$. Ý
tưởng chính của việc duy trì bao lồi của các hàm tuyến tính được gọi là *kỹ thuật
bao lồi (convex hull trick)*.

```cpp
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

struct Line {
    ll a, b;  // Biểu diễn đường thẳng y = ax + b
    // Trả về độ cao của đường thẳng tại x.
    ll operator()(ll x) { return a * x + b; }
};

int main() {
    int n, x;
    cin >> n >> x;

    vector<int> s(n), f(n);
    for (int i = 0; i < n; ++i) cin >> s[i];
    for (int i = 0; i < n; ++i) cin >> f[i];

    vector<Line> lines;
    lines.push_back({x, 0});

    int pos = 0;  // Lưu chỉ số của đường thẳng thấp nhất hiện tại.

    // Tìm độ cao của đường thẳng thấp nhất tại vị trí x.
    // Giả sử dãy các x đang tăng dần.
    auto get_best = [&](ll x) {
        while (pos + 1 < lines.size() && lines[pos + 1](x) < lines[pos](x)) {
            pos++;
        }
        return lines[pos](x);
    };

    for (int i = 0; i < n - 1; ++i) {
        ll b = get_best(s[i]);
        Line l = {f[i], b};
        while (lines.size() > 1) {
            auto a = lines[lines.size() - 2];
            auto b = lines[lines.size() - 1];
            // So sánh x1 và x2.
            //
            //      b.b - a.b          l.b - a.b
            // x1 = ---------     x2 = ---------
            //      a.a - b.a          a.a - l.a
            if ((l.b - a.b) * (a.a - b.a) <= (b.b - a.b) * (a.a - l.a)) {
                lines.pop_back();
            } else {
                break;
            }
        }
        lines.push_back(l);
    }

    cout << get_best(s[n - 1]) << '\n';
}
```

## Tài liệu tham khảo

* [CP-Algorithms, *Convex hull trick*](https://cp-algorithms.com/geometry/convex_hull_trick.html)
