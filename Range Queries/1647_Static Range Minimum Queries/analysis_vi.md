# 1647 - Static Range Minimum Queries

## Cách tiếp cận thứ nhất: Cây phân đoạn

Vì không có phép toán nghịch đảo cho giá trị nhỏ nhất, một mảng tĩnh sẽ không đủ. Tuy nhiên, cây phân đoạn xử lý các truy vấn một cách dễ dàng.

```cpp
#include <iostream>
using namespace std;

const int TREE_SIZE = 1 << 18;
int tree[TREE_SIZE * 2];

void change(int i, int x) {
    i += TREE_SIZE;
    tree[i] = x;
    while (i > 1) {
        i /= 2;
        tree[i] = min(tree[i * 2], tree[i * 2 + 1]);
    }
}

// Returns the minimum value in range [l, r]
int get_min(int l, int r) {
    int res = (int)1e9;
    l += TREE_SIZE;
    r += TREE_SIZE;
    while (l <= r) {
        if (l % 2 == 1) res = min(res, tree[l++]);
        if (r % 2 == 0) res = min(res, tree[r--]);
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
    }

    for (int qi = 0; qi < q; ++qi) {
        int l, r;
        cin >> l >> r;
        cout << get_min(l, r) << '\n';
    }
}
```

### Tài liệu tham khảo thêm về cây phân đoạn

* [CPHB (Competitive Programmer's Handbook)](http://cses.fi/book), Chương 9
* [CP-Algorithms, Segment Tree](https://cp-algorithms.com/data_structures/segment_tree.html)

## Cách tiếp cận thứ hai: Bảng thưa (Sparse table)

Một cách khác để giải bài toán này là sử dụng bảng thưa (sparse table). Bảng thưa là một cấu trúc dữ liệu có khả năng trả lời các truy vấn trong thời gian $O(1)$. Việc xây dựng bảng tốn $O(n \log n)$ thời gian.

Lưu ý rằng, trái ngược với cây phân đoạn, bảng thưa chỉ được xây dựng một lần và không thể thay đổi sau đó.

```cpp
#include <iostream>
using namespace std;

const int N = 200000;
const int L = 20;

int x[N];
int table[N][L];

// Returns the minimum value in range [l, r)
int get_min(int l, int r) {
    // __lg(x) returns the base-2 logarithm of x, rounded down.
    // With it, we'll figure out the largest power of two
    // that is not larger than the length of the query.
    int i = __lg(r - l);
    return min(table[l][i], table[r - (1 << i)][i]);
}

int main() {
    int n, q;
    cin >> n >> q;

    for (int i = 0; i < n; ++i) {
        cin >> x[i];
        table[i][0] = x[i];
    }

    for (int j = 0; (1 << j) < n; ++j) {
        for (int i = 0; i + (1 << j) < n; ++i) {
            table[i][j + 1] = min(table[i][j], table[i + (1 << j)][j]);
        }
    }

    for (int qi = 0; qi < q; ++qi) {
        int l, r;
        cin >> l >> r;
        l--;
        cout << get_min(l, r) << '\n';
    }
}
```

### Tài liệu tham khảo thêm về bảng thưa

* [CPHB (Competitive Programmer's Handbook)](http://cses.fi/book), Chương 9
* [CP-Algorithms, Sparse Table](https://cp-algorithms.com/data_structures/sparse-table.html)
