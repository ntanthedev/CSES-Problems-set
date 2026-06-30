# 2085 - Monster Game II

Ba cách tiếp cận riêng biệt cho bài toán này được trình bày dưới đây. Chúng ta cố gắng
giải, với mỗi $i$, thời gian tối thiểu để tiêu diệt con quái vật thứ $i$ và
có thể một số con khác trước nó. Ý tưởng chính trong tất cả các giải pháp là
các thời gian tối thiểu $t\_1, t\_2, \dots t\_n$ này tạo thành các đề xuất dạng
$(t\_i, f\_i)$, trong đó $t\_i$ là thời gian tối thiểu để tiêu diệt con quái vật
thứ $i$ và $f\_i$ là sức mạnh của người chơi sau khi tiêu diệt con quái vật đó.
Các đề xuất này không thay đổi đối với mọi $j>i$.

Với nhận xét này, bài toán trở thành tìm một cấu trúc dữ liệu để lưu trữ các đề
xuất và truy vấn tổng thời gian thấp nhất cho một con quái vật có sức mạnh $s\_i$.
Tổng thời gian để tiêu diệt quái vật $i$ bằng cách sử dụng đề xuất $j$ là
$t\_j+f\_j\cdot s\_i$. Các đề xuất có thể được xem xét về mặt hình học như các
đường thẳng và các cách tiếp cận khác nhau cho bài toán này được gọi chung là
*kỹ thuật bao lồi (convex hull trick)*.

## Solution 1: Kỹ thuật bao lồi thông thường & Biến đổi Bentley-Saxe

Cấu trúc dữ liệu đơn giản nhất để lưu trữ bao lồi là một mảng.
Tuy nhiên, một mảng không cho phép chèn hiệu quả vào giữa nó. Do đó,
tự nó, một mảng đơn giản sẽ quá chậm. May mắn thay, có một cách để
tăng tốc giải pháp này. Nó được gọi là *biến đổi Bentley-Saxe*.

Biến đổi Bentley-Saxe cho phép chúng ta thực hiện chèn vào các cấu trúc dữ liệu
tĩnh, tức là những cấu trúc không hỗ trợ chèn, biến chúng thành động.
Ý tưởng chính là duy trì $O(\log N)$ cấu trúc dữ liệu tĩnh và hợp nhất hai
trong số chúng khi chúng có cùng kích thước. Hợp nhất hai bao lồi nghĩa là lấy
các đường thẳng của chúng và xây dựng một bao lồi hoàn toàn mới từ đầu. Quy
trình diễn ra như sau:

* Duy trì một ngăn xếp các bao lồi tĩnh.
* Khi thêm một đường thẳng mới, tạo một bao lồi chỉ gồm đường thẳng mới đó và
  đẩy nó vào ngăn xếp.
* Bất cứ khi nào hai cấu trúc dữ liệu mới nhất ở cuối ngăn xếp có cùng kích
  thước, hợp nhất chúng thành một bao lồi mới có kích thước gấp đôi.

Quy trình này đảm bảo rằng, tại mọi thời điểm, chúng ta có nhiều nhất
$O(\log N)$ cấu trúc dữ liệu để truy vấn và mỗi đường thẳng được hợp nhất nhiều
nhất $O(\log N)$ lần. Tổng độ phức tạp thời gian của việc xây dựng là
$O(N \log N)$ vì mỗi đường thẳng đóng góp $O(1)$ công việc vào việc xây dựng
mỗi bao lồi mà nó là một phần. Truy vấn mất $O(\log^2 N)$ thời gian vì có
$O(\log N)$ bao lồi và tìm kiếm nhị phân cần được thực hiện trong mỗi bao lồi
để tìm đường thẳng tốt nhất.

## Tài liệu tham khảo

* [CP-Algorithms, *Convex Hull Trick*](https://cp-algorithms.com/geometry/convex_hull_trick.html)
* [J. L. Bentley,
  J. B. Saxe,
  Decomposable searching problems I. Static-to-dynamic transformation,
  Journal of Algorithms,
  Volume 1,
  Issue 4,
  1980](https://www.sciencedirect.com/science/article/pii/0196677480900152)

```cpp
#include <algorithm>
#include <iostream>
#include <limits>
#include <tuple>
#include <vector>
using namespace std;
using ll = long long;
const ll INF = numeric_limits<ll>::max();

struct Line {
    ll a, b;  // Biểu diễn đường thẳng y = ax + b
    // Trả về độ cao của đường thẳng tại x.
    ll operator()(ll x) const { return a * x + b; }
    bool operator<(Line oth) const {
        return a != oth.a ? a > oth.a : b < oth.b;
    }
    ll intersect(Line oth) {
        ll num = oth.b - b, dem = a - oth.a;
        return num / dem - ((num ^ dem) < 0 && num % dem);
    }
};

struct Hull {
    // Lưu tất cả các đường thẳng bất kể chúng có là một phần của bao lồi hay không.
    vector<Line> all;
    // Lưu các đường thẳng của bao lồi và các điểm giao nhau giữa
    // các đường thẳng liên tiếp.
    vector<pair<ll, Line>> hull;
    Hull(Line x) : all{x}, hull{{-INF, x}} {}
    // Xây dựng một bao lồi mới từ các bao lồi a và b.
    Hull(const Hull &a, const Hull &b) {
        all.resize(a.size() + b.size());
        // Chú ý rằng vì các đường thẳng của a và b đã được sắp xếp, chúng ta có
        // thể hợp nhất chúng trong thời gian O(N) mà không cần sắp xếp lại mảng.
        merge(a.all.begin(), a.all.end(), b.all.begin(), b.all.end(),
              all.begin());
        hull.emplace_back(-INF, all[0]);
        for (int i = 1; i < (int)all.size(); ++i) {
            auto l = all[i];
            if (hull.back().second.a == l.a) continue;
            while (hull.size() >= 2) {
                auto al = hull[hull.size() - 2].second;
                auto bl = hull[hull.size() - 1].second;
                if (bl.intersect(l) <= al.intersect(bl)) {
                    hull.pop_back();
                } else {
                    break;
                }
            }
            hull.emplace_back(hull.back().second.intersect(l), l);
        }
    }
    // Trả về đường thẳng thấp nhất tại điểm x.
    ll query(ll x) const {
        auto p = pair{x, Line{INF, INF}};
        auto it = prev(lower_bound(hull.begin(), hull.end(), p));
        return it->second(x);
    }
    size_t size() const { return all.size(); }
};

int main() {
    int n, x;
    cin >> n >> x;

    vector<int> s(n), f(n);
    for (int i = 0; i < n; ++i) cin >> s[i];
    for (int i = 0; i < n; ++i) cin >> f[i];

    vector<Hull> hulls;
    hulls.emplace_back(Line{x, 0});

    auto best_line = [&](ll x) {
        ll r = INF;
        for (auto &h : hulls) r = min(r, h.query(x));
        return r;
    };

    for (int i = 0; i < n - 1; ++i) {
        ll b = best_line(s[i]);
        hulls.emplace_back(Line{f[i], b});
        while (hulls.size() > 1) {
            auto &a = hulls[hulls.size() - 2];
            auto &b = hulls[hulls.size() - 1];
            if (a.size() == b.size()) {
                a = Hull(a, b);
                hulls.pop_back();
            } else {
                break;
            }
        }
    }

    cout << best_line(s[n - 1]) << '\n';
}
```

## Solution 2: Cấu trúc Set

Một cách tiếp cận khác là lưu trữ các đường thẳng trong một cấu trúc set. Set
duy trì thứ tự của các đường thẳng và nếu ta lưu trữ các điểm giao nhau của các
đường thẳng liên tiếp, ta lại có thể tìm đường thẳng nhỏ nhất tại một điểm bằng
tìm kiếm nhị phân.

Chèn một đường thẳng có chi phí khấu hao $O(\log N)$ vì có thể có nhiều lần xóa
sau một lần chèn nhưng mỗi đường thẳng chỉ có thể bị xóa một lần. Truy vấn
đường thẳng nhỏ nhất tại một điểm mất $O(\log N)$ thời gian. Nhược điểm của
cách tiếp cận này là cấu trúc set khó cài đặt vì bao lồi và các điểm giao nhau
phải được duy trì và cập nhật sau mỗi lần chèn.

## Tài liệu tham khảo

* [KACTL, ICPC Team Reference Document, LineContainer.h](https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/LineContainer.h)
* [CP-Algorithms, *Convex hull trick*](https://cp-algorithms.com/geometry/convex_hull_trick.html)

```cpp
#include <iostream>
#include <limits>
#include <set>
#include <vector>
using namespace std;
using ll = long long;
const ll INF = numeric_limits<ll>::max();

struct Line {
    ll a, b;  // Biểu diễn đường thẳng y = ax + b
    ll p;  // Tọa độ x tại đó đường thẳng này giao với đường thẳng trước đó.
    // Trả về độ cao của đường thẳng tại x.
    ll operator()(ll x) const { return a * x + b; }
    bool operator<(Line oth) const { return a > oth.a; }
    bool operator<(ll x) const { return p < x; }
    ll intersect(Line oth) const {
        ll num = oth.b - b, dem = a - oth.a;
        return num / dem - ((num ^ dem) < 0 && num % dem);
    }
};

struct Hull {
    set<Line, less<>> hull;
    using Iter = set<Line, less<>>::iterator;
    // Tính lại điểm giao nhau của đường thẳng tại `it`.
    void fix(Iter it) {
        Line l = *it;
        it = hull.erase(it);
        if (it != end(hull)) {
            l.p = l.intersect(*it);
        } else {
            l.p = INF;
        }
        hull.insert(it, l);
    }
    // Kiểm tra xem đường thẳng tại `it` có vô dụng hay không.
    // Một đường thẳng được gọi là vô dụng nếu nó không bao giờ đạt giá trị nhỏ nhất.
    bool check(Iter it) {
        if (it != begin(hull) && next(it) != end(hull)) {
            auto a = *prev(it);
            auto b = *it;
            auto c = *next(it);
            return __int128(a.b - c.b) * (b.a - a.a) <=
                   __int128(c.a - a.a) * (a.b - b.b);
        }
        return false;
    }
    // Chèn đường thẳng l vào bao lồi.
    void insert(Line l) {
        auto it = hull.lower_bound(l);
        if (it != end(hull) && it->a == l.a) {
            if (l.b >= it->b) return;
            it = hull.erase(it);
        }
        it = hull.insert(it, l);
        if (check(it)) {
            hull.erase(it);
        } else {
            while (it != begin(hull) && check(prev(it))) {
                hull.erase(prev(it));
            }
            while (next(it) != end(hull) && check(next(it))) {
                hull.erase(next(it));
            }
            if (it != begin(hull)) fix(prev(it));
            if (next(it) != end(hull)) fix(next(it));
            fix(it);
        }
    }
    // Trả về đường thẳng thấp nhất tại điểm x.
    ll query(ll x) const {
        // Chú ý rằng chúng ta đã cài đặt hai hàm so sánh riêng biệt,
        // một để so sánh các đường thẳng với tọa độ và một để so sánh
        // với các đường thẳng khác.
        // Khi so sánh một đường thẳng với một tọa độ, thực chất chúng ta
        // đang so sánh điểm bắt đầu của miền hoạt động của đường thẳng với tọa độ.
        Line l = *hull.lower_bound(x);
        return l(x);
    }
};

int main() {
    int n, x;
    cin >> n >> x;

    vector<int> s(n), f(n);
    for (int i = 0; i < n; ++i) cin >> s[i];
    for (int i = 0; i < n; ++i) cin >> f[i];

    Hull h;
    h.insert({x, 0});

    for (int i = 0; i < n - 1; ++i) {
        ll b = h.query(s[i]);
        h.insert({f[i], b});
    }

    cout << h.query(s[n - 1]) << '\n';
}
```

## Solution 3: Cây Li Chao

Cách tiếp cận cuối cùng được trình bày ở đây được gọi là *cây Li Chao*. Nó là
một biến thể của cây phân đoạn cho phép lưu trữ các đường thẳng và truy vấn
đường thẳng nhỏ nhất tại một điểm nhất định. Nhược điểm duy nhất của cách tiếp
cận cây Li Chao là nó yêu cầu biết trước các điểm truy vấn.

## Tài liệu tham khảo

* [CP-Algorithms, *Li Chao Tree*](https://cp-algorithms.com/geometry/convex_hull_trick.html#toc-tgt-1)

```cpp
#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>
using namespace std;
using ll = long long;
const ll INF = numeric_limits<ll>::max();

struct Line {
    ll a, b;  // Biểu diễn đường thẳng y = ax + b
    // Trả về độ cao của đường thẳng tại x.
    ll operator()(ll x) const { return a * x + b; }
};

struct LiChao {
    int n;
    vector<Line> p;
    vector<ll> xs;

    // Xây dựng cây Li Chao hỗ trợ chèn bất kỳ đường thẳng nào và
    // truy vấn tại tất cả các vị trí có trong mảng x.
    LiChao(vector<int> x) {
        n = 1;
        while (n <= x.size()) n *= 2;
        p.assign(n * 2, Line{0, INF});
        sort(x.begin(), x.end());
        while (x.size() < n) x.push_back(x.back());
        xs.assign(n * 2, 0);
        for (int i = 0; i < n; ++i) xs[i + n] = x[i];
        for (int i = n - 1; i > 0; --i) {
            xs[i] = xs[i * 2];
        }
    }

    // Chèn đường thẳng x vào cây.
    void insert(Line x) {
        int s = 1;
        while (s < n) {
            ll p1 = xs[s * 2], p2 = xs[s * 2 + 1];
            bool c1 = x(p1) < p[s](p1);
            bool c2 = x(p2) < p[s](p2);
            if (c2) swap(x, p[s]);
            s = s * 2 + (c1 == c2);
        }
        if (x(xs[s]) < p[s](xs[s])) {
            p[s] = x;
        }
    }
    // Trả về đường thẳng thấp nhất tại điểm x.
    // Chú ý rằng x phải có trong vector các điểm đã cung cấp trước đó.
    ll query(ll x) {
        int i = lower_bound(xs.begin() + n, xs.end(), x) - xs.begin();
        ll r = INF;
        while (i > 0) {
            r = min(r, p[i](x));
            i /= 2;
        }
        return r;
    }
};

int main() {
    int n, x;
    cin >> n >> x;

    vector<int> s(n), f(n);
    for (int i = 0; i < n; ++i) cin >> s[i];
    for (int i = 0; i < n; ++i) cin >> f[i];

    LiChao l(s);
    l.insert({x, 0});

    for (int i = 0; i < n - 1; ++i) {
        ll b = l.query(s[i]);
        l.insert({f[i], b});
    }

    cout << l.query(s[n - 1]) << '\n';
}
```
