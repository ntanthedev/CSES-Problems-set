# 2103 - Đếm Mẫu

## Cách 1: mảng hậu tố

Ta tạo một mảng hậu tố (suffix array) cho xâu, sau đó có thể đếm hiệu quả số lần xuất hiện của mẫu trong xâu.

Đoạn mã sau tạo mảng hậu tố bằng phương pháp prefix doubling và hoạt động trong $O(n \log^2 n)$ thời gian. Ta sử dụng tìm kiếm nhị phân để tìm khoảng của một mẫu trong mảng hậu tố trong $O(m \log n)$ thời gian.

```cpp
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

struct SuffixArray {
    string s;
    int n;
    vector<int> sa;

    SuffixArray(string x) : s(x + "$"), n(s.size()), sa(n) {
        int bound = 1;
        while (bound < n) bound *= 2;
        vector<int> inv(2 * bound);
        copy(s.begin(), s.end(), inv.begin());
        vector<int> order(n);
        iota(order.begin(), order.end(), 0);
        for (int add = 1; add < bound; add *= 2) {
            vector<pair<int, int>> pairs(n);
            for (int i = 0; i < n; i++) {
                pairs[i] = {inv[i], inv[i + add]};
            }
            sort(order.begin(), order.end(),
                 [&](int a, int b) { return pairs[a] < pairs[b]; });
            int label = 1;
            for (int i = 0; i < n; i++) {
                label += i && pairs[order[i - 1]] != pairs[order[i]];
                inv[order[i]] = label;
            }
        }
        for (int i = 0; i < n; i++) {
            sa[inv[i] - 1] = i;
        }
    }

    // Trả về khoảng (nửa mở) nơi mẫu p xuất hiện trong mảng hậu tố
    pair<int, int> find(string p) {
        int m = p.size();
        auto left = sa.begin();
        auto right = sa.end();
        for (int i = 0; i < m; i++) {
            auto cmp = [&](int e, int v) {
                return s[e + i] < v;
            };
            auto new_left = lower_bound(left, right, p[i], cmp);
            auto new_right = lower_bound(left, right, p[i] + 1, cmp);
            left = new_left;
            right = new_right;
        }
        return {left - sa.begin(), right - sa.begin()};
    }
};

int main() {
    string s;
    cin >> s;
    SuffixArray sa(s);

    int k;
    cin >> k;
    for (int ki = 1; ki <= k; ki++) {
        string p;
        cin >> p;
        auto [l, r] = sa.find(p);
        cout << r - l << "\n";
    }
}
```

## Cách 2: ôtômat hậu tố

Ta cũng có thể giải bài toán bằng một ôtômat hậu tố (suffix automaton) lưu tất cả các hậu tố của một xâu dưới dạng gọn.

Đoạn mã sau tạo ôtômat hậu tố và sau đó sử dụng duyệt theo chiều sâu (DFS) để tính giá trị `count` cho mỗi trạng thái: số cách để đến một trạng thái kết thúc khi bắt đầu từ trạng thái đó. Giá trị này tương ứng với số lần xuất hiện của một mẫu trong xâu.

Việc xây dựng ôtômat hậu tố mất $O(n)$ thời gian và xử lý mỗi mẫu mất $O(m)$ thời gian.

```cpp
#include <iostream>
#include <map>
#include <vector>
using namespace std;

struct SuffixAutomaton {
    struct State {
        int len;
        State *link;
        map<char, State *> next;
        bool final;
        int count;
    };

    State *first, *last;

    SuffixAutomaton(string s) {
        first = last = new State{};
        for (auto c : s) {
            auto *add = new State{};
            add->len = last->len + 1;
            add->link = first;
            State *cur = last;
            while (cur && !cur->next[c]) {
                cur->next[c] = add;
                cur = cur->link;
            }
            if (cur && cur->next[c] != add) {
                State *mid = cur->next[c];
                if (cur->len + 1 == mid->len) {
                    add->link = mid;
                } else {
                    auto *copy = new State(*mid);
                    copy->len = cur->len + 1;
                    add->link = mid->link = copy;
                    while (cur && cur->next[c] == mid) {
                        cur->next[c] = copy;
                        cur = cur->link;
                    }
                }
            }
            last = add;
        }
        State *cur = last;
        while (cur->len) {
            cur->final = true;
            cur = cur->link;
        }
        dfs(first);
    }

    void dfs(State *cur) {
        if (cur->count) return;
        if (cur->final) cur->count = 1;
        for (auto [c, p] : cur->next) {
            dfs(p);
            cur->count += p->count;
        }
    }

    int count(string p) {
        State *cur = first;
        for (auto c : p) {
            if (!cur->next[c]) return 0;
            cur = cur->next[c];
        }
        return cur->count;
    }
};

int main() {
    string s;
    cin >> s;
    SuffixAutomaton sa(s);

    int k;
    cin >> k;
    for (int ki = 1; ki <= k; ki++) {
        string p;
        cin >> p;
        cout << sa.count(p) << "\n";
    }
}
```

## Tài liệu tham khảo

* [Mảng hậu tố (Wikipedia)](https://en.wikipedia.org/wiki/Suffix_array)
* [Ôtômat hậu tố (Wikipedia)](https://en.wikipedia.org/wiki/Suffix_automaton)
