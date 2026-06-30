# 1146 - Đếm bit

Ta có thể phân tích mẫu hình của từng bit một cách riêng lẻ. Dưới đây là
biểu diễn nhị phân của các số nguyên $1 \dots 15$.

$$\begin{array}{l|l}
1 & 0001 \\
2 & 0010 \\
3 & 0011 \\
4 & 0100 \\
5 & 0101 \\
6 & 0110 \\
7 & 0111 \\
8 & 1000 \\
9 & 1001 \\
10 & 1010 \\
11 & 1011 \\
12 & 1100 \\
13 & 1101 \\
14 & 1110 \\
15 & 1111
\end{array}$$

Nếu xét bit $2 ^ i$, ta thấy $2 ^ i - 1$ số đầu tiên có bit này bằng
$0$, $2 ^ i$ số tiếp theo có bit này bằng $1$, rồi $2 ^ i$ số sau đó lại có
bit này bằng 0, và cứ tiếp tục như vậy. Có thể chứng minh rằng điều này
đúng với mọi bit.

Bây giờ, ta có thể duyệt qua từng bit một và đếm số lượng bit 1 ở vị trí
tương ứng trong các số $1 \dots n$. Gọi một chu kỳ là một bộ $2 ^ i$ số 0
tiếp theo là $2 ^ i$ số 1. Đầu tiên, ta đếm số lượng chu kỳ đầy đủ, sau đó
đếm số lượng bit 1 trong chu kỳ cuối cùng (có thể không đầy đủ).

Lời giải này có độ phức tạp thời gian $O(\log n)$.

```cpp
#include <iostream>
using namespace std;
using ll = long long;

int main() {
    ll n;
    cin >> n;

    ll sum = 0;
    for (int j = 60; j >= 0; --j) {
        ll bit = 1ll << j;
        sum += n / (bit * 2) * bit;
        sum += max(0ll, n % (bit * 2) - (bit - 1));
    }

    cout << sum << '\n';
}
```
