# 2416 - Truy vấn mảng tăng dần

Có nhiều cách tiếp cận cho bài toán này. Trước hết chúng ta hãy phân tích tình huống
trước khi thảo luận về bất kỳ cách tiếp cận cụ thể nào.

Một câu hỏi quan trọng là "Khi nào chúng ta cần tăng một phần tử?" Gọi một
phần tử của mảng là *đặc biệt* nếu nó lớn hơn giá trị đứng sau nó.
Chỉ các phần tử *đặc biệt* mới có thể khiến các phần tử khác tăng lên. Mỗi giá trị nhỏ hơn
đứng sau một phần tử *đặc biệt* sẽ được tăng lên để bằng kích thước của phần tử *đặc biệt* đó.

Hình ảnh sau minh họa ý tưởng – chiều cao của các tháp
biểu diễn kích thước của các phần tử mảng và các ô màu đỏ được thêm vào bằng
thao tác.

![](33a248716f823b63b45b3188e958889a25f20f08c4139bd4fd6762b00273e156)

## Cách tiếp cận thứ nhất: Cây phân đoạn với lazy propagation

Đây là một cách tiếp cận offline khi chúng ta trả lời các truy vấn theo thứ tự
chỉ số bắt đầu của chúng. Chúng ta sẽ duyệt mảng theo thứ tự ngược và theo dõi
lượng tăng cần thiết cho mỗi phần tử. Bằng cách này, chúng ta có thể trả lời một truy vấn bằng một
truy vấn tổng trên cây phân đoạn lazy.

Với mỗi vị trí trong cây, chúng ta sẽ lưu lượng mà phần tử ở vị trí này
cần được tăng lên, nói cách khác, là giá trị sau khi tăng trừ đi giá trị ban đầu.

Để tìm ra lượng tăng cần thiết cho mỗi phần tử, chúng ta sẽ sử dụng một ngăn xếp
các giá trị tăng dần. Với mỗi phần tử, chúng ta sẽ xóa tất cả các giá trị nhỏ hơn nó
khỏi ngăn xếp. Lưu ý rằng tất cả các giá trị trong ngăn xếp đều là các phần tử *đặc biệt*.
Phần tử trên cùng của ngăn xếp sẽ là giá trị lớn hơn tiếp theo và
tất cả các giá trị đứng trước nó sẽ cần được tăng lên, điều này có thể thực hiện bằng cách
cộng giá trị hiện tại vào đoạn tương ứng trong cây.

Chúng ta sẽ sử dụng các thao tác trên cây phân đoạn khi xóa một phần tử khỏi
ngăn xếp hoặc khi trả lời một truy vấn. Mỗi chỉ số có thể bị xóa khỏi ngăn xếp tối đa
một lần – nói cách khác, số lượng phần tử bị xóa là $O(n)$.
Hơn nữa, mỗi thao tác trên cây phân đoạn mất $O(\log n)$ thời gian. Do đó,
độ phức tạp thời gian tổng thể của lời giải là $O((n+q)\log n)$.

```cpp
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

// Cây phân đoạn với lazy propagation.
// Hỗ trợ các thao tác sau:
//  1. `add`: cộng x vào mọi phần tử trong đoạn [l, r)
//  2. `query`: tìm tổng các giá trị trong đoạn [l, r)
struct Tree {
    int n;
    vector<ll> tree;
    vector<ll> lazy;

    Tree(int n) : n(n), tree(n * 4), lazy(n * 4) {}

    void add(int s, int l, int r, int ql, int qr, ll x) {
        if (r <= ql || qr <= l) return;
        if (ql <= l && r <= qr) return apply(s, r - l, x);
        push(s, r - l);
        int m = (l + r) / 2;
        add(s * 2 + 0, l, m, ql, qr, x);
        add(s * 2 + 1, m, r, ql, qr, x);
        pull(s);
    }

    ll query(int s, int l, int r, int ql, int qr) {
        if (r <= ql || qr <= l) return 0;
        if (ql <= l && r <= qr) return tree[s];
        push(s, r - l);
        int m = (l + r) / 2;
        return query(s * 2, l, m, ql, qr) + query(s * 2 + 1, m, r, ql, qr);
    }

    void push(int s, int length) {
        if (lazy[s]) {
            apply(s * 2 + 0, length / 2, lazy[s]);
            apply(s * 2 + 1, (length + 1) / 2, lazy[s]);
            lazy[s] = 0;
        }
    }

    void apply(int s, int length, ll x) {
        tree[s] += x * length;
        lazy[s] += x;
    }

    void pull(int s) { tree[s] = tree[s * 2] + tree[s * 2 + 1]; }
    void add(int l, int r, ll x) { add(1, 0, n, l, r, x); }
    ll query(int l, int r) { return query(1, 0, n, l, r); }
};

int main() {
    int n, q;
    cin >> n >> q;

    Tree tree(n);

    vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
        tree.add(i, i + 1, -v[i]);
    }

    vector<vector<pair<int, int>>> queries(n);
    vector<ll> ans(q);

    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        l--;
        queries[l].emplace_back(r, i);
    }

    vector<int> stack{n};

    for (int i = n - 1; i >= 0; --i) {
        while (stack.back() < n && v[stack.back()] <= v[i]) {
            int j = stack.back();
            stack.pop_back();
            tree.add(j, stack.back(), -v[j]);
        }
        tree.add(i, stack.back(), v[i]);
        stack.push_back(i);
        for (auto [r, j] : queries[i]) {
            ans[j] = tree.query(i, r);
        }
    }

    for (ll u : ans) {
        cout << u << '\n';
    }
}
```

## Cách tiếp cận thứ hai: Cây phân đoạn thông thường

Lời giải trên có thể được sửa đổi để hoạt động với một cây phân đoạn thông thường.

Khi làm việc với cây phân đoạn thông thường, chúng ta sẽ lưu lượng tăng vào
các vị trí của các phần tử *đặc biệt* tương ứng. Lưu ý rằng đoạn ảnh hưởng
của phần tử *đặc biệt* cuối cùng trong đoạn truy vấn có thể vượt quá
đầu cuối bên phải của truy vấn. Trong trường hợp này, chúng ta phải trừ đi phần tăng thừa.

Cách tiếp cận này có cùng độ phức tạp thời gian như cách tiếp cận trước.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

const int TREE_SIZE = 1 << 18;
ll tree[TREE_SIZE * 2];

// Cộng x vào vị trí i
void add(int i, ll x) {
    i += TREE_SIZE;
    while (i > 0) {
        tree[i] += x;
        i /= 2;
    }
}

// Trả về tổng các giá trị trong đoạn [l, r)
ll query(int l, int r) {
    ll res = 0;
    l += TREE_SIZE;
    r += TREE_SIZE;
    while (l < r) {
        if (l % 2 == 1) res += tree[l++];
        if (r % 2 == 1) res += tree[--r];
        l /= 2;
        r /= 2;
    }
    return res;
}

int main() {
    int n, q;
    cin >> n >> q;

    vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
        add(i, -v[i]);
    }

    vector<vector<pair<int, int>>> queries(n);
    vector<ll> ans(q);

    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        l--;
        queries[l].emplace_back(r, i);
    }

    vector<pair<int, int>> stack{{n, 0}};

    for (int i = n - 1; i >= 0; --i) {
        while (stack.back().first < n && v[stack.back().first] <= v[i]) {
            auto [j, len] = stack.back();
            stack.pop_back();
            add(j, -ll(len) * v[j]);
        }
        add(i, ll(stack.back().first - i) * v[i]);
        stack.emplace_back(i, stack.back().first - i);
        for (auto [r, j] : queries[i]) {
            auto iter = lower_bound(stack.rbegin(), stack.rend(), pair{r, 0});
            auto [it, len] = *prev(iter);
            ans[j] = query(i, r) - ll(len - (r - it)) * v[it];
        }
    }

    for (ll u : ans) {
        cout << u << '\n';
    }
}
```

## Cách tiếp cận thứ ba: Sparse table

Có một lời giải đơn giản sử dụng sparse table. Chúng ta sẽ, với mỗi phần tử,
lưu một con trỏ tới phần tử lớn hơn tiếp theo. Sau đó, một sparse table sẽ được xây dựng
để theo dõi các con trỏ một cách hiệu quả.

Lượng tăng cần thiết để làm cho đoạn từ vị trí $i$ đến
vị trí $j$ của phần tử lớn hơn tiếp theo trở thành không giảm được tính bằng
công thức $(j-i)\cdot x\_i-\sum\_{i\le k < j}a\_k$. Công thức biểu diễn
hiệu giữa các giá trị sau khi tăng và các giá trị ban đầu.

Lưu ý rằng, cũng trong lời giải này, bước nhảy cuối cùng có thể vượt quá đoạn truy vấn.
Trong trường hợp này, chúng ta biết rằng mỗi phần tử còn lại trong đoạn sẽ có
cùng giá trị – vì chúng nhỏ hơn giá trị hiện tại của chúng ta. Do đó, chúng ta có thể tính
lượng tăng cần thiết cho các phần tử này một cách riêng biệt.

Xây dựng sparse table mất $O(n\log n)$ thời gian và trả lời một
truy vấn đơn lẻ mất $O(\log n)$ thời gian. Do đó, độ phức tạp thời gian tổng thể
là $O((n+q)\log n)$.

```cpp
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const int INF = 1e9;

const int N = 200001;
const int L = 19;
int jump[L][N];
ll cost[L][N];

int main() {
    int n, q;
    cin >> n >> q;

    vector<int> a(n + 1);
    vector<ll> prefix_sum(n + 1);

    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        prefix_sum[i + 1] = prefix_sum[i] + a[i];
    }

    a[n] = INF;
    jump[0][n] = n;

    vector<int> stack{n};

    for (int i = n - 1; i >= 0; --i) {
        while (a[stack.back()] <= a[i]) {
            stack.pop_back();
        }

        int j = stack.back();
        jump[0][i] = j;
        cost[0][i] = ll(j - i) * a[i];
        stack.push_back(i);
    }

    for (int j = 0; j < L - 1; ++j) {
        for (int i = 0; i <= n; ++i) {
            cost[j + 1][i] = cost[j][i] + cost[j][jump[j][i]];
            jump[j + 1][i] = jump[j][jump[j][i]];
        }
    }

    for (int qi = 0; qi < q; ++qi) {
        int l, r;
        cin >> l >> r;
        l--;
        ll ans = -(prefix_sum[r] - prefix_sum[l]);

        for (int j = L - 1; j >= 0; --j) {
            if (jump[j][l] < r) {
                ans += cost[j][l];
                l = jump[j][l];
            }
        }

        ans += ll(r - l) * a[l];

        cout << ans << '\n';
    }
}
```
