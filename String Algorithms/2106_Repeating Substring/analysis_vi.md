# 2106 - Xâu Con Lặp Lại

## Cách 1: mảng hậu tố

Ta tạo một cấu trúc dữ liệu bổ sung cho mảng hậu tố: mảng LCP chứa, với mỗi vị trí $i>0$ của mảng hậu tố, độ dài của tiền tố chung dài nhất của các hậu tố có vị trí trong mảng hậu tố là $i-1$ và $i$.

Độ dài lớn nhất của một mẫu lặp lại bằng giá trị lớn nhất trong mảng LCP. Ta có thể tìm giá trị lớn nhất và mẫu tương ứng bằng cách duyệt qua mảng LCP.

Việc tạo mảng hậu tố mất $O(n \log^2 n)$ thời gian và tạo mảng LCP mất $O(n)$ thời gian. Sau đó, ta có thể tính đáp án trong $O(n)$ thời gian.

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
    int len = 0;
    int pos = 0;
    for (int i = 1; i <= n; i++) {
        if (sa.lcp[i] > len) {
            len = sa.lcp[i];
            pos = sa.sa[i];
        }
    }
    if (len == 0) {
        cout << "-1\n";
    } else {
        cout << s.substr(pos, len) << "\n";
    }
}
```

## Cách 2: ôtômat hậu tố

Ta tính hai giá trị cho mỗi trạng thái của ôtômat: `count` biểu thị số đường đi bắt đầu từ trạng thái và kết thúc tại một trạng thái kết thúc, và `max` biểu thị độ dài lớn nhất của một đường đi bắt đầu từ trạng thái và kết thúc tại một trạng thái có `count` ít nhất là hai.

Sau khi tính các giá trị, giá trị `max` của trạng thái bắt đầu bằng độ dài của mẫu lặp lại dài nhất. Ta có thể tìm mẫu từng bước bằng cách luôn di chuyển đến trạng thái tiếp theo có giá trị `max` nhỏ hơn một so với giá trị `max` của trạng thái hiện tại.

Ta có thể xây dựng ôtômat, tính các giá trị và tìm mẫu trong $O(n)$ thời gian.

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
        int max;
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
            if (p->count > 1) {
                cur->max = max(cur->max, p->max + 1);
            }
        }
    }
};

int main() {
    string s;
    cin >> s;
    SuffixAutomaton sa(s);

    auto cur = sa.first;
    if (cur->max == 0) {
        cout << "-1\n";
    } else {
        while (cur->max) {
            for (auto [c, p] : cur->next) {
                if (p->max == cur->max - 1) {
                    cout << c;
                    cur = p;
                    break;
                }
            }
        }
        cout << "\n";
    }
}
```

## Cách 3: tìm kiếm nhị phân và hàm băm

Đây là một cách giải khác tìm độ dài mẫu lặp lại dài nhất bằng tìm kiếm nhị phân. Để kiểm tra độ dài $k$ có hợp lệ hay không, ta tạo một tập hợp tất cả giá trị băm của các xâu con có độ dài $k$. Nếu tập hợp chứa cùng một giá trị băm hai lần, thì ta đã tìm được một mẫu lặp lại.

Trong bài toán này, giá trị băm 32-bit không đủ an toàn vì ta thực sự so sánh giá trị băm của *tất cả* các cặp xâu con có độ dài $k$ và có thể dễ dàng xảy ra va chạm (bài toán nghịch lý ngày sinh). Vì lý do này, ta làm việc với giá trị băm 64-bit.

Thuật toán hoạt động trong $O(n \log^2 n)$ thời gian vì nó kiểm tra $O(\log n)$ độ dài mẫu và mỗi lần kiểm tra mất $O(n \log n)$ thời gian. Lưu ý rằng cách giải này chậm hơn nhiều so với hai cách giải trước và chỉ vừa kịp giới hạn thời gian.

```cpp
#include <chrono>
#include <iostream>
#include <random>
#include <set>
#include <vector>
using namespace std;
using ll = long long;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct HashString {
    const ll M = 1111111111111111111;  // M là số nguyên tố.
    const ll C = uniform_int_distribution<ll>(0.1 * M, 0.9 * M)(rng);

    ll mul(ll a, ll b) { return __int128(a) * b % M; }

    int n;
    vector<ll> pows, sums;

    HashString(string s) : n(s.size()), pows(n + 1, 1), sums(n + 1) {
        for (int i = 1; i <= n; i++) {
            pows[i] = mul(pows[i - 1], C);
            sums[i] = (mul(sums[i - 1], C) + s[i - 1]) % M;
        }
    }

    // Trả về giá trị băm của xâu con [l, r)
    ll hash(int l, int r) {
        ll h = sums[r] - mul(sums[l], pows[r - l]);
        return (h % M + M) % M;
    }
};

int main() {
    string s;
    cin >> s;
    int n = s.size();
    HashString hs(s);

    auto find = [&](int len) {
        set<ll> hashes;
        for (int i = 0; i <= n - len; i++) {
            ll h = hs.hash(i, i + len);
            if (hashes.count(h)) return i;
            hashes.insert(h);
        }
        return -1;
    };

    int len = 0;
    int first = 0;
    for (int b = 1 << 16; b >= 1; b /= 2) {
        int pos = find(len + b);
        if (pos == -1) continue;
        first = pos;
        len += b;
    }

    if (len == 0) {
        cout << "-1\n";
    } else {
        cout << s.substr(first, len) << "\n";
    }
}
```

## Tài liệu tham khảo

* [Mảng hậu tố (Wikipedia)](https://en.wikipedia.org/wiki/Suffix_array)
* [Mảng LCP (Wikipedia)](https://en.wikipedia.org/wiki/LCP_array)
* [Ôtômat hậu tố (Wikipedia)](https://en.wikipedia.org/wiki/Suffix_automaton)
