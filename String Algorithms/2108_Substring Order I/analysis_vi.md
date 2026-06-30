# 2108 - Thứ tự xâu con I

## Cách giải 1: mảng hậu tố

Ta duyệt qua mảng hậu tố và tính số lượng xâu con phân biệt mà mỗi hậu tố tạo ra. Điều này có thể thực hiện bằng công thức

$$n - \textrm{sa}[i] - \textrm{lcp}[i]$$

trong đó $n - \textrm{sa}[i]$ là độ dài của hậu tố và $\textrm{lcp}[i]$ cho biết số lượng tiền tố đã được đếm.

Đầu tiên ta xác định hậu tố chứa xâu con nhỏ thứ $k$ và sau đó in ra tiền tố có độ dài thích hợp.

Xây dựng mảng hậu tố mất $O(n \log^2 n)$ thời gian và xây dựng mảng LCP mất $O(n)$ thời gian. Sau đó, ta có thể tính đáp án trong $O(n)$ thời gian.

```cpp
#include <algorithm>
#include <iostream>
#include <numeric>
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
    for (int i = 1; i <= n; i++) {
        int add = n - sa.sa[i] - sa.lcp[i];
        if (k > add) {
            k -= add;
        } else {
            cout << s.substr(sa.sa[i], sa.lcp[i] + k) << "\n";
            break;
        }
    }
}
```

## Cách giải 2: automaton hậu tố

Ta tính một giá trị `count` cho mỗi trạng thái của automaton: số lượng đường đi bắt đầu tại trạng thái đó và kết thúc tại một trạng thái nào đó. Sau đó, ta sinh xâu con nhỏ thứ $k$ từng bước một.

Giả sử ta đang ở một trạng thái nào đó của automaton và muốn chọn ký tự tiếp theo. Ta duyệt qua các ký tự theo thứ tự bảng chữ cái và kiểm tra, với mỗi ký tự, giá trị `count` của trạng thái tiếp theo tương ứng với số lượng xâu con bắt đầu bằng ký tự đó. Điều này cho phép ta xác định ký tự tiếp theo trong xâu con và tiếp tục tương tự.

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
        ll count;
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
        dfs(first);
    }

    void dfs(State *cur) {
        if (cur->count) return;
        cur->count = 1;
        for (auto [c, p] : cur->next) {
            dfs(p);
            cur->count += p->count;
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
    while (k) {
        for (auto [c, p] : cur->next) {
            if (p->count < k) {
                k -= p->count;
            } else {
                cout << c;
                k--;
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
