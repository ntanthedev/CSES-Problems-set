# 2080 - Đường đi độ dài cố định I

## Lời giải 1: Phân tích tâm (Centroid Decomposition)

Bài toán này có thể được giải bằng một kỹ thuật gọi là phân tích tâm (centroid decomposition).

Ý tưởng là đệ quy chia cây thành các cây rời rạc. Ta bắt đầu bằng cách
chọn một đỉnh từ cây. Sau đó, ta tính số lượng đường đi độ dài
$k$ đi qua đỉnh được chọn. Sau đó, tất cả các đường đi chưa được tính
hoàn toàn nằm trong các cây con của đỉnh đó. Do đó, ta có thể loại bỏ
đỉnh được chọn và lặp lại quy trình tương tự cho các cây mới thu được.

Lời giải sẽ quá chậm nếu mỗi lần ta chọn đỉnh một cách ngẫu nhiên. Ý
tưởng chính là chọn đỉnh sao cho nó là tâm của cây, tức là một đỉnh
sao cho khi nó được chọn làm gốc của cây, mỗi cây con có tối đa
$\lfloor n/2 \rfloor$ đỉnh.

Nếu ta chọn một đỉnh là tâm, kích thước của các cây kết quả sẽ tối đa bằng
một nửa kích thước ban đầu. Điều này có nghĩa là mỗi đỉnh sẽ là một phần của tối đa
$O(\log n)$ cây. Vì mọi đỉnh của mọi cây đều được xử lý một lần, tổng độ phức tạp
thời gian của lời giải là $O(n\log n)$.

Tại mỗi bước, một đỉnh tâm có thể được tìm bằng thuật toán tham lam, hoạt động
như sau: chọn gốc cho cây, duyệt đệ quy từ gốc, mỗi lần chọn
một đỉnh con có kích thước cây con ít nhất $\lfloor n/2 \rfloor$. Nếu không có
đỉnh con như vậy, quá trình duyệt đã đến một đỉnh tâm.

Khi đã tìm được tâm, ta có thể bắt đầu đếm các đường đi. Để làm
điều này, ta sử dụng một mảng `dist`. Mỗi vị trí $i$ của `dist` lưu số lượng
đỉnh ở khoảng cách $i$ từ tâm. Để đảm bảo rằng các đường đi được đếm không
chỉ nằm trong một cây con duy nhất và mỗi đường đi chỉ được đếm
một lần, ta đếm số lượng đường đi kết thúc trong một cây con trước khi cập nhật mảng
`dist` với khoảng cách của các đỉnh trong cây con đó.

Mảng `dist` được tái sử dụng cho tất cả các cây được xử lý riêng lẻ. Vì vậy, ta
phải đặt lại nó giữa các lần gọi đệ quy.

```cpp
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

const int N = 200001;
bool deleted[N];
int n, k, sizes[N];
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

int dist[N];

void dfs_add(int node, int parent, int depth, int change) {
    dist[depth] += change;
    for (int child : g[node]) {
        if (child == parent || deleted[child]) continue;
        dfs_add(child, node, depth + 1, change);
    }
}

void dfs_query(int node, int parent, int depth) {
    if (k - depth >= 0) answer += dist[k - depth];
    for (int child : g[node]) {
        if (child == parent || deleted[child]) continue;
        dfs_query(child, node, depth + 1);
    }
}

void recurse(int node) {
    dfs_sizes(node, -1);
    int r = find_centroid(node, -1, sizes[node]);
    dist[0] = 1;
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
    cin >> n >> k;

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

Có một lời giải khác, đơn giản hơn cho bài toán này. Nó sử dụng một kỹ thuật
đôi khi được gọi là *hợp nhất từ nhỏ đến lớn*. Cài đặt chỉ có một
lần duyệt cây.

Sau khi chọn gốc cho cây, ta thực hiện duyệt DFS trên cây. Trong quá trình
duyệt, ta tính số lượng đường đi đi qua mỗi đỉnh. Bất kỳ đường đi nào trong
cây đều có một đỉnh cao nhất: đỉnh gần gốc nhất. Ta sẽ
tính mỗi đường đi chỉ một lần, tại đỉnh cao nhất của nó.

Để đảm bảo ta chỉ đếm các đường đi độ dài $k$, ta sử dụng thực tế là
khoảng cách giữa hai đỉnh $a$ và $b$ trong cây bằng

$$\textrm{depth}(a)+\textrm{depth}(b)-2\cdot\textrm{depth}(c),$$

trong đó $c$ là đỉnh cao nhất trên đường đi giữa $a$ và $b$, còn được gọi là tổ
tiên chung thấp nhất của $a$ và $b$. Với điều này, việc tìm số lượng đường đi độ
dài $k$ qua đỉnh $x$ tương ứng với việc tìm số cách chọn
hai đỉnh $a$ và $b$ từ các cây con khác nhau của $x$ với điều kiện sau:

$$\textrm{depth}(a)+\textrm{depth}(b)-2\cdot\textrm{depth}(x)=k.$$

Ta tạo một `map` cho mỗi đỉnh, lưu độ sâu của các đỉnh trong
cây con của đỉnh đó. Ta sử dụng kỹ thuật *hợp nhất từ nhỏ đến lớn* để
hợp nhất `map` của một đỉnh vào `map` của đỉnh cha một cách hiệu quả: nếu map của một đỉnh con lớn hơn
map của đỉnh cha, ta hoán đổi các cấu trúc dữ liệu trước khi
hợp nhất. Điều này có nghĩa là thay vì di chuyển các phần tử từ map của đỉnh con sang
map của đỉnh cha, ta di chuyển chúng từ map nhỏ hơn sang map lớn hơn.

Có thể chứng minh rằng mỗi phần tử sẽ được di chuyển tối đa $O(\log n)$ lần,
làm cho độ phức tạp thời gian tổng thể của lời giải là $O(n\log^2n)$.

```cpp
#include <iostream>
#include <map>
#include <vector>
using namespace std;
using ll = long long;

const int N = 200001;
int n, k;
vector<int> g[N];
ll answer;

map<int, int> dfs(int node, int parent, int depth) {
    map<int, int> dist;
    dist[depth] = 1;
    for (int child : g[node]) {
        if (child == parent) continue;
        auto child_dist = dfs(child, node, depth + 1);
        if (child_dist.size() > dist.size()) {
            swap(dist, child_dist);
        }
        for (auto [d, amt] : child_dist) {
            answer += 1ll * dist[k - d + 2 * depth] * amt;
        }
        for (auto [d, amt] : child_dist) {
            dist[d] += amt;
        }
    }
    return dist;
}

int main() {
    cin >> n >> k;

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

Thay vì sử dụng `map` để lưu thông tin về độ sâu của các đỉnh trong
mỗi cây con, ta sử dụng `deque`. Ngoài ra, lời giải này hoạt động theo cách
rất giống với lời giải trước đó.

Lưu ý rằng, trái ngược với lời giải trước, chỉ số của `deque` biểu diễn
độ sâu tương đối so với đỉnh hiện tại, thay vì so với đỉnh gốc.
Cũng lưu ý rằng kích thước của cấu trúc dữ liệu đã hợp nhất tỷ lệ với
độ sâu của đỉnh, thay vì kích thước cây con của đỉnh.

Có thể đáng ngạc nhiên rằng lời giải này chạy trong thời gian $O(n)$.

Chứng minh này lần đầu tiên được [trình bày](https://codeforces.com/blog/entry/70822) bởi
người dùng Codeforces [neal](https://codeforces.com/profile/neal).

Độ phức tạp thời gian của việc xây dựng các `deque` là tuyến tính vì mỗi
lần chèn hoạt động trong thời gian $O(1)$ và mỗi đỉnh tương ứng với tối đa hai
lần chèn. Do đó, ta chỉ cần tập trung vào hàm `merge`.

Một thao tác `merge` tạo ra một `deque` có kích thước bằng kích thước
của `deque` lớn hơn trong hai `deque` được hợp nhất, thay vì tổng của hai kích thước. Do đó,
`deque` nhỏ hơn bị "tiêu thụ" và các phần tử của nó sẽ không tạo thêm
bất kỳ công việc nào nữa. Vì chỉ có tổng cộng $O(n)$ phần tử `deque` và mỗi phần tử trong số chúng bị
tiêu thụ tối đa một lần, tổng độ phức tạp thời gian là tuyến tính.

```cpp
#include <deque>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

const int N = 200001;
int n, k;
vector<int> g[N];
ll answer;

void merge(deque<int> &a, deque<int> &b) {
    if (b.size() > a.size()) swap(a, b);
    int bs = b.size();
    for (int i = 0; i < bs; ++i) {
        if (0 <= k - i && k - i < (int)a.size()) {
            answer += b[i] * a[k - i];
        }
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
        child_depths.push_front(0);
        merge(ret, child_depths);
    }
    return ret;
}

int main() {
    cin >> n >> k;

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
