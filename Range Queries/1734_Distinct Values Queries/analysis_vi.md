# 1734 - Truy vấn giá trị phân biệt

## Cách tiếp cận thứ nhất: Cây phân đoạn

Bài toán này có thể được giải bằng cây phân đoạn.
Lưu ý rằng chúng ta có thể trả lời các truy vấn một cách offline,
nghĩa là chúng ta có thể thay đổi thứ tự trả lời chúng.

Chúng ta xử lý các truy vấn theo thứ tự tăng dần của điểm bắt đầu.
Tại mỗi điểm, chúng ta trả lời tất cả các truy vấn bắt đầu tại điểm đó.

Chúng ta luôn muốn chỉ có một lần xuất hiện
của mỗi giá trị phân biệt trong cây phân đoạn,
và chúng ta lưu, với mỗi giá trị, lần xuất hiện tiếp theo
bên phải của con trỏ của chúng ta.

Điều này đảm bảo rằng nếu
bất kỳ lần xuất hiện nào của một giá trị nằm
trong đoạn truy vấn thì
lần xuất hiện ngoài cùng bên trái cũng nằm
trong đoạn truy vấn.
Do đó, mỗi giá trị phân biệt trong đoạn truy vấn
được đếm đúng một lần,
chính xác những gì chúng ta muốn.

Độ phức tạp thời gian của cài đặt này
là $O(n\log n)$.

```cpp
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

const int TREE_SIZE = 1 << 18;
int tree[TREE_SIZE * 2];

void change(int k, int x) {
    k += TREE_SIZE;
    tree[k] = x;
    while (k > 1) {
        k /= 2;
        tree[k] = tree[k * 2] + tree[k * 2 + 1];
    }
}

// Trả về tổng các giá trị trong đoạn [l, r].
int query(int l, int r) {
    int ans = 0;
    l += TREE_SIZE;
    r += TREE_SIZE;
    while (l <= r) {
        if (l % 2 == 1) ans += tree[l++];
        if (r % 2 == 0) ans += tree[r--];
        l /= 2;
        r /= 2;
    }
    return ans;
}

struct Query {
    int l, r, i;
};

int main() {
    int n, q;
    cin >> n >> q;

    vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }

    // Lưu các lần xuất hiện của mỗi giá trị – theo thứ tự giảm dần.
    // Làm theo cách này, chúng ta có thể, tại bất kỳ thời điểm nào, một cách hiệu quả
    // loại bỏ lần xuất hiện nhỏ nhất của bất kỳ giá trị nào
    // bằng cách sử dụng hàm `pop_back`.
    map<int, vector<int>> occurrences;
    for (int i = n - 1; i >= 0; --i) {
        occurrences[v[i]].push_back(i);
    }

    for (auto &[v, l] : occurrences) {
        change(l.back(), 1);
        l.pop_back();
    }

    vector<Query> queries(q);
    for (int i = 0; i < q; ++i) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].l--;
        queries[i].r--;
        queries[i].i = i;
    }

    sort(queries.begin(), queries.end(),
         [&](auto a, auto b) { return a.l < b.l; });

    vector<int> answer(q);

    for (int i = 0, j = 0; i < n; ++i) {
        while (j < q && queries[j].l == i) {
            answer[queries[j].i] = query(i, queries[j].r);
            ++j;
        }
        if (!occurrences[v[i]].empty()) {
            change(occurrences[v[i]].back(), 1);
            occurrences[v[i]].pop_back();
        }
    }

    for (int a : answer) {
        cout << a << ' ';
    }
    cout << '\n';
}
```

## Cách tiếp cận thứ hai: Giải thuật Mo

Giải thuật Mo là một giải thuật offline
để trả lời các truy vấn trên đoạn.
Giải thuật dựa trên một thứ tự đặc biệt
trong đó các truy vấn được chia thành
các khối kích thước $B=\sqrt n$.
Truy vấn $[l\_0,r\_0]$ đứng trước
$[l\_1,r\_1]$ nếu

* $\left\lfloor \frac{l\_0}{B}\right\rfloor<\left\lfloor \frac{l\_1}{B}\right\rfloor$
* $\left\lfloor \frac{l\_0}{B}\right\rfloor=\left\lfloor \frac{l\_1}{B}\right\rfloor$ và $r\_0< r\_1$.

Chúng ta duy trì một đoạn đang hoạt động với hai con trỏ.
Các con trỏ này được di chuyển, từng bước một,
từ truy vấn này sang truy vấn tiếp theo.

Con trỏ trái di chuyển $O(n)$ lần, mỗi lần $O(\sqrt n)$
bước
và
con trỏ phải di chuyển $O(\sqrt n)$ lần, mỗi lần $O(n)$
bước.

Do đó, độ phức tạp thời gian tổng thể của giải thuật này
là
$$O(n\cdot f(n)\sqrt n)$$
trong đó
$f(n)$ là chi phí di chuyển một con trỏ.

Một cài đặt của giải thuật Mo có thể được tìm thấy bên dưới. Thật không may, giải
pháp này quá chậm.

Vì việc di chuyển một con trỏ thay đổi
một giá trị bên trong `map`, nên nó mất
$O(\log n)$ thời gian và
độ phức tạp thời gian tổng thể của
cài đặt là
$O(n \sqrt{n} \log{n})$
nếu chúng ta giả sử có
$n$ truy vấn. Điều này tương đương
với khoảng $1.57\cdot 10^9$
thao tác với hệ số hằng số lớn.

```cpp
#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

// Đặt kích thước khối bằng sqrt(N).
const int B = (int)sqrt(2e5);

struct Query {
    int l, r, i;
};

int main() {
    int n, q;
    cin >> n >> q;

    vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }

    vector<Query> queries(q);
    for (int i = 0; i < q; ++i) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].l--;
        queries[i].r--;
        queries[i].i = i;
    }

    sort(queries.begin(), queries.end(), [&](auto a, auto b) {
        if (a.l / B != b.l / B) {
            return a.l / B < b.l / B;
        }
        return a.r < b.r;
    });

    vector<int> answer(q);

    map<int, int> s;

    auto add = [&](int i) {
        s[v[i]]++;
    };

    auto remove = [&](int i) {
        auto it = s.find(v[i]);
        it->second--;
        if (it->second == 0) {
            s.erase(it);
        }
    };

    int al = 0, ar = 0;
    add(0);

    for (auto [l, r, i] : queries) {
        while (ar < r) add(++ar);
        while (al > l) add(--al);
        while (al < l) remove(al++);
        while (ar > r) remove(ar--);
        answer[i] = (int)s.size();
    }

    for (int a : answer) {
        cout << a << ' ';
    }
    cout << '\n';
}
```

May mắn thay, có một cách sửa dễ dàng: nén tọa độ.
Khi chúng ta dịch các số từ khoảng $[1,10^9]$
sang khoảng $[0,n-1]$, chúng ta không cần `map` nữa.
Thay vào đó, chúng ta có thể sử dụng một mảng để đếm số lượng
của mỗi giá trị.
Cài đặt mới này có độ phức tạp thời gian
là $O(n\sqrt n)$ và hoàn toàn nằm
trong giới hạn thời gian.

```cpp
#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

// Đặt kích thước khối bằng sqrt(N).
const int B = (int)sqrt(2e5);

struct Query {
    int l, r, i;
};

int main() {
    int n, q;
    cin >> n >> q;

    vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }

    auto values = v;
    sort(values.begin(), values.end());

    for (int &x : v) {
        x = lower_bound(values.begin(), values.end(), x) - values.begin();
    }

    vector<Query> queries(q);
    for (int i = 0; i < q; ++i) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].l--;
        queries[i].r--;
        queries[i].i = i;
    }

    sort(queries.begin(), queries.end(), [&](auto a, auto b) {
        if (a.l / B != b.l / B) {
            return a.l / B < b.l / B;
        }
        return a.r < b.r;
    });

    int distinct = 0;
    vector<int> occurrences(n);
    vector<int> answer(q);

    auto add = [&](int i) {
        if (occurrences[v[i]]++ == 0) {
            distinct++;
        }
    };

    auto remove = [&](int i) {
        if (--occurrences[v[i]] == 0) {
            distinct--;
        }
    };

    int al = 0, ar = 0;
    add(0);

    for (auto [l, r, i] : queries) {
        while (ar < r) add(++ar);
        while (al > l) add(--al);
        while (al < l) remove(al++);
        while (ar > r) remove(ar--);
        answer[i] = distinct;
    }

    for (int a : answer) {
        cout << a << ' ';
    }
    cout << '\n';
}
```
