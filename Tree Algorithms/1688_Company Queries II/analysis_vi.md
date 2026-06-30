# 1688 - Truy vấn công ty II

Bài toán tìm LCA (tổ tiên chung thấp nhất) của hai đỉnh trong một cây là
một trong những bài toán quan trọng nhất về cây trong lập trình thi đấu.
Đó là lý do tại sao cần thảo luận về một vài cách tiếp cận khác nhau cho
bài toán thiết yếu này.

## Cách tiếp cận thứ nhất: Binary lifting

Cách tiếp cận đầu tiên dựa trên một kỹ thuật gọi là *binary lifting*.
Đầu tiên, ta xây dựng một bảng bước nhảy có thể trả lời các truy vấn dạng
"đỉnh nào cao hơn đỉnh $x$ $2^k$ bước?" trong thời gian $O(1)$.

Không rõ ràng làm thế nào để trả lời các truy vấn LCA sau khi bảng bước nhảy đã được xây dựng.
Các bước thực hiện như sau.

Đầu tiên, lấy đỉnh xa gốc hơn và
nâng nó lên cho đến khi nó cách gốc một khoảng bằng với đỉnh thứ hai.

Bây giờ cả hai đỉnh đã ở cùng một 'mức', ta nên nâng cả hai lên
cùng một lúc. Hóa ra một thuật toán tham lam hoạt động ở đây:
ta nâng các đỉnh lên cao nhất có thể miễn là hai con trỏ
trỏ đến hai đỉnh khác nhau.

Việc xây dựng bảng bước nhảy tốn $O(n\log n)$ thời gian.
Trả lời một truy vấn đơn lẻ tốn $O(\log n)$ thời gian, nghĩa là
trả lời tất cả các truy vấn tốn tổng cộng $O(q\log n)$ thời gian.
Do đó, độ phức tạp thời gian tổng thể của lời giải là $O(n\log n+q\log n)$.

```cpp
#include <iostream>
#include <vector>
using namespace std;

const int N = 200000;
int jmp[N][20];
int depth[N];
vector<int> g[N];

void dfs(int node) {
    for (int child : g[node]) {
        depth[child] = depth[node] + 1;
        dfs(child);
    }
}

int lca(int a, int b) {
    if (depth[a] < depth[b]) {
        swap(a, b);
    }
    int depth_difference = depth[a] - depth[b];
    for (int j = 19; j >= 0; --j) {
        if ((1 << j) & depth_difference) {
            a = jmp[a][j];
        }
    }
    if (a == b) {
        return a;
    } else {
        for (int j = 19; j >= 0; --j) {
            if (jmp[a][j] != jmp[b][j]) {
                a = jmp[a][j];
                b = jmp[b][j];
            }
        }
        return jmp[a][0];
    }
}

int main() {
    int n, q;

    cin >> n >> q;

    for (int i = 1; i < n; ++i) {
        cin >> jmp[i][0];
        jmp[i][0]--;
        g[jmp[i][0]].push_back(i);
    }

    for (int j = 0; (1 << j) <= n; ++j) {
        for (int i = 0; i < n; ++i) {
            jmp[i][j + 1] = jmp[jmp[i][j]][j];
        }
    }

    dfs(0);

    for (int qi = 0; qi < q; ++qi) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        cout << lca(a, b) + 1 << '\n';
    }
}
```

### Tài nguyên cho binary lifting

* [CP-Algorithms, *Lowest Common Ancestor - Binary Lifting*](https://cp-algorithms.com/graph/lca_binary_lifting.html)
* [CPHB (Competitive Programmer's Handbook)](http://cses.fi/book), Chương 18

### Ghi chú phụ

[*Heavy-light decomposition*](https://codeforces.com/blog/entry/53170) hoặc
kỹ thuật được gọi là [*jump pointers*](https://codeforces.com/blog/entry/74847)
có thể được sử dụng để cải thiện độ phức tạp bộ nhớ của lời giải này lên $O(n)$.

## Cách tiếp cận thứ hai: Euler tour

Một cách khác để giải bài toán này là sử dụng kỹ thuật gọi là *Euler tour*.
Kỹ thuật này dựa trên một mảng đặc biệt. Mảng này được xây dựng
trong quá trình duyệt DFS. Mỗi khi một đỉnh được thăm,
nó được thêm vào mảng. Đó là khi quá trình duyệt lần đầu tiên đến
đỉnh, giữa lúc thăm các đỉnh con và khi quá trình duyệt
rời khỏi đỉnh.

![](3db66a4f519505ac0d96e65246625d03c3a8b26e790daa32ed50dbf73882f0a4)

Ví dụ, mảng này tương ứng với hình ảnh trên.

![](5d1ec467300ee5c0c2dd62b3623057739394d6d9e67b45aa96f5083d9bca7cfe)

Mảng này có thể được sử dụng để tìm tổ tiên chung thấp nhất của hai đỉnh.
Ta bắt đầu bằng cách tìm vị trí mà các đỉnh xuất hiện
lần đầu tiên trong mảng. Sau đó, LCA tương ứng với
đỉnh có độ sâu nhỏ nhất giữa các vị trí này.
Do đó, ta đã quy bài toán LCA về bài toán RMQ (range minimum query).

Ta có thể trả lời các truy vấn bằng cách sử dụng, ví dụ, cây phân đoạn.

```cpp
#include <iostream>
#include <vector>
using namespace std;
const int INF = 1e9;

struct Tree {
    int n;
    vector<pair<int, int>> t;
    // Xây dựng cây phân đoạn trong thời gian tuyến tính
    Tree(vector<pair<int, int>> &v) {
        n = 1;
        while (n <= (int)size(v)) {
            n *= 2;
        }
        t.resize(n * 2);
        for (int i = 0; i < (int)size(v); ++i) {
            t[n + i] = v[i];
        }
        for (int i = n - 1; i > 0; --i) {
            t[i] = min(t[i * 2], t[i * 2 + 1]);
        }
    }
    // Trả về giá trị nhỏ nhất trong đoạn [l, r]
    pair<int, int> query(int l, int r) {
        pair<int, int> ans{INF, INF};
        l += n;
        r += n;
        while (l <= r) {
            if (l % 2 == 1) ans = min(ans, t[l++]);
            if (r % 2 == 0) ans = min(ans, t[r--]);
            l /= 2;
            r /= 2;
        }
        return ans;
    }
};

const int N = 200000;
int depth[N];
vector<int> g[N];

void dfs(int node, vector<pair<int, int>> &tour) {
    tour.emplace_back(depth[node], node);
    for (int child : g[node]) {
        depth[child] = depth[node] + 1;
        dfs(child, tour);
        tour.emplace_back(depth[node], node);
    }
}

int main() {
    int n, q;

    cin >> n >> q;

    for (int i = 1; i < n; ++i) {
        int p;
        cin >> p;
        p--;
        g[p].push_back(i);
    }

    vector<pair<int, int>> tour;

    dfs(0, tour);

    vector<int> position(n, -1);

    for (int i = 0; i < (int)tour.size(); ++i) {
        int id = tour[i].second;
        if (position[id] < 0) {
            position[id] = i;
        }
    }

    Tree tree(tour);

    for (int qi = 0; qi < q; ++qi) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        a = position[a];
        b = position[b];
        if (b < a) {
            swap(a, b);
        }
        cout << tree.query(a, b).second + 1 << '\n';
    }
}
```

Việc xây dựng mảng và cây phân đoạn tốn tổng cộng
$O(n)$ thời gian.
Một truy vấn cây phân đoạn đơn lẻ tốn $O(\log n)$ thời gian.
Do đó, độ phức tạp thời gian tổng thể của lời giải là $O(n+q\log n)$.

Ta có thể sử dụng sparse table thay cho cây phân đoạn.

```cpp
#include <iostream>
#include <vector>
using namespace std;

struct RMQ {
    vector<vector<pair<int, int>>> table;
    // Xây dựng sparse table trong O(n log n)
    RMQ(vector<pair<int, int>> &v) : table{v} {
        for (int j = 0; (1 << j) < (int)size(v); ++j) {
            table.emplace_back(size(v) - (1 << j));
            for (int i = 0; i < (int)size(table.back()); ++i) {
                table[j + 1][i] = min(table[j][i], table[j][i + (1 << j)]);
            }
        }
    }
    pair<int, int> query(int l, int r) {
        int len = r - l + 1;
        int lvl = __lg(len);
        return min(table[lvl][l], table[lvl][r - (1 << lvl) + 1]);
    }
};

const int N = 200000;
int depth[N];
vector<int> g[N];

void dfs(int node, vector<pair<int, int>> &tour) {
    tour.emplace_back(depth[node], node);
    for (int child : g[node]) {
        depth[child] = depth[node] + 1;
        dfs(child, tour);
        tour.emplace_back(depth[node], node);
    }
}

int main() {
    int n, q;

    cin >> n >> q;

    for (int i = 1; i < n; ++i) {
        int p;
        cin >> p;
        p--;
        g[p].push_back(i);
    }

    vector<pair<int, int>> tour;

    dfs(0, tour);

    vector<int> position(n, -1);

    for (int i = 0; i < (int)tour.size(); ++i) {
        int id = tour[i].second;
        if (position[id] < 0) {
            position[id] = i;
        }
    }

    RMQ rmq(tour);

    for (int qi = 0; qi < q; ++qi) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        a = position[a];
        b = position[b];
        if (b < a) {
            swap(a, b);
        }
        cout << rmq.query(a, b).second + 1 << '\n';
    }
}
```

Sparse table có thời gian xây dựng là $O(n\log n)$ và thời gian
truy vấn là $O(1)$. Do đó, độ phức tạp thời gian tổng thể của
lời giải là $O(n\log n+q)$.

### Tài nguyên cho kỹ thuật Euler tour

* [CP-Algorithms, *Lowest Common Ancestor*](https://cp-algorithms.com/graph/lca.html)
* [CPHB (Competitive Programmer's Handbook)](http://cses.fi/book), Chương 18
