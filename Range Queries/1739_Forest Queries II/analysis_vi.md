# 1739 - Truy vấn Rừng II

Bài toán này có thể được giải bằng *cây phân đoạn 2D*. Trong *cây phân đoạn 2D*, mỗi nút chứa một cây phân đoạn thông thường.

Chúng ta truy vấn $O(\log n)$ nút ở cây mức trên cùng và trả lời mỗi truy vấn này trong cây mức thứ hai mất $O(\log n)$ thời gian. Do đó, trả lời một truy vấn đơn lẻ mất $O(\log^2 n)$ thời gian.

Độ phức tạp thời gian tổng thể là $O((n+q)\log^2 n)$.

Cây tiêu tốn $O(n^2)$ bộ nhớ tổng cộng vì mỗi nút trong số $O(n)$ nút ở cây mức trên cùng tiêu tốn $O(n)$ bộ nhớ.

```cpp
#include <iostream>
using namespace std;

const int TREE_SIZE = 1 << 10;
int trees[TREE_SIZE * 2][TREE_SIZE * 2];

// Cộng d vào vị trí x trong cây phân đoạn `tree`.
void add(int *tree, int x, int d) {
    x += TREE_SIZE;
    while (x > 0) {
        tree[x] += d;
        x /= 2;
    }
}

// Cộng d vào vị trí (i, j).
void add(int y, int x, int d) {
    y += TREE_SIZE;
    while (y > 0) {
        add(trees[y], x, d);
        y /= 2;
    }
}

// Trả về tổng các giá trị trong đoạn [x1, x2] trong `tree`.
int query(int *tree, int x1, int x2) {
    x1 += TREE_SIZE;
    x2 += TREE_SIZE;
    int sum = 0;
    while (x1 <= x2) {
        if (x1 % 2 == 1) sum += tree[x1++];
        if (x2 % 2 == 0) sum += tree[x2--];
        x1 /= 2;
        x2 /= 2;
    }
    return sum;
}

// Trả về tổng các giá trị trong hình chữ nhật [y1, y2] x [x1, x2].
int query(int y1, int y2, int x1, int x2) {
    y1 += TREE_SIZE;
    y2 += TREE_SIZE;
    int sum = 0;
    while (y1 <= y2) {
        if (y1 % 2 == 1) sum += query(trees[y1++], x1, x2);
        if (y2 % 2 == 0) sum += query(trees[y2--], x1, x2);
        y1 /= 2;
        y2 /= 2;
    }
    return sum;
}

const int N = 1001;
int forest[N][N];

int main() {
    int n, q;
    cin >> n >> q;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            char c;
            cin >> c;
            if (c == '*') {
                forest[i][j] = 1;
                add(i, j, 1);
            }
        }
    }

    for (int qi = 0; qi < q; ++qi) {
        int t;
        cin >> t;
        if (t == 1) {
            int i, j;
            cin >> i >> j;
            if (forest[i][j]) {
                add(i, j, -1);
                forest[i][j] = 0;
            } else {
                add(i, j, 1);
                forest[i][j] = 1;
            }
        } else {
            int y1, x1, y2, x2;
            cin >> y1 >> x1 >> y2 >> x2;
            cout << query(y1, y2, x1, x2) << '\n';
        }
    }
}
```
