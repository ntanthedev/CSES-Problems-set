# 1736 - Truy vấn đa thức

Bài toán này có thể được giải bằng *cây phân đoạn lười biếng (lazy segment tree)*.

Chúng ta hãy tập trung vào một phiên bản tổng quát hơn của bài toán, nơi một cấp số cộng
bất kỳ có thể được thêm vào.

Mọi cấp số cộng $a,a+d,a+2d,\dots$ có thể được xác định bởi hai số
$a$ và $d$, phần tử đầu tiên của dãy và công sai giữa các phần tử liên tiếp.

Làm thế nào để tính tổng của $n$ phần tử đầu tiên trong một cấp số cộng? Đầu tiên, hãy
để ý rằng $a$ được lặp lại trong mỗi số hạng. Do đó chúng ta có thể lấy
tổng $n\cdot a$ và tập trung vào dãy $0,d,2d,\dots,(n-1)d$.

Nhắc lại công thức tính tổng nổi tiếng

$$0+1+2+\dots+(n-1)=\frac{n(n-1)}{2}.$$

Từ công thức trên chúng ta có thể suy ra

$$0+d+2d+\dots+d(n-1)=d\frac{n(n-1)}{2}.$$

Kết luận, tổng của $n$ phần tử đầu tiên trong bất kỳ cấp số cộng nào
$a,a+d,a+2d,\dots$ bằng

$$na+d\frac{n(n-1)}{2}.$$

Điều này có thể được cài đặt bằng ba mảng cho cây phân đoạn:

1. `sum` lưu tổng các giá trị trong đoạn của mỗi nút
2. `lazy_a` lưu giá trị bắt đầu của dãy cần được thêm vào các phần tử trong đoạn của nút
3. `lazy_d` lưu công sai giữa các phần tử liên tiếp trong dãy cần được thêm vào các phần tử trong đoạn của nút

Nói cách khác, các giá trị $a$ và $d$, của `lazy_a` và `lazy_d` tương ứng,
tương ứng với dãy

$$a,a+d,a+2d,\dots$$

Các giá trị *lười biếng* chỉ áp dụng cho các nút con của một nút – sự thay đổi đã được
tính trong tổng của nút tương ứng.

Khi chúng ta đẩy một cấp số cộng vào hai nút con của một nút trong cây phân đoạn,
dãy của nút con bên phải sẽ bắt đầu từ giá trị
$a+d\cdot\textrm{length}$, trong đó $\mathrm{length}$ là kích thước của đoạn
tương ứng với nút con bên trái.

```cpp
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

// Cài đặt cây phân đoạn lười biếng này hỗ trợ các thao tác sau:
//  1. add(l, r, x): trong đoạn [l, r), thêm x + 0 vào phần tử đầu tiên,
//                                        x + 1 vào phần tử thứ hai,
//                                        x + 2 vào phần tử thứ ba và cứ tiếp tục
//  3. query(l, r): tính tổng các giá trị trong đoạn [l, r)
struct Tree {
    int n;
    vector<ll> sum;
    vector<ll> lazy_a;
    vector<ll> lazy_d;

    Tree(int n) : n(n), sum(n * 4), lazy_a(n * 4), lazy_d(n * 4) {}

    void add(int s, int l, int r, int ql, int qr, int x) {
        if (r <= ql || qr <= l) return;
        if (ql <= l && r <= qr) {
            apply(s, r - l, x + (l - ql), 1);
            return;
        }
        push(s, r - l);
        int m = (l + r) / 2;
        add(s * 2 + 0, l, m, ql, qr, x);
        add(s * 2 + 1, m, r, ql, qr, x);
        sum[s] = sum[s * 2] + sum[s * 2 + 1];
    }

    ll query(int s, int l, int r, int ql, int qr) {
        if (r <= ql || qr <= l) return 0;
        if (ql <= l && r <= qr) return sum[s];
        push(s, r - l);
        int m = (l + r) / 2;
        return query(s * 2, l, m, ql, qr) + query(s * 2 + 1, m, r, ql, qr);
    }

    void push(int s, int len) {
        apply(s * 2 + 0, len / 2, lazy_a[s], lazy_d[s]);
        apply(s * 2 + 1, (len + 1) / 2, lazy_a[s] + len / 2 * lazy_d[s],
              lazy_d[s]);
        lazy_a[s] = 0;
        lazy_d[s] = 0;
    }

    void apply(int s, int len, ll a, ll d) {
        sum[s] += a * len + d * ll(len - 1) * len / 2;
        lazy_a[s] += a;
        lazy_d[s] += d;
    }

    void add(int l, int r, int x) { add(1, 0, n, l, r, x); }
    ll query(int l, int r) { return query(1, 0, n, l, r); }
};

int main() {
    int n, q;
    cin >> n >> q;

    Tree tree(n);

    for (int i = 0; i < n; ++i) {
        int t;
        cin >> t;
        tree.add(i, i + 1, t);
    }

    for (int qi = 0; qi < q; ++qi) {
        int t, l, r;
        cin >> t >> l >> r;
        l--;
        if (t == 1) {
            tree.add(l, r, 1);
        } else {
            cout << tree.query(l, r) << '\n';
        }
    }
}
```

## Tài liệu tham khảo

* [CPHB (Sổ tay Lập trình viên Thi đấu)](http://cses.fi/book), Chương 28
* [CP-Algorithms, Cây phân đoạn](https://cp-algorithms.com/data_structures/segment_tree.html)
