# 1655 - Đoạn con xor lớn nhất

Ta xây dựng một mảng mới $(S\_1, S\_2, S\_3, \dots, S\_n)$, trong đó $S\_i$
là tổng tiền tố xor của $i$ phần tử đầu tiên. Khi đó, tổng xor của đoạn con
từ $i$ đến $j$ bằng $S\_j \oplus S\_{i-1}$.

Nếu xét từng vị trí kết thúc một cách riêng biệt, ta cần tối đa hóa biểu thức
$S\_j \oplus S\_{i-1}$ với $j$ cố định, nói cách khác, tìm $i$ để tối đa hóa
biểu thức. Điều này có thể thực hiện bằng cấu trúc dữ liệu trie.

Thông thường, trie được dùng để lưu xâu, nhưng trong bài toán này, ta sẽ lưu
các số theo biểu diễn nhị phân của chúng. Bằng cách này, ta có thể tìm vị trí
bắt đầu tối ưu trong thời gian logarit. Ta sẽ tìm tổng tiền tố tối ưu từng
bit một, bắt đầu từ bit có ý nghĩa nhất. Vì mỗi bit có giá trị lớn hơn tổng
các bit đứng sau nó, nên việc quyết định bit lớn nhất trước là tối ưu.

```cpp
#include <iostream>
using namespace std;

const int N = 200001;
const int LOG_X = 30;
const int NODES = N * LOG_X;

int c[NODES][2], nodes = 1;

void add(int x) {
    int n = 0;
    for (int shift = LOG_X - 1; shift >= 0; --shift) {
        int bit = x >> shift & 1;
        if (!c[n][bit]) c[n][bit] = nodes++;
        n = c[n][bit];
    }
}

int query(int x) {
    int n = 0, ret = 0;
    for (int shift = LOG_X - 1; shift >= 0; --shift) {
        int bit = ~x >> shift & 1;
        if (!c[n][bit]) {
            n = c[n][!bit];
        } else {
            ret += 1 << shift;
            n = c[n][bit];
        }
    }
    return ret;
}

int x[N];

int main() {
    int n;
    cin >> n;

    int ans = 0, sum = 0;
    add(0);

    for (int i = 0; i < n; ++i) {
        cin >> x[i];
        sum ^= x[i];
        ans = max(ans, query(sum));
        add(sum);
    }

    cout << ans << '\n';
}
```
