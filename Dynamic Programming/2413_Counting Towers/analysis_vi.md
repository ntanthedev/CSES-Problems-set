# 2413 - Đếm tháp

## Lời giải 1

Để giải bài toán này bằng quy hoạch động, việc chọn *không gian trạng thái* là
không hiển nhiên.

Ví dụ, chỉ dùng chiều cao của tháp $n$ làm trạng thái có vẻ không
đủ. Một lời giải có thể thử chia tháp thành hai phần với chiều cao
$a+b=n$, nhưng các tháp không thể chia cũng thể hiện các mẫu phức tạp và
khó đếm. Điều này gợi ý rằng cần mã hóa thêm thông tin về tháp
vào trạng thái.

Một không gian trạng thái phù hợp được xác định bởi chiều cao của tháp, và
liệu hai ô vuông trên cùng có tách rời hay không. Nói cách khác, liệu có một
"đường" được vẽ giữa các ô vuông hay không.

Gọi hàm $\mathrm{towers}(i, s)$ mô tả số lượng tháp với
chiều cao $i$, trong đó $s \in \{ 1, 0 \}$ chỉ liệu các ô vuông trên cùng
có tách rời ($1$) hay không ($0$).

Định nghĩa tháp có chiều cao một là trường hợp cơ sở: $\mathrm{towers}(1, 1) = 1$ (hai
khối $1 \times 1$) và $\mathrm{towers}(1, 0) = 1$ (một khối $2 \times
1$).

Bây giờ hãy xét các *chuyển trạng thái* giữa các chiều cao $i-1$ và $i$.
Có bao nhiêu cách để thêm một lớp vào tháp trong mỗi trường hợp, bằng cách
bắt đầu các khối mới hoặc kéo dài các khối hiện có?

![chuyển trạng thái](477c37c3fb6e8fb2dfd150ebfec2dd20337508b3bf25e11b54d9e7cf651ecdac)

Công thức truy hồi tương ứng với bảng này như sau:

$$\begin{align\*}
\mathrm{towers}(i, 1) &=
4\cdot\mathrm{towers}(i-1, 1) + \mathrm{towers}(i-1, 0) \\
\mathrm{towers}(i, 0) &=
\mathrm{towers}(i-1, 1) + 2\cdot\mathrm{towers}(i-1, 0)
\end{align\*}$$

Cài đặt dưới đây tiền tính toán các giá trị này cho mọi $i \le 10^6$, để mỗi
test có thể được trả lời một cách hiệu quả.

```cpp
#include <iostream>
using namespace std;
using ll = long long;
const int M = 1000000007;
const int N = 1000001;

ll towers[N][2];

int main() {
    towers[1][1] = 1;
    towers[1][0] = 1;

    for (int i = 2; i < N; ++i) {
        towers[i][1] = (4 * towers[i - 1][1] + towers[i - 1][0]) % M;
        towers[i][0] = (towers[i - 1][1] + 2 * towers[i - 1][0]) % M;
    }

    int t;
    cin >> t;
    for (int ti = 0; ti < t; ++ti) {
        int n;
        cin >> n;
        cout << (towers[n][0] + towers[n][1]) % M << "\n";
    }
}
```

## Lời giải 2

Mặc dù có vẻ khó khăn, vẫn tồn tại một công thức tường minh để đếm các tháp
không thể chia nhỏ hơn nữa. Một tháp như vậy gồm một khối $2 \times n$
hoặc hai cột các khối $1 \times x$, trong đó các ranh giới khối không
trùng nhau tại bất kỳ chiều cao nào.

Trong trường hợp sau, có ba cấu hình khả dĩ tại mỗi chiều cao trung gian:
không cột nào có ranh giới khối, chỉ cột trái có ranh giới khối,
hoặc chỉ cột phải có ranh giới khối. Nếu cả hai cột đều có ranh giới,
tháp có thể bị chia tại chiều cao đó.

Gọi chiều cao của tháp không chia được này là $a$. Tổng số
tổ hợp để xây dựng nó là

$$1 + 3^{a-1}.$$

Bây giờ ta có thể xây dựng công thức truy hồi với chỉ một biến. Phần
không chia được trên cùng có thể có chiều cao bất kỳ $1 \le a \le i$.

$$\mathrm{towers}(i) = \sum\_{a=1}^i (1 + 3^{a-1}) \mathrm{towers}(i-a)$$

Ta đặt $\mathrm{towers}(0) = 1$ để phù hợp với mẫu: nếu $a=i$, thì
phần còn lại có chiều cao không, và trường hợp này là hợp lệ.

Dùng trực tiếp công thức truy hồi này sẽ cho độ phức tạp $O(N^2)$,
với $N=10^6$ là $i$ lớn nhất cần. Tuy nhiên, phương trình có thể được
đơn giản hóa.

Để ngắn gọn, $f(i)$ ký hiệu giống như $\mathrm{towers}(i)$.

$$f(i) = \sum\_{a=1}^i (1 + 3^{a-1}) f(i-a)
\tag{1}$$

Quan sát rằng số hạng đầu tiên là $(1 + 3^0) f(i-1) = 2f(i-1)$. Nó có thể
được chuyển sang vế trái của phương trình.

$$f(i) - 2f(i-1) = \sum\_{a=2}^i (1 + 3^{a-1}) f(i-a)$$

Các lũy thừa của ba có thể bị triệt tiêu bằng cách trừ $3f(i-1)$ ở cả hai vế,
thay $i-1$ cho $i$ trong phương trình (1).

$$\begin{align\*}
f(i) - 5f(i-1) &= \sum\_{a=2}^i (1 + 3^{a-1} - 3(1 + 3^{a-2})) f(i-a) \\
&= \sum\_{a=2}^i (1 + 3^{a-1} - 3 - 3\cdot3^{a-2}) f(i-a) \\
&= \sum\_{a=2}^i (1 + 3^{a-1} - 3 - 3^{a-1}) f(i-a) \\
&= -2 \sum\_{a=2}^i f(i-a)
\tag{2}
\end{align\*}$$

Cuối cùng, trừ $f(i-1)-5f(i-2)$ ở cả hai vế theo phương trình (2).

$$\begin{align\*}
f(i) - 6f(i-1) + 5f(i-2) &= -2 \sum\_{a=2}^i f(i-a) +2 \sum\_{a=2}^{i-1} f(i-1-a) \\
&= -2\sum\_{a=2}^i f(i-a) +2 \sum\_{a=3}^i f(i-a) \\
&= -2 f(i-2)
\end{align\*}$$

Biến đổi để được

$$f(i) = 6f(i-1) - 7f(i-2).$$

```cpp
#include <iostream>
using namespace std;
using ll = long long;
const int M = 1000000007;
const int N = 1000001;

ll towers[N];

int main() {
    towers[0] = 1;
    towers[1] = 2;

    for (int i = 2; i < N; ++i) {
        towers[i] = (6 * towers[i - 1] + (M - 7) * towers[i - 2]) % M;
    }

    int t;
    cin >> t;
    for (int ti = 0; ti < t; ++ti) {
        int n;
        cin >> n;
        cout << towers[n] << "\n";
    }
}
```

## Tài liệu tham khảo

* [The On-Line Encyclopedia of Integer Sequences, A034999](http://oeis.org/A034999)
