# 2072 - Cut and Paste

Treap là một cây tìm kiếm nhị phân có thể được sử dụng để mô phỏng các thao tác cắt/dán một cách hiệu quả.

Trong một treap, mỗi nút được gán một trọng số ngẫu nhiên, và cấu trúc của cây được xác định bởi tính chất đống (heap property), nghĩa là trọng số của nút cha luôn lớn hơn hoặc bằng trọng số của các nút con. Tính chất này đảm bảo rằng chiều cao của cây rất có thể tỷ lệ với logarit của số lượng nút, đảm bảo các thao tác split/merge hiệu quả. Các thao tác merge và split hoạt động, trung bình, trong thời gian $O(\log n)$, với $n$ là kích thước của cây.

Độ phức tạp thời gian của lời giải là $O((n + m) \log n)$ vì mất $O(n\log n)$ thời gian để xây dựng cây và $O(m\log n)$ thời gian để xử lý các truy vấn. Trong cài đặt, chúng ta dự trữ trước một mảng các nút treap. Bằng cách này, chúng ta không phải lo lắng về việc giải phóng bộ nhớ, và ngoài ra nó còn nhanh hơn việc cấp phát từng nút riêng lẻ.

```cpp
#include <chrono>
#include <iostream>
#include <random>
#include <tuple>
using namespace std;

mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct Treap {
    Treap *left = nullptr, *right = nullptr;
    int v, weight, sz = 1;
    Treap() {}
    Treap(int v) : v(v), weight(rng()) {}

    static void update(Treap *node) {
        node->sz = 1;
        if (node->left) node->sz += node->left->sz;
        if (node->right) node->sz += node->right->sz;
    }

    // Hợp nhất hai treap a và b.
    static Treap *merge(Treap *a, Treap *b) {
        if (!a) return b;
        if (!b) return a;
        Treap *r;
        if (a->weight < b->weight) {
            a->right = merge(a->right, b);
            r = a;
        } else {
            b->left = merge(a, b->left);
            r = b;
        }
        update(r);
        return r;
    }

    // Chia treap thành hai treap.
    // Treap đầu tiên trong cặp kết quả sẽ chứa k nút đầu tiên của a.
    static pair<Treap *, Treap *> split(Treap *a, int k) {
        if (!a) return {nullptr, nullptr};
        int al = a->left ? a->left->sz : 0;
        Treap *r;
        if (al >= k) {
            tie(r, a->left) = split(a->left, k);
            update(a);
            return {r, a};
        }
        tie(a->right, r) = split(a->right, k - al - 1);
        update(a);
        return {a, r};
    }

    static void print(Treap *a, char endl = '\n') {
        if (a->left) print(a->left, '\0');
        cout << (char)a->v;
        if (a->right) print(a->right, '\0');
        if (endl) cout << endl;
    }
};

Treap *new_treap(int v) {
    const int pool_sz = 2e5;
    static Treap pool[pool_sz];
    static Treap *pool_ptr = pool;

    *pool_ptr = Treap(v);
    return pool_ptr++;
}

int main() {
    Treap *root = nullptr;

    int n, m;
    cin >> n >> m;

    string s;
    cin >> s;

    for (char c : s) {
        root = Treap::merge(root, new_treap(c));
    }

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        auto [r0, r1] = Treap::split(root, a - 1);
        auto [r2, r3] = Treap::split(r1, b - a + 1);
        root = Treap::merge(r0, r3);
        root = Treap::merge(root, r2);
    }

    Treap::print(root);
}
```

## Tài liệu tham khảo

* [Treap (Wikipedia)](https://en.wikipedia.org/wiki/Treap)
