# 2105 - Xâu Con Phân Biệt

## Cách 1: mảng hậu tố

Ta tạo một cấu trúc dữ liệu bổ sung cho mảng hậu tố: mảng LCP. Mảng này chứa, với mỗi vị trí $i>0$ của mảng hậu tố, độ dài của tiền tố chung dài nhất của các hậu tố có vị trí trong mảng hậu tố là $i-1$ và $i$.

Gọi $\textrm{lcp}[i]$ là giá trị LCP tại vị trí $i$. Đáp án của bài toán là

$$\frac{n(n+1)}{2} - \sum\_{i=1}^n \textrm{lcp}[i]$$

trong đó đầu tiên ta đếm số lượng tất cả xâu con, sau đó trừ đi số lượng xâu con lặp lại. Lưu ý rằng độ dài của mảng LCP là $n+1$ vì ta thêm `$` vào xâu trước khi tạo các mảng.

Việc tạo mảng hậu tố mất $O(n \log^2 n)$ thời gian và tạo mảng LCP mất $O(n)$ thời gian. Sau đó, ta có thể tính đáp án trong $O(n)$ thời gian.

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
    SuffixArray sa(s);

    int n = s.size();
    ll ans = (ll)n * (n + 1) / 2;
    for (int i = 1; i <= n; i++) {
        ans -= sa.lcp[i];
    }
    cout << ans << "\n";
}
```

## Cách 2: ôtômat hậu tố

Ta tính giá trị `count` cho mỗi trạng thái của ôtômat: số đường đi bắt đầu từ trạng thái đó và kết thúc tại một trạng thái nào đó. Vì mỗi đường đi tương ứng với một xâu phân biệt, đáp án của bài toán là số lượng đường đi như vậy bắt đầu từ trạng thái đầu tiên của ôtômat.

Lưu ý rằng ta không nên đếm xâu rỗng, vì vậy ta giảm số lượng xâu đi một trước khi in kết quả.

Ta có thể xây dựng ôtômat và đếm số đường đi trong $O(n)$ thời gian.

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
    SuffixAutomaton sa(s);
    cout << sa.first->count - 1 << "\n";
}
```

## Tài liệu tham khảo

* [Mảng hậu tố (Wikipedia)](https://en.wikipedia.org/wiki/Suffix_array)
* [Mảng LCP (Wikipedia)](https://en.wikipedia.org/wiki/LCP_array)
* [Ôtômat hậu tố (Wikipedia)](https://en.wikipedia.org/wiki/Suffix_automaton)
