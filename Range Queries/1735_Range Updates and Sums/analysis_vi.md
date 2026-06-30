# 1735 - Cập nhật và tính tổng trên đoạn

Bài toán này có thể được giải bằng *cây phân đoạn lười biếng (lazy segment tree)*.

Chúng ta sẽ sử dụng ba mảng cho cây phân đoạn:

1. `sum` lưu tổng các giá trị trong đoạn của mỗi nút
2. `lazy_add` lưu tổng cần được thêm vào mỗi giá trị trong đoạn của nút
3. `lazy_set` lưu giá trị mà mỗi phần tử trong đoạn của nút cần được gán thành

Các giá trị *lười biếng* chỉ áp dụng cho các nút con của một nút – sự thay đổi đã được
tính trong tổng của nút tương ứng.

Khi chúng ta đẩy các cập nhật lười biếng xuống dưới trong cây, chúng ta phải cẩn thận để
kết hợp chúng một cách chính xác. Ví dụ, một thao tác gán đè lên tất cả các thao tác thêm
trước đó.

```cpp
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

// Cài đặt cây phân đoạn lười biếng này hỗ trợ các thao tác sau:
//  1. add(l, r, x): thêm x vào mọi phần tử trong đoạn [l, r)
//  2. set(l, r, x): gán mọi phần tử trong đoạn [l, r) thành x
//  3. query(l, r): tính tổng các giá trị trong đoạn [l, r)
struct Tree {
    int n;
    vector<ll> sum;
    vector<ll> lazy_add;
    vector<ll> lazy_set;

    Tree(int n) : n(n), sum(n * 4), lazy_add(n * 4), lazy_set(n * 4) {}

    void add(int s, int l, int r, int ql, int qr, int x) {
        if (r <= ql || qr <= l) return;
        if (ql <= l && r <= qr) {
            apply_add(s, r - l, x);
            return;
        }
        push(s, r - l);
        int m = (l + r) / 2;
        add(s * 2 + 0, l, m, ql, qr, x);
        add(s * 2 + 1, m, r, ql, qr, x);
        sum[s] = sum[s * 2] + sum[s * 2 + 1];
    }

    void set(int s, int l, int r, int ql, int qr, int x) {
        if (r <= ql || qr <= l) return;
        if (ql <= l && r <= qr) {
            apply_set(s, r - l, x);
            return;
        }
        push(s, r - l);
        int m = (l + r) / 2;
        set(s * 2 + 0, l, m, ql, qr, x);
        set(s * 2 + 1, m, r, ql, qr, x);
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
        if (lazy_set[s]) {
            apply_set(s * 2, len / 2, lazy_set[s]);
            apply_set(s * 2 + 1, (len + 1) / 2, lazy_set[s]);
            lazy_set[s] = 0;
        }
        if (lazy_add[s]) {
            apply_add(s * 2, len / 2, lazy_add[s]);
            apply_add(s * 2 + 1, (len + 1) / 2, lazy_add[s]);
            lazy_add[s] = 0;
        }
    }

    void apply_add(int s, int len, ll x) {
        sum[s] += x * len;
        lazy_add[s] += x;
    }

    void apply_set(int s, int len, ll x) {
        sum[s] = x * len;
        lazy_add[s] = 0;
        lazy_set[s] = x;
    }

    void add(int l, int r, int x) { add(1, 0, n, l, r, x); }
    void set(int l, int r, int x) { set(1, 0, n, l, r, x); }
    ll query(int l, int r) { return query(1, 0, n, l, r); }
};

int main() {
    int n, q;
    cin >> n >> q;

    Tree tree(n);

    for (int i = 0; i < n; ++i) {
        int t;
        cin >> t;
        tree.set(i, i + 1, t);
    }

    for (int qi = 0; qi < q; ++qi) {
        int t, l, r;
        cin >> t >> l >> r;
        l--;
        if (t == 1) {
            int x;
            cin >> x;
            tree.add(l, r, x);
        } else if (t == 2) {
            int x;
            cin >> x;
            tree.set(l, r, x);
        } else {
            cout << tree.query(l, r) << '\n';
        }
    }
}
```

## Tài liệu tham khảo

* [CPHB (Sổ tay Lập trình viên Thi đấu)](http://cses.fi/book), Chương 28
* [CP-Algorithms, Cây phân đoạn](https://cp-algorithms.com/data_structures/segment_tree.html)
