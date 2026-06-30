# 1737 - Truy vấn đoạn và Sao chép

Bài toán này có thể được giải bằng *cây phân đoạn bền vững* (persistent segment tree). Cây phân đoạn bền vững cho phép chúng ta truy vấn và sửa đổi các phiên bản lịch sử của cây.

Chúng ta sẽ tạo một cây phân đoạn mới sau mỗi thao tác. Nhận xét quan trọng ở đây là chỉ có $O(\log n)$ nút bị thay đổi mỗi thao tác và phần còn lại có thể được tái sử dụng.

Mỗi thao tác trên cây phân đoạn mất $O(\log n)$ thời gian, do đó độ phức tạp thời gian tổng thể của lời giải là $O((n+q)\log n)$.

Vì mỗi thao tác tạo ra $O(\log n)$ nút, lời giải sử dụng $O(q\log n)$ bộ nhớ.

```cpp
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

struct Node {
    Node *left = nullptr, *right = nullptr;
    ll sum;
};

// Xây dựng cây phân đoạn từ vector v.
// Trả về con trỏ tới cây đã được xây dựng.
Node *build(int l, int r, vector<int> &v) {
    Node *p = new Node();
    if (r - l == 1) {
        p->sum = v[l];
    } else {
        int m = (l + r) / 2;
        p->left = build(l, m, v);
        p->right = build(m, r, v);
        p->sum = p->left->sum + p->right->sum;
    }
    return p;
}

// Thay đổi giá trị tại vị trí k thành x trong cây p.
// Trả về con trỏ tới cây mới.
Node *change(Node *p, int l, int r, int k, int x) {
    Node *n = new Node(*p);
    if (r - l == 1) {
        n->sum = x;
    } else {
        int m = (l + r) / 2;
        if (k < m) {
            n->left = change(p->left, l, m, k, x);
        } else {
            n->right = change(p->right, m, r, k, x);
        }
        n->sum = n->left->sum + n->right->sum;
    }
    return n;
}

// Trả về tổng các giá trị trong đoạn [ql, qr).
ll query(Node *p, int l, int r, int ql, int qr) {
    if (qr <= l || r <= ql) return 0;
    if (ql <= l && r <= qr) return p->sum;
    int m = (l + r) / 2;
    return query(p->left, l, m, ql, qr) + query(p->right, m, r, ql, qr);
}

int main() {
    int n, q;
    cin >> n >> q;

    vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }

    vector<Node *> trees{build(0, n, v)};

    for (int qi = 0; qi < q; ++qi) {
        int t, k;
        cin >> t >> k;
        k--;
        if (t == 1) {
            int a, x;
            cin >> a >> x;
            trees[k] = change(trees[k], 0, n, a - 1, x);
        } else if (t == 2) {
            int l, r;
            cin >> l >> r;
            cout << query(trees[k], 0, n, l - 1, r) << '\n';
        } else {
            trees.push_back(trees[k]);
        }
    }
}
```

## Tài liệu tham khảo

* [CPHB (Sổ tay Lập trình viên Thi đấu)](http://cses.fi/book), Chương 28
* [CP-Algorithms, Cây phân đoạn](https://cp-algorithms.com/data_structures/segment_tree.html)
