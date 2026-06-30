# 2081 - Đường đi độ dài cố định II

## Lời giải 1: Phân tích tâm (Centroid Decomposition)

Bài toán này có thể được giải bằng phân tích tâm (centroid decomposition).

Ý tưởng là đệ quy chia cây thành các cây rời rạc. Ta tìm một
đỉnh tâm của mỗi cây và tính số lượng đường đi có độ dài
từ $k\_1$ đến $k\_2$ đi qua tâm. Sau đó, tất cả
các đường đi chưa được tính hoàn toàn nằm trong các cây con của đỉnh đó. Do đó, ta
có thể loại bỏ tâm khỏi cây và lặp lại quy trình tương tự cho các
cây mới thu được.

Ta sử dụng cây Fenwick để đếm số lượng đỉnh ở các khoảng cách cụ thể từ
tâm.

Tại mỗi bước, kích thước của các cây kết quả sẽ tối đa bằng một nửa
kích thước ban đầu. Điều này có nghĩa là mỗi đỉnh sẽ là một phần của tối đa $O(\log n)$
cây. Vì việc xử lý một đỉnh tương ứng với một truy vấn trên cây Fenwick và mọi
đỉnh của mọi cây đều được xử lý chính xác hai lần, tổng độ phức tạp thời gian
của lời giải là $O(n\log^2n)$.

```cpp
#include <array>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

struct FenwickTree {
    static const int N = 200000;
    array<int, N + 1> tree;
    void add(int k, int d) {
        for (int i = k + 1; i <= N; i += i & -i) {
            tree[i] += d;
        }
    }
    int sum(int k) {
        int s = 0;
        for (int i = k; i > 0; i -= i & -i) {
            s += tree[i];
        }
        return s;
    }
    int sum(int l, int r) { return sum(r + 1) - sum(l); }
} tree;

const int N = 200001;
bool deleted[N];
int n, k1, k2, sizes[N];
vector<int> g[N];
ll answer;

void dfs_sizes(int node, int parent) {
    sizes[node] = 1;
    for (int child : g[node]) {
        if (child == parent || deleted[child]) continue;
        dfs_sizes(child, node);
        sizes[node] += sizes[child];
    }
}

int find_centroid(int node, int parent, int n) {
    for (int child : g[node]) {
        if (child != parent && !deleted[child] && sizes[child] > n / 2) {
            return find_centroid(child, node, n);
        }
    }
    return node;
}

void dfs_add(int node, int parent, int depth, int change) {
    tree.add(depth, change);
    for (int child : g[node]) {
        if (child == parent || deleted[child]) continue;
        dfs_add(child, node, depth + 1, change);
    }
}

void dfs_query(int node, int parent, int depth) {
    answer += tree.sum(k1 - depth, k2 - depth);
    for (int child : g[node]) {
        if (child == parent || deleted[child]) continue;
        dfs_query(child, node, depth + 1);
    }
}

void recurse(int node) {
    dfs_sizes(node, -1);
    int r = find_centroid(node, -1, sizes[node]);
    tree.add(0, 1);
    for (int child : g[r]) {
        if (!deleted[child]) {
            dfs_query(child, r, 1);
            dfs_add(child, r, 1, 1);
        }
    }
    dfs_add(r, -1, 0, -1);
    deleted[r] = true;
    for (int child : g[r]) {
        if (!deleted[child]) {
            recurse(child);
        }
    }
}

int main() {
    cin >> n >> k1 >> k2;

    for (int i = 1; i <= n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    recurse(1);
    cout << answer << '\n';
}
```

## Lời giải 2: Hợp nhất từ nhỏ đến lớn (Small-To-Large Merging)

Có một lời giải khác, đơn giản hơn cho bài toán này. Nó sử dụng một kỹ thuật gọi là
*hợp nhất từ nhỏ đến lớn* kết hợp với cấu trúc dữ liệu *policy-based*.

Cấu trúc dữ liệu *policy-based* không phải là một phần của chuẩn C++, mà chúng được
tích hợp sẵn trong trình biên dịch GNU. Cây cân bằng nhị phân policy-based cho phép ta
truy vấn số lượng phần tử trong một đoạn bằng hàm `order_of_key`.

Sau khi chọn gốc cho cây, ta thực hiện duyệt DFS trên cây. Trong quá trình
duyệt, ta tính số lượng đường đi có độ dài
từ $k\_1$ đến $k\_2$ mà đỉnh cao nhất của chúng là đỉnh hiện tại.

Với kỹ thuật hợp nhất từ nhỏ đến lớn, có thể chứng minh rằng mỗi phần tử sẽ được di chuyển tối
đa $O(\log n)$ lần, làm cho độ phức tạp thời gian tổng thể của lời giải
là $O(n\log^2n)$.

Lưu ý rằng cây policy-based chỉ hỗ trợ các giá trị duy nhất. Ta có thể giải quyết
điều này bằng cách lưu độ sâu trong các `pair` với chỉ số đỉnh là phần tử thứ hai.

```cpp
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

template <typename T>
using indexed_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

int query_range(indexed_set<pair<int, int>> &tree, int l, int r) {
    return tree.order_of_key({r + 1, 0}) - tree.order_of_key({l, 0});
}

const int N = 200001;
int n, k1, k2;
vector<int> g[N];
ll answer;

indexed_set<pair<int, int>> dfs(int node, int parent, int depth) {
    indexed_set<pair<int, int>> dist;
    dist.insert({depth, node});
    for (int child : g[node]) {
        if (child == parent) continue;
        auto child_dist = dfs(child, node, depth + 1);
        if (child_dist.size() > dist.size()) {
            dist.swap(child_dist);
        }
        for (auto [d, s] : child_dist) {
            answer += query_range(dist, k1 - d + 2 * depth, k2 - d + 2 * depth);
        }
        for (auto p : child_dist) dist.insert(p);
    }
    return dist;
}

int main() {
    cin >> n >> k1 >> k2;

    for (int i = 1; i <= n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    dfs(1, -1, 0);
    cout << answer << '\n';
}
```

## Lời giải 3: Hợp nhất cải tiến

Thay vì sử dụng cây policy-based để lưu thông tin về độ sâu của
các đỉnh, ta có thể sử dụng `deque`. Nếu mỗi vị trí của deque tương ứng với một
độ sâu, ta chỉ có thể truy vấn số lượng đỉnh tại một độ sâu cụ thể. Để
truy vấn số lượng đỉnh có độ sâu từ $k\_1$ đến $k\_2$, ta có thể lưu
tổng hậu tố vào deque. Bằng cách đó, mỗi vị trí tương ứng với số lượng
đỉnh có độ sâu lớn hơn hoặc bằng chỉ số của vị trí đó.

Ta sử dụng kỹ thuật hợp nhất từ nhỏ đến lớn nhưng vì kích thước của các cấu trúc dữ liệu đã hợp nhất
tương ứng với độ sâu của các cây con, thay vì kích thước, lời giải
chạy trong thời gian $O(n)$.

```cpp
#include <deque>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

const int N = 200001;
int n, k1, k2;
vector<int> g[N];
ll answer;

void merge(deque<int> &a, deque<int> &b) {
    if (b.size() > a.size()) swap(a, b);
    auto get = [&](int i) {
        if (i < 0) return a.front();
        if (i >= a.size()) return 0;
        return a[i];
    };
    int bs = b.size();
    b.push_back(0);
    for (int i = 0; i < bs; ++i) {
        ll cur_b = b[i] - b[i + 1];
        answer += cur_b * (get(k1 - i) - get(k2 - i + 1));
    }
    for (int i = 0; i < bs; ++i) {
        a[i] += b[i];
    }
}

deque<int> dfs(int node, int parent) {
    deque<int> ret{1};
    for (int child : g[node]) {
        if (child == parent) continue;
        auto child_depths = dfs(child, node);
        child_depths.push_front(child_depths.front());
        merge(ret, child_depths);
    }
    return ret;
}

int main() {
    cin >> n >> k1 >> k2;

    for (int i = 1; i <= n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    dfs(1, -1);
    cout << answer << '\n';
}
```
