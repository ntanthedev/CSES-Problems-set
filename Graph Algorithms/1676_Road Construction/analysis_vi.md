# 1676 - Xây dựng đường giao thông

Chúng tôi giải bài toán bằng cấu trúc union-find. Chúng tôi duy trì số lượng thành phần liên thông riêng biệt và kích thước của thành phần lớn nhất. Khi xây dựng một con đường mới giữa hai thành phố $a$ và $b$, trước tiên ta kiểm tra xem chúng đã thuộc cùng một thành phần liên thông hay chưa. Nếu chưa, ta hợp nhất các thành phần liên thông tương ứng, giảm số lượng thành phần liên thông đi một và kiểm tra xem thành phần mới được tạo có lớn hơn thành phần lớn nhất trước đó hay không.

Độ phức tạp thời gian của lời giải là $O(n + m \alpha(n))$, trong đó $\alpha(n)$ là hàm Ackermann ngược.

```cpp
#include <algorithm>
#include <iostream>
#include <numeric>

using namespace std;
const int N = 100001;

int sz[N];
int link[N];

int find(int x) {
    if (link[x] == x) {
        return x;
    }
    return link[x] = find(link[x]);
}

bool same(int x, int y) {
    return find(x) == find(y);
}

void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (sz[x] < sz[y]) {
        swap(x, y);
    }
    sz[x] += sz[y];
    link[y] = x;
}

int main() {
    int n, m;
    cin >> n >> m;

    fill(sz, sz + n + 1, 1);
    iota(link, link + n + 1, 0);

    int n_components = n;
    int largest_size = 1;

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        if (!same(a, b)) {
            unite(a, b);
            --n_components;
            largest_size = max(sz[find(a)], largest_size);
        }
        cout << n_components << ' ' << largest_size << '\n';
    }
}
```

## Tài liệu tham khảo

* [CPHB (Sổ tay lập trình viên thi đấu)](http://cses.fi/book),
  Chương 15.2
* [CP-Algorithms, Disjoint Set Union / Union Find](https://cp-algorithms.com/data_structures/disjoint_set_union.html)
