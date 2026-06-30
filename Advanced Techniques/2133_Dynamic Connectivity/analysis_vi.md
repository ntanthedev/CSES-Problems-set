# 2133 - Kết Nối Động

Bài toán này có thể được giải bằng cấu trúc union find, vì nó cung cấp thông tin về số lượng thành phần liên thông trong một mạng lưới nhất định. Theo mặc định, union find không hỗ trợ việc xóa cạnh, nhưng nó có thể được sửa đổi để hỗ trợ việc hoàn tác các thao tác trước đó. Điều này có thể thực hiện bằng cách giữ một ngăn xếp các thay đổi được thực hiện trên cấu trúc. Việc thêm một cạnh chỉ sửa đổi $O(1)$ giá trị trong mảng, và do đó bất kỳ thao tác nào cũng có thể được hoàn tác với $O(1)$ công việc.

Sẽ rất hữu ích khi nghĩ về các cạnh theo khoảng thời gian $[l, r)$ mà trong đó chúng *hoạt động*, nghĩa là khoảng thời gian một cạnh là một phần của đồ thị. Nếu một cạnh thuộc đồ thị ban đầu, khoảng thời gian của nó bắt đầu tại thời điểm 0, và nếu một cạnh không bao giờ bị xóa, khoảng thời gian của nó kết thúc tại $r = k+1$. Nhiệm vụ của chúng ta là tìm số lượng thành phần liên thông tại các thời điểm riêng lẻ.

Để làm điều này, chúng ta sẽ tạo một hàm đệ quy kiểu chia để trị luôn chia đôi phạm vi tìm kiếm và xử lý từng nửa một cách đệ quy. Trong quá trình tìm kiếm, chúng ta sẽ giữ một danh sách tất cả các khoảng cạnh có điểm chung với phạm vi tìm kiếm của chúng ta, và truyền danh sách này đến các phạm vi tiếp theo. Bất cứ khi nào một khoảng chứa toàn bộ phạm vi tìm kiếm, nó sẽ được loại khỏi danh sách và được thêm vào cấu trúc union find. Sau khi các lời gọi đệ quy kết thúc, chúng ta sẽ hoàn tác các thay đổi mà các cạnh đã thêm vào cấu trúc union find.

Quá trình này đảm bảo rằng mỗi cạnh sẽ được thêm và xóa tối đa $O(\log k)$ lần. Vì mỗi thao tác hoạt động trong $O(\log n)$ thời gian, độ phức tạp thời gian tổng thể của thuật toán là $O(k \log k \log n + m \log n)$.

Kỹ thuật được sử dụng ở đây cũng có thể áp dụng cho các bài toán khác. Ví dụ, nó có thể được sử dụng với cây Li Chao, cho phép xóa các đường thẳng.

```cpp
#include <iostream>
#include <map>
#include <vector>
using namespace std;

// Cấu trúc Union Find với chức năng rollback.
struct UnionFind {
    // Lưu số lượng cây rời rạc.
    int n;
    // Nếu p[i] < 0, i là nút gốc với kích thước cây là -p[i].
    // Ngược lại, p[i] đại diện cho cha của i.
    vector<int> p;
    vector<pair<int *, int>> changes;
    UnionFind(int n) : n(n), p(n, -1) {}
    int root(int s) {
        while (p[s] >= 0) {
            s = p[s];
        }
        return s;
    }
    void merge(int a, int b) {
        a = root(a);
        b = root(b);
        if (a == b) return;
        if (p[a] < p[b]) swap(a, b);
        changes.emplace_back(&p[a], p[a]);
        changes.emplace_back(&p[b], p[b]);
        changes.emplace_back(&n, n);
        n--;
        p[b] += p[a];
        p[a] = b;
    }
    void undo(int cnt) {
        while (cnt--) {
            auto [a, b] = changes.back();
            changes.pop_back();
            *a = b;
        }
    }
};

using Event = tuple<int, int, int, int>;

const int N = 100001;
int ans[N];
UnionFind uf(0);

void answer(int l, int r, vector<Event> edges) {
    int old_size = uf.changes.size();
    int mid = (l + r) / 2;
    vector<Event> left, right;
    for (auto &e : edges) {
        auto [t0, t1, a, b] = e;
        if (t0 <= l && r <= t1) {
            uf.merge(a, b);
        } else {
            if (t0 < mid) {
                left.emplace_back(e);
            }
            if (mid < t1) {
                right.emplace_back(e);
            }
        }
    }
    if (r - l == 1) {
        ans[l] = uf.n;
    } else {
        answer(l, mid, left);
        answer(mid, r, right);
    }
    uf.undo(uf.changes.size() - old_size);
}

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    map<pair<int, int>, int> edge_time;
    vector<Event> edges;

    for (int i = 0; i < m + k; ++i) {
        int _, a, b;
        if (i >= m) cin >> _;
        cin >> a >> b;
        a--;
        b--;
        if (b < a) swap(a, b);
        int t = max(0, i - (m - 1));
        if (auto it = edge_time.find({a, b}); it != edge_time.end()) {
            edges.emplace_back(it->second, t, a, b);
            edge_time.erase(it);
        } else {
            edge_time.insert(it, {{a, b}, t});
        }
    }

    for (auto [e, t] : edge_time) {
        auto [a, b] = e;
        edges.emplace_back(t, k + 1, a, b);
    }

    uf = UnionFind(n);
    answer(0, k + 1, edges);

    for (int i = 0; i < k + 1; ++i) {
        cout << ans[i] << ' ';
    }
    cout << '\n';
}
```
