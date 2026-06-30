# 3226 - Subarray Sum Queries II (Truy vấn Tổng Đoạn Con II)

Chúng ta tạo một cây phân đoạn mà mỗi nút lưu bốn giá trị:

* `total_sum`: tổng các giá trị trong đoạn
* `max_left`: tổng lớn nhất bắt đầu từ đầu bên trái của đoạn
* `max_right`: tổng lớn nhất kết thúc tại đầu bên phải của đoạn
* `max_sum`: tổng đoạn con lớn nhất trong đoạn

Sử dụng bốn giá trị này, ta có thể tính hiệu quả tổng đoạn con lớn nhất cho bất kỳ đoạn nào.

Giải pháp chạy trong thời gian $O((n+q) \log n)$. Mặc dù bài toán không yêu cầu, cách tiếp cận này cũng hỗ trợ các truy vấn cập nhật.

```cpp
#include <iostream>
using namespace std;
using ll = long long;
const int N = 1 << 18;

struct Node {
    ll total_sum, max_left, max_right, max_sum;
};

Node tree[2 * N];

Node combine(Node left, Node right) {
    Node result;
    result.total_sum = left.total_sum + right.total_sum;
    result.max_left = max(left.max_left, left.total_sum + right.max_left);
    result.max_right = max(right.max_right, left.max_right + right.total_sum);
    result.max_sum =
        max(max(left.max_sum, right.max_sum), left.max_right + right.max_left);
    return result;
}

void set_val(int pos, int value) {
    pos += N;
    tree[pos] = {value, value, value, value};

    for (pos /= 2; pos >= 1; pos /= 2) {
        tree[pos] = combine(tree[pos * 2], tree[pos * 2 + 1]);
    }
}

ll get_sum(int a, int b) {
    a += N;
    b += N;

    Node left = {}, right = {};
    while (a <= b) {
        if (a % 2 == 1) {
            left = combine(left, tree[a++]);
        }
        if (b % 2 == 0) {
            right = combine(tree[b--], right);
        }
        a /= 2;
        b /= 2;
    }

    return combine(left, right).max_sum;
}

int main() {
    int n, q;
    cin >> n >> q;

    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        set_val(i, x);
    }

    for (int i = 1; i <= q; i++) {
        int a, b;
        cin >> a >> b;
        cout << get_sum(a, b) << "\n";
    }
}
```
