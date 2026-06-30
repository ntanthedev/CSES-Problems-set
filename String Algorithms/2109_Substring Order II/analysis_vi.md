# 2109 - Thứ tự xâu con II

## Cách giải 1: mảng hậu tố

Ta tạo hai cấu trúc dữ liệu bổ sung:

* `sums` là một mảng tổng tiền tố, dùng để tính tổng độ dài của các hậu tố trong một đoạn của mảng hậu tố
* `lcps` là một tập hợp tất cả các giá trị LCP, dùng để tìm vị trí mảng hậu tố tiếp theo có một giá trị LCP cho trước

Ta xây dựng xâu con từng bước một sử dụng các cấu trúc dữ liệu và duy trì đoạn tương ứng trên mảng hậu tố. Khi ta đã tạo một xâu con có độ dài $l$, ta chia đoạn thành các đoạn con, mỗi đoạn con gồm các hậu tố có cùng một ký tự tại vị trí $l$. Ta tạo các đoạn con bằng cách tìm các vị trí có giá trị LCP là $l$. Sau đó, ta có thể xác định ký tự tiếp theo bằng cách tính tổng độ dài của các hậu tố trong mỗi đoạn.

Xây dựng mảng hậu tố mất $O(n \log^2 n)$ thời gian và xây dựng mảng LCP mất $O(n)$ thời gian. Sau đó, ta có thể tính đáp án trong $O(n \log n)$ thời gian.

```cpp
#include <algorithm>
#include <iostream>
#include <numeric>
#include <set>
#include <vector>
using namespace std;
using ll = long long;

struct SuffixArray {
    string s;
    int n;
    vector<int> sa;
    vector<int> lcp;

    SuffixArray(string x) : s(x + "$"), n(s.size()), sa(n), lcp(n) {
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
            inv[i]--;
            sa[inv[i]] = i;
        }
        for (int i = 0; i < n - 1; i++) {
            int k = inv[i];
            if (i) lcp[k] = max(0, lcp[inv[i - 1]] - 1);
            while (s[sa[k - 1] + lcp[k]] == s[sa[k] + lcp[k]]) lcp[k]++;
        }
    }
};

int main() {
    string s;
    cin >> s;
    int n = s.size();
    ll k;
    cin >> k;

    SuffixArray sa(s);

    vector<ll> sums(n + 1);
    for (int i = 1; i <= n; i++) {
        sums[i] = sums[i - 1] + n - sa.sa[i];
    }

    set<pair<int, int>> lcps;
    for (int i = 1; i <= n; i++) {
        lcps.emplace(sa.lcp[i], i);
    }
    lcps.emplace(0, n + 1);

    int left = 1;
    int right = n + 1;
    int len = 0;
    while (k > 0) {
        int end = right;
        while (true) {
            auto it = lcps.upper_bound({len, left});
            if (it != lcps.end() && it->first == len && it->second < end) {
                right = it->second;
            } else {
                right = end;
            }
            ll count = sums[right - 1] - sums[left - 1];
            count -= len * (right - left);
            if (k > count) {
                k -= count;
                left = right;
            } else {
                cout << s[sa.sa[left] + len];
                k -= right - left;
                len++;
                break;
            }
        }
    }
    cout << "\n";
}
```

## Cách giải 2: automaton hậu tố

Ta tính hai giá trị cho mỗi trạng thái của automaton: `count` là tổng số xâu con (không nhất thiết phân biệt) bắt đầu tại trạng thái đó, và `to_final` là số đường đi từ trạng thái đó đến một trạng thái kết thúc (tức là số hậu tố bắt đầu tại trạng thái đó).

Ta xây dựng xâu con từng bước một và luôn xác định ký tự tiếp theo bằng cách duyệt qua các ký tự theo thứ tự bảng chữ cái và kiểm tra các giá trị `count`. Vì ta xét tất cả các xâu con, các giá trị `to_final` tương ứng với số lượng xâu con sau khi thêm một ký tự.

Ta có thể xây dựng automaton và sinh xâu con trong $O(n)$ thời gian.

```cpp
#include <iostream>
#include <map>
#include <vector>
using namespace std;
using ll = long long;

struct SuffixAutomaton {
    struct State {
        int len;
        State *link;
        map<char, State *> next;
        bool final;
        ll count;
        ll to_final;
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
        if (cur->final) {
            cur->count = cur->to_final = 1;
        }
        for (auto [c, p] : cur->next) {
            dfs(p);
            cur->count += p->count + p->to_final;
            cur->to_final += p->to_final;
        }
    }
};

int main() {
    string s;
    cin >> s;
    ll k;
    cin >> k;

    SuffixAutomaton sa(s);
    auto cur = sa.first;
    while (k > 0) {
        for (auto [c, p] : cur->next) {
            if (p->count < k) {
                k -= p->count;
            } else {
                cout << c;
                k -= p->to_final;
                cur = p;
                break;
            }
        }
    }
    cout << "\n";
}
```

## Tài liệu tham khảo

* [Mảng hậu tố (Wikipedia)](https://en.wikipedia.org/wiki/Suffix_array)
* [Mảng LCP (Wikipedia)](https://en.wikipedia.org/wiki/LCP_array)
* [Automaton hậu tố (Wikipedia)](https://en.wikipedia.org/wiki/Suffix_automaton)
