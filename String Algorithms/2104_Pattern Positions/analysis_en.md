# 2104 - Pattern Positions

## Solution 1: suffix array

To find the first pattern position, we should find the minimum value in the
suffix array range that corresponds to the pattern. We can do that by creating a
segment tree for the suffix array.

The following code creates the suffix array in $O(n \log^2 n)$ time and the
segment tree in $O(n)$ time. For each query, we first find the suffix array
range in $O(m \log n)$ time and then the minimum position in $O(\log n)$ time.

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

    // Returns the (half-open) range where pattern p appears in the suffix array
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

struct MinTree {
    int n;
    vector<int> tree;

    MinTree(vector<int> v) {
        n = 1;
        while (n < v.size()) n *= 2;
        tree.resize(2 * n);
        for (int i = 0; i < v.size(); i++) {
            tree[n + i] = v[i];
        }
        for (int i = n - 1; i >= 1; i--) {
            tree[i] = min(tree[2 * i], tree[2 * i + 1]);
        }
    }

    int find(int l, int r) {
        l += n;
        r += n;
        int ans = tree[l];
        while (l <= r) {
            if (l % 2 == 1) ans = min(ans, tree[l++]);
            if (r % 2 == 0) ans = min(ans, tree[r--]);
            l /= 2;
            r /= 2;
        }
        return ans;
    }
};

int main() {
    string s;
    cin >> s;
    SuffixArray sa(s);
    MinTree min(sa.sa);

    int k;
    cin >> k;
    for (int ki = 1; ki <= k; ki++) {
        string p;
        cin >> p;
        auto [l, r] = sa.find(p);
        if (l == r) {
            cout << "-1\n";
        } else {
            cout << min.find(l, r - 1) + 1 << "\n";
        }
    }
}
```

## Solution 2: suffix automaton

We calculate a value `pos` for each automaton state: the minimum position of a
suffix that begins at that state. The position of the last state is $n$, and we
calculate the values for other states using depth-first search.

After finding the state of a pattern, the first position where the pattern
appears can be calculated using the formula $x-m$ where $x$ is the position of
the state and $m$ is the length of the pattern.

The construction of the suffix automaton takes $O(n)$ time and processing each
pattern takes $O(m)$ time.

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
        int pos;
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
        last->pos = s.size();
        dfs(first);
    }

    void dfs(State *cur) {
        if (cur->pos) return;
        cur->pos = last->pos;
        for (auto [c, p] : cur->next) {
            dfs(p);
            cur->pos = min(cur->pos, p->pos - 1);
        }
    }

    int pos(string p) {
        State *cur = first;
        for (auto c : p) {
            if (!cur->next[c]) return -1;
            cur = cur->next[c];
        }
        return cur->pos - p.size();
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
        int pos = sa.pos(p);
        cout << (pos != -1 ? pos + 1 : -1) << "\n";
    }
}
```

## References

* [Suffix array (Wikipedia)](https://en.wikipedia.org/wiki/Suffix_array)
* [Suffix automaton (Wikipedia)](https://en.wikipedia.org/wiki/Suffix_automaton)