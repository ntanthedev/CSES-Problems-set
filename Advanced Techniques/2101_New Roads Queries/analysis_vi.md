# 2101 - New Roads Queries

## Solution 1: Tìm kiếm nhị phân song song

Bài toán này có thể được giải hiệu quả với một kỹ thuật gọi là *tìm kiếm nhị phân
song song*. Điều này có nghĩa là chúng ta tìm kiếm nhị phân câu trả lời cho tất
cả các truy vấn đồng thời.

Nếu chúng ta sử dụng tìm kiếm nhị phân để trả lời từng truy vấn riêng biệt, chúng ta
sẽ phải xây dựng một cấu trúc union find để kiểm tra mỗi điểm giữa trong mỗi
lần tìm kiếm. Độ phức tạp thời gian của việc xây dựng một cấu trúc union find là
$O(m \log n)$, làm cho tổng độ phức tạp thời gian của giải pháp này là
$O(qm \log^2 n)$, quá chậm.

Ý tưởng chính là chúng ta chỉ cần $O(\log m)$ cấu trúc như vậy để trả lời tất cả
các truy vấn. Chúng ta sẽ bắt đầu bằng cách gán cho mỗi truy vấn một phạm vi
$[l, r]$, có nghĩa là các thành phố sẽ trở nên kết nối sớm nhất vào ngày $l$ và
muộn nhất vào ngày $r$. Ban đầu, phạm vi sẽ là $[0, m]$.

Sau đó, chúng ta sẽ mô phỏng việc xây dựng các con đường $\log m$ lần. Giống như
với tìm kiếm nhị phân thông thường, chúng ta sẽ tính điểm giữa của mỗi phạm vi,
và kiểm tra xem các thành phố có được kết nối tại thời điểm đó hay không. Tùy
thuộc vào kết quả, chúng ta sẽ thay đổi cận dưới hoặc cận trên của mỗi phạm vi
thành điểm giữa, làm giảm một nửa mỗi phạm vi.

Thêm $m$ con đường vào mạng mất $O(m \log n)$ thời gian và cập nhật các phạm vi
mất $O(q \log n)$ thời gian, làm cho tổng độ phức tạp thời gian là
$O(\log m \cdot (m + q) \log n)$.

```cpp
#include <iostream>
#include <vector>
using namespace std;

struct UnionFind {
    int n;
    // Nếu p[i] < 0, i là nút gốc với kích thước cây là -p[i].
    // Ngược lại, p[i] là cha của i.
    vector<int> p;
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
        p[b] += p[a];
        p[a] = b;
    }
};

int main() {
    int n, m, q;
    cin >> n >> m >> q;

    UnionFind graph(n);
    vector<pair<int, int>> edges(m);
    for (auto &[a, b] : edges) {
        cin >> a >> b;
        a--;
        b--;
        graph.merge(a, b);
    }

    vector<int> qa(q), qb(q), ql(q), qr(q);
    for (int i = 0; i < q; ++i) {
        int &a = qa[i], &b = qb[i];
        cin >> a >> b;
        a--;
        b--;
        ql[i] = 0;
        qr[i] = m;
    }

    int log2 = __lg(m + 1);

    for (int t = 0; t < log2 + 1; ++t) {
        vector<vector<int>> queries(m + 1);
        for (int i = 0; i < q; ++i) {
            if (ql[i] < qr[i]) {
                queries[(ql[i] + qr[i]) / 2].push_back(i);
            }
        }
        UnionFind uf(n);
        for (int i = 0; i < m; ++i) {
            for (int qi : queries[i]) {
                if (uf.root(qa[qi]) == uf.root(qb[qi])) {
                    qr[qi] = i;
                } else {
                    ql[qi] = i + 1;
                }
            }
            uf.merge(edges[i].first, edges[i].second);
        }
    }

    for (int i = 0; i < q; ++i) {
        if (graph.root(qa[i]) != graph.root(qb[i])) {
            cout << -1 << '\n';
        } else {
            cout << ql[i] << '\n';
        }
    }
}
```

## Solution 2: Binary Lifting

Một cách tiếp cận khác, có thể trả lời các truy vấn trực tuyến, là sử dụng
binary lifting.

Đầu tiên, chúng ta cần xem xét đồ thị đã cho. Chú ý rằng nó có thể không liên
thông. Nếu hai đỉnh nằm trong các thành phần khác nhau, chúng sẽ không bao giờ
đến được với nhau. Do đó, chúng ta chỉ có thể tập trung vào một thành phần duy
nhất. Nếu coi thời điểm một cạnh được thêm vào đồ thị là trọng số của cạnh, ta
có thể tìm cây khung nhỏ nhất của mỗi thành phần. Trọng số cạnh lớn nhất trên
đường đi giữa hai đỉnh trong cây khung tương ứng với thời điểm đầu tiên các
đỉnh có thể đến được với nhau. Việc xây dựng các cây khung được thực hiện dễ
dàng với thuật toán Kruskal vì các cạnh đã được sắp xếp theo trọng số của chúng.

Bây giờ, chúng ta có thể sử dụng binary lifting để tìm cạnh có trọng số lớn nhất
trên đường đi giữa hai đỉnh bất kỳ. Chúng ta sẽ tiến hành tương tự như thuật
toán LCA binary lifting, ngoại trừ việc với mỗi bước nhảy, chúng ta cũng lưu
trữ trọng số cạnh lớn nhất trên đường đi tương ứng với bước nhảy đó.

```cpp
#include <iostream>
#include <vector>
using namespace std;

struct UnionFind {
    int n;
    // Nếu p[i] < 0, i là nút gốc với kích thước cây là -p[i].
    // Ngược lại, p[i] là cha của i.
    vector<int> p;
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
        p[b] += p[a];
        p[a] = b;
    }
};

const int N = 200000;
vector<pair<int, int>> g[N];
int jmp[N][20], jmp_time[N][20];
int depth[N], component[N];
bool visited[N];

void dfs(int node) {
    visited[node] = true;
    for (auto [nxt, t] : g[node]) {
        if (!visited[nxt]) {
            component[nxt] = component[node];
            depth[nxt] = depth[node] + 1;
            jmp[nxt][0] = node;
            jmp_time[nxt][0] = t;
            dfs(nxt);
        }
    }
}

int main() {
    int n, m, q;
    cin >> n >> m >> q;

    UnionFind uf(n);
    for (int i = 1; i <= m; ++i) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        if (uf.root(a) != uf.root(b)) {
            uf.merge(a, b);
            g[a].emplace_back(b, i);
            g[b].emplace_back(a, i);
        }
    }

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            depth[i] = 0;
            component[i] = i;
            jmp[i][0] = i;
            dfs(i);
        }
    }

    for (int j = 0; j < 19; ++j) {
        for (int i = 0; i < n; ++i) {
            jmp[i][j + 1] = jmp[jmp[i][j]][j];
            jmp_time[i][j + 1] = max(jmp_time[i][j], jmp_time[jmp[i][j]][j]);
        }
    }

    auto answer = [&](int a, int b) {
        int r = 0;
        if (depth[a] < depth[b]) {
            swap(a, b);
        }
        for (int j = 19; j >= 0; --j) {
            if (depth[jmp[a][j]] >= depth[b]) {
                r = max(r, jmp_time[a][j]);
                a = jmp[a][j];
            }
        }
        if (a == b) {
            return r;
        }
        for (int j = 19; j >= 0; --j) {
            if (jmp[a][j] != jmp[b][j]) {
                r = max(r, jmp_time[a][j]);
                r = max(r, jmp_time[b][j]);
                a = jmp[a][j];
                b = jmp[b][j];
            }
        }
        r = max(r, jmp_time[a][0]);
        r = max(r, jmp_time[b][0]);
        return r;
    };

    for (int i = 0; i < q; ++i) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        if (component[a] != component[b]) {
            cout << -1 << '\n';
        } else {
            cout << answer(a, b) << '\n';
        }
    }
}
```

## Solution 3: Hợp nhất Union Find

Một cách tiếp cận offline đơn giản hơn nữa là sử dụng cấu trúc union find để
trả lời trực tiếp các truy vấn.

Chúng ta sẽ lưu trữ danh sách các chỉ số truy vấn trong mỗi đỉnh. Chúng ta sẽ lưu
chỉ số của mỗi truy vấn vào danh sách của cả hai đỉnh trong truy vấn đó. Sau đó,
chúng ta sẽ thêm từng cạnh vào cấu trúc, từng cạnh một. Trước mỗi lần thêm, chúng
ta sẽ kiểm tra xem danh sách của các cây được hợp nhất có chứa bất kỳ chỉ số
nào giống nhau hay không. Nếu một chỉ số có trong danh sách của cả hai cây rời
rạc, cạnh được thêm vào sẽ là cạnh đầu tiên sau đó các thành phố của truy vấn
tương ứng trở nên đến được với nhau.

Về mặt cài đặt, các danh sách sẽ được lưu trữ ở đỉnh gốc của mỗi cây và sẽ được
hợp nhất bằng kỹ thuật small-to-large. Điều này đảm bảo rằng mỗi đỉnh sẽ được
hợp nhất nhiều nhất $O(\log n)$ lần và vì có $q$ chỉ số được lưu trữ trong các
danh sách, sẽ có nhiều nhất $O(q \log n)$ lần hợp nhất phần tử danh sách. Mỗi
lần hợp nhất, đến lượt nó, mất $O(\log n)$ thời gian vì một truy vấn union find
duy nhất sẽ được sử dụng để kiểm tra xem các đỉnh tương ứng đã trở nên đến được
với nhau hay chưa. Do đó, thuật toán kết quả có độ phức tạp thời gian là
$O(m \log n + q \log^2 n)$.

```cpp
#include <iostream>
#include <vector>
using namespace std;

const int N = 200000;
int qa[N], qb[N], ans[N];

struct UnionFind {
    int n;
    // Nếu p[i] < 0, i là nút gốc với kích thước cây là -p[i].
    // Ngược lại, p[i] là cha của i.
    vector<int> p;
    // Lưu các chỉ số của truy vấn tại các nút gốc.
    vector<vector<int>> q;
    UnionFind(int n) : n(n), p(n, -1), q(n) {}
    int root(int s) {
        while (p[s] >= 0) {
            s = p[s];
        }
        return s;
    }
    void merge(int a, int b, int t) {
        a = root(a);
        b = root(b);
        if (a == b) return;
        if (p[a] < p[b]) {
            swap(a, b);
        }
        p[b] += p[a];
        p[a] = b;
        if (q[b].size() < q[a].size()) {
            swap(q[a], q[b]);
        }
        for (int i : q[a]) {
            if (ans[i] != -1) continue;
            if (root(qa[i]) == root(qb[i])) {
                ans[i] = t;
            } else {
                q[b].push_back(i);
            }
        }
        q[a].clear();
    }
};

int main() {
    int n, m, q;
    cin >> n >> m >> q;

    vector<pair<int, int>> edges(m);
    for (auto &[a, b] : edges) {
        cin >> a >> b;
        a--;
        b--;
    }

    UnionFind uf(n);
    for (int i = 0; i < q; ++i) {
        int &a = qa[i], &b = qb[i];
        cin >> a >> b;
        a--;
        b--;
        if (a == b) {
            ans[i] = 0;
        } else {
            ans[i] = -1;
            uf.q[a].push_back(i);
            uf.q[b].push_back(i);
        }
    }

    for (int i = 0; i < m; ++i) {
        uf.merge(edges[i].first, edges[i].second, i + 1);
    }

    for (int i = 0; i < q; ++i) {
        cout << ans[i] << '\n';
    }
}
```
