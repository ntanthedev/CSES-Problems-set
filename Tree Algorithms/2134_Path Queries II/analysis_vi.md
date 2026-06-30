# 2134 - Truy vấn đường đi II

Bài toán này có thể được giải bằng một kỹ thuật gọi là *heavy-light
decomposition*.

Ta sẽ gọi, với mỗi đỉnh, đỉnh con có cây con lớn nhất (theo kích thước) là đỉnh con
*nặng*. Mọi đỉnh con khác là đỉnh con *nhẹ*.

Các đỉnh con *nặng* và *nhẹ* sẽ phân hoạch cây thành các đường đi. Một đường đi bao gồm
các đỉnh *nặng* lặp lại. Với mỗi đỉnh, hãy lưu một con trỏ trỏ đến
đầu cuối của đường đi mà đỉnh đó thuộc về.

![](908b4d6363d0991d77d3aaf11c5cdd885c6b0e170ebcf43c71565825f69b5f8f)

Nhận xét chính ở đây là đường đi từ bất kỳ đỉnh nào đến gốc sẽ bao gồm
$O(\log n)$ các đường đi *nặng* này. Bản thân điều này có vẻ không phải là một
kỹ thuật mạnh mẽ. Ta cần thêm một vài nhận xét nữa.

Ta sẽ đưa đỉnh con *nặng* lên vị trí đầu tiên trong danh sách kề cho mỗi
đỉnh. Sau đó, ta sẽ thực hiện duyệt DFS và lưu các đỉnh – theo thứ tự
chúng được thăm – vào một mảng. Bất kỳ đỉnh con nặng nào sẽ theo sau đỉnh cha của nó trong
mảng DFS. Hơn nữa, mỗi đường đi nặng tương ứng với một đoạn liên tiếp
trong mảng.

Bây giờ, làm thế nào để phân hoạch một đường đi giữa hai đỉnh thành các đường đi nặng? Ta có thể nghĩ
về điều này tương tự như việc tìm tổ tiên chung thấp nhất của hai đỉnh. Ta
tham lam di chuyển đỉnh thấp hơn trong hai đỉnh lên trên cho đến khi hai đỉnh gặp nhau. Nếu ta kết hợp
mảng DFS với cây phân đoạn, ta có thể truy vấn hiệu quả giá trị lớn nhất trong quá trình
này. Mỗi khi ta di chuyển một đỉnh, ta sẽ thực hiện một truy vấn trên cây phân đoạn.

Một truy vấn đơn lẻ sẽ chia đường đi giữa hai đỉnh thành $O(\log n)$ phần. Mỗi
truy vấn cây phân đoạn trong số $O(\log n)$ truy vấn tốn $O(\log n)$ thời gian. Do đó,
tổng độ phức tạp thời gian là $O(n+q\log^2n)$.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// Cây phân đoạn này hỗ trợ các thao tác sau:
// 1. SegmentTree(v) xây dựng cây từ vector v.
// 2. set(k, x) đặt giá trị tại vị trí k thành x.
// 3. query(l, r) trả về giá trị lớn nhất trong đoạn [l, r].
struct SegmentTree {
    int n;
    vector<int> tree;

    SegmentTree(vector<int> &v) {
        n = 1;
        while (n < v.size()) n *= 2;
        tree.resize(n * 2);
        for (int i = 0; i < v.size(); ++i) {
            tree[i + n] = v[i];
        }
        for (int i = n - 1; i > 0; --i) {
            tree[i] = max(tree[i * 2], tree[i * 2 + 1]);
        }
    }

    void set(int k, int x) {
        k += n;
        tree[k] = x;
        while (k > 1) {
            k /= 2;
            tree[k] = max(tree[k * 2], tree[k * 2 + 1]);
        }
    }

    int query(int l, int r) {
        int ans = 0;
        for (l += n, r += n; l <= r; l /= 2, r /= 2) {
            if (l % 2 == 1) ans = max(ans, tree[l++]);
            if (r % 2 == 0) ans = max(ans, tree[r--]);
        }
        return ans;
    }
};

using graph = vector<vector<int>>;

// Heavy-light decomposition.
// Phân hoạch cây đã cho thành các đường đi nặng và nhẹ.
// Cung cấp các hàm sau:
// 1. `position(x)`: Trả về vị trí của đỉnh x trong mảng thứ tự DFS.
// 2. `subtree(x)`: Trả về đoạn trong mảng thứ tự DFS tương ứng với
//                  cây con của đỉnh x.
// 3. `path_query(a, b, f)`: Chia đường đi giữa hai đỉnh a và b thành
//                           O(log n) đoạn liên tiếp của mảng thứ tự DFS.
//                           Gọi f(l, r) cho mỗi đoạn [l, r] như vậy.
//                           Hàm f có thể, ví dụ, truy vấn/cập nhật một
//                           cây phân đoạn.
struct HLD {
    int n;
    graph &g;
    vector<int> parent;
    vector<int> jump;
    vector<int> total;
    vector<int> order;

    HLD(graph &g) : n(g.size()), g(g), parent(n), jump(n), total(n), order(n) {
        dfs_size(0);
        int order_index = 0;
        dfs_hld(0, order_index);
    }

    template <typename F>
    void path_query(int a, int b, F f) {
        for (;; a = parent[jump[a]]) {
            if (order[a] < order[b]) swap(a, b);
            if (order[jump[a]] <= order[b]) {
                f(order[b], order[a]);
                return;
            }
            f(order[jump[a]], order[a]);
        }
    }

    int position(int x) { return order[x]; }
    pair<int, int> subtree(int x) {
        return {order[x], order[x] + total[x] - 1};
    }

private:
    void dfs_size(int node) {
        total[node] = 1;
        for (auto &child : g[node]) {
            g[child].erase(find(g[child].begin(), g[child].end(), node));
            dfs_size(child);
            total[node] += total[child];
            if (total[child] > total[g[node][0]]) {
                swap(child, g[node][0]);
            }
        }
    }

    void dfs_hld(int node, int &order_index) {
        order[node] = order_index++;
        for (auto child : g[node]) {
            parent[child] = node;
            if (child == g[node][0]) {
                jump[child] = jump[node];
            } else {
                jump[child] = child;
            }
            dfs_hld(child, order_index);
        }
    }
};

int main() {
    int n, q;
    cin >> n >> q;

    vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }

    graph g(n);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    HLD hld(g);

    vector<int> initial(n);
    for (int i = 0; i < n; ++i) {
        initial[hld.position(i)] = v[i];
    }
    SegmentTree tree(initial);

    for (int qi = 0; qi < q; ++qi) {
        int t;
        cin >> t;
        if (t == 1) {
            int s, x;
            cin >> s >> x;
            tree.set(hld.position(s - 1), x);
        } else {
            int a, b;
            cin >> a >> b;
            int ans = 0;
            auto update_ans = [&](int l, int r) {
                ans = max(ans, tree.query(l, r));
            };
            hld.path_query(a - 1, b - 1, update_ans);
            cout << ans << '\n';
        }
    }
}
```

Lưu ý rằng cách chúng ta cài đặt HLD, bằng cách sửa đổi thứ tự của danh sách
kề, cho phép ta thực hiện các truy vấn trên cây con ngoài các truy vấn đường đi. Không phải tất cả
các cài đặt đều hỗ trợ điều này.

## Tài liệu tham khảo

* [Codeforces, *Easiest HLD with subtree queries* by adamant](https://codeforces.com/blog/entry/53170)
* [CP-Algorithms, Heavy-light decomposition](https://cp-algorithms.com/graph/hld.html)
