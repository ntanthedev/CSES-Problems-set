# 1651 - Truy vấn cập nhật trên đoạn

Bài toán này có các thao tác cập nhật trên đoạn.
Một cây phân đoạn thông thường không thể xử lý chúng.
Một cấu trúc dữ liệu mạnh mẽ hơn như
*Cây phân đoạn với Lazy Propagation*
có thể được sử dụng.
Tuy nhiên, nếu muốn
tiếp tục sử dụng cây phân đoạn thông thường, chúng ta phải
sáng tạo một chút.

## Cách tiếp cận thứ nhất: Mảng hiệu

Một sự thay đổi góc nhìn giúp giải bài toán này
dễ dàng hơn. Chúng ta không nên nghĩ về mảng theo cách thông thường.
Thay vào đó, chúng ta nên thao tác trên một mảng mà mỗi phần tử
đại diện cho hiệu giữa các phần tử liên tiếp
trong mảng gốc. Phần tử thứ $i$ của mảng gốc
được biểu diễn bằng tổng
của các giá trị tại $i$ vị trí đầu tiên, tức là
các vị trí $1\ldots i$, trong mảng mới.

Đầu tiên, chúng ta khởi tạo mảng với các số 0.
Sau đó, chúng ta thêm các phần tử gốc.
Với mỗi phần tử $x\_i$, chúng ta thêm $x_i$ vào vị trí $i$
và $-x\_i$ vào vị trí $i+1$.
Lúc này, với mỗi $i$, tổng của các vị trí $1\ldots i$
có giá trị $x\_i$.

Các thao tác cập nhật được xử lý theo cách tương tự – với mỗi cập nhật
$a, b, u$, chúng ta thêm $u$ vào vị trí $a$ và trừ $u$ khỏi vị trí $b+1$.

Bởi vì chúng ta chỉ thực hiện cập nhật điểm và truy vấn trên đoạn, mảng này có thể được
biểu diễn bằng một cây phân đoạn thông thường hoặc cây Fenwick.

Làm theo cách này, mỗi lần tra cứu một giá trị đơn lẻ mất $O(\log n)$ thời gian,
nhưng đó là nhược điểm chúng ta phải chấp nhận.

```cpp
#include <iostream>
using namespace std;
using ll = long long;

const int TREE_SIZE = 1 << 18;
ll tree[TREE_SIZE * 2];

void change(int i, int x) {
    i += TREE_SIZE;
    while (i) {
        tree[i] += x;
        i /= 2;
    }
}

// Trả về tổng các giá trị trong đoạn [l, r]
ll get_sum(int l, int r) {
    ll res = 0;
    l += TREE_SIZE;
    r += TREE_SIZE;
    while (l <= r) {
        if (l % 2 == 1) res += tree[l++];
        if (r % 2 == 0) res += tree[r--];
        l /= 2;
        r /= 2;
    }
    return res;
}

int main() {
    int n, q;
    cin >> n >> q;

    for (int i = 1; i <= n; ++i) {
        int x;
        cin >> x;
        change(i, x);
        change(i + 1, -x);
    }

    for (int qi = 0; qi < q; ++qi) {
        int t;
        cin >> t;
        if (t == 1) {
            int l, r, u;
            cin >> l >> r >> u;
            change(l, u);
            change(r + 1, -u);
        } else {
            int k;
            cin >> k;
            cout << get_sum(1, k) << '\n';
        }
    }
}
```

## Cách tiếp cận thứ hai: Cây phân đoạn biến đổi

Chúng ta hãy xem xét kỹ hơn cách thức hoạt động của cây
phân đoạn.

Hàm sau đây tính tổng các giá trị
tương ứng với các vị trí $[l,r]$.
Nó thực hiện điều này bằng cách tìm số lượng nút tối thiểu tương ứng
với các đoạn không chồng lấn phủ toàn bộ đoạn truy vấn.

```cpp
ll query(int l, int r) {
    ll ret = 0;
    l += tree_size;
    r += size_size;
    while (l <= r) {
        if (l % 2 == 1) ret += tree[l++];
        if (r % 2 == 0) ret += tree[r--];
        l /= 2;
        r /= 2;
    }
    return ret;
}
```

Hình ảnh sau mô tả một ví dụ về truy vấn và
các nút được sử dụng để trả lời truy vấn.

![](879551a5b0a78c9bb90b10134245a5487d9f5ae3fb42aa9bc8abc029c89157ac)

Hàm sau đây thay đổi một giá trị đơn lẻ trong mảng.
Nó cũng thay đổi tất cả các nút trên đường đi từ phần tử mảng đến
gốc. Đó là các nút tương ứng với các đoạn mà
chỉ số đó là một phần của.

```cpp
void change(int i, int d) {
    i += tree_size;
    while (i > 0) {
        tree[i] += d;
        i /= 2;
    }
}
```

Một ví dụ về thao tác thay đổi. Tất cả các nút trên đường đi đến gốc
đều được chọn.

![](3d604ec96dd9d81bbf21ab0931ceab113a347b72262aee16627fb775255d28e9)

Điều gì sẽ xảy ra nếu chúng ta hoán đổi vai trò của các hàm này? Liệu chúng ta có thể sử dụng
phương pháp hiện tại để trả lời truy vấn (chọn số lượng nút nhỏ nhất phủ một
đoạn cho trước) để sửa đổi trên đoạn và sử dụng phương pháp cập nhật giá trị đơn lẻ
để truy vấn giá trị đơn lẻ? Hóa ra là hoàn toàn có thể.

Hàm $\texttt{change}$ sẽ trông như thế này:

```cpp
void change(int l, int r, int d) {
    l += tree_size;
    r += tree_size;
    while (l <= r) {
        if (l % 2 == 1) tree[l++] += d;
        if (r % 2 == 0) tree[r--] += d;
        l /= 2;
        r /= 2;
    }
}
```

Lưu ý rằng, trong cách biểu diễn mới của chúng ta, để tìm ra một giá trị riêng lẻ,
chúng ta phải tính tổng giá trị của mỗi nút trên đường đi từ chỉ số đến gốc.

```cpp
ll query(int i) {
    ll ans = 0;
    i += tree_size;
    while (i > 0) {
        ans += tree[i];
        i /= 2;
    }
    return ans;
}
```

Cài đặt hoàn chỉnh của phương pháp này có thể được tìm thấy bên dưới. Việc nghĩ ra
giải pháp này hơi khó và đòi hỏi sự hiểu biết sâu sắc về các ý tưởng
xung quanh cây phân đoạn. Tuy nhiên, cài đặt hoàn chỉnh khá ngắn gọn.

```cpp
#include <iostream>
using namespace std;
using ll = long long;

const int TREE_SIZE = 1 << 18;
ll tree[TREE_SIZE * 2];

ll query(int i) {
    ll ans = 0;
    i += TREE_SIZE;
    while (i > 0) {
        ans += tree[i];
        i /= 2;
    }
    return ans;
}

void change(int l, int r, int d) {
    l += TREE_SIZE;
    r += TREE_SIZE;
    while (l <= r) {
        if (l % 2 == 1) tree[l++] += d;
        if (r % 2 == 0) tree[r--] += d;
        l /= 2;
        r /= 2;
    }
}

int main() {
    int n, q;
    cin >> n >> q;

    for (int i = 1; i <= n; ++i) {
        int x;
        cin >> x;
        change(i, i, x);
    }

    for (int qi = 0; qi < q; ++qi) {
        int t;
        cin >> t;
        if (t == 1) {
            int l, r, u;
            cin >> l >> r >> u;
            change(l, r, u);
        } else {
            int k;
            cin >> k;
            cout << query(k) << '\n';
        }
    }
}
```
