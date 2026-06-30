# 1143 - Hotel Queries

## Cách tiếp cận thứ nhất: Tìm kiếm nhị phân thông thường, $O(q \log^2 n)$

Với tìm kiếm nhị phân và một cây phân đoạn thông thường, bài toán này có thể được giải một cách trực tiếp. Mỗi bước tìm kiếm nhị phân thực hiện $O(\log n)$ truy vấn trên cây phân đoạn, mỗi truy vấn tốn $O(\log n)$ thời gian. Do đó, trả lời tất cả các truy vấn tốn tổng cộng $O(q \log^2 n)$ thời gian.

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
        tree[i] = max(tree[i * 2], tree[i * 2 + 1]);
    }
}

// Returns the maximum value in range [l, r]
int get_max(int l, int r) {
    int res = 0;
    l += TREE_SIZE;
    r += TREE_SIZE;
    while (l <= r) {
        if (l % 2 == 1) res = max(res, tree[l++]);
        if (r % 2 == 0) res = max(res, tree[r--]);
        l /= 2;
        r /= 2;
    }
    return res;
}

const int N = 200001;
int h[N];

int main() {
    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; ++i) {
        cin >> h[i];
        change(i, h[i]);
    }

    for (int i = 1; i <= m; ++i) {
        int x;
        cin >> x;
        if (tree[1] < x) {
            cout << 0 << ' ';
        } else {
            int l = 1, r = n;
            while (l < r) {
                int m = (l + r) / 2;
                if (get_max(1, m) < x) {
                    l = m + 1;
                } else {
                    r = m;
                }
            }
            h[l] -= x;
            change(l, h[l]);
            cout << l << ' ';
        }
    }
    cout << '\n';
}
```

## Cách tiếp cận thứ hai: Tìm kiếm nhị phân trên cây phân đoạn, $O(q \log n)$

Cấu trúc đặc biệt của cây phân đoạn cho phép ta thực hiện tìm kiếm nhị phân bên trong cây.

Quá trình tìm kiếm bắt đầu từ nút gốc với đoạn truy vấn là toàn bộ mảng. Quá trình tiếp tục bằng cách di chuyển đến nút con bên trái hoặc bên phải của nút hiện tại – mỗi lần thu hẹp một nửa đoạn truy vấn. Nếu có khách sạn phù hợp trên đoạn tương ứng với nút con trái, nút con trái sẽ được chọn, nếu không thì nút con phải sẽ được chọn. Cây phân đoạn có độ cao $O(\log n)$. Do đó, tìm kiếm nhị phân tốn $O(\log n)$ thời gian. Vì vậy, trả lời tất cả các truy vấn tốn tổng cộng $O(q \log n)$ thời gian.

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
        tree[i] = max(tree[i * 2], tree[i * 2 + 1]);
    }
}

// Returns the index of the first value larger than x
int query(int x) {
    int s = 1;
    while (s < TREE_SIZE) {
        // The index of the left child is s * 2.
        // The index of the right child is s * 2 + 1.
        s = s * 2 + (tree[s * 2] < x);
    }
    return s - TREE_SIZE;
}

const int N = 200001;
int h[N];

int main() {
    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; ++i) {
        cin >> h[i];
        change(i, h[i]);
    }

    for (int i = 1; i <= m; ++i) {
        int x;
        cin >> x;
        if (tree[1] < x) {
            cout << 0 << ' ';
        } else {
            int pos = query(x);
            h[pos] -= x;
            change(pos, h[pos]);
            cout << pos << ' ';
        }
    }
    cout << '\n';
}
```

## Tài liệu tham khảo

* [CPHB (Competitive Programmer's Handbook)](http://cses.fi/book), Chương 9
* [CP-Algorithms, Segment Tree](https://cp-algorithms.com/data_structures/segment_tree.html)
