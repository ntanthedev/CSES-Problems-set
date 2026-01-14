# 2105 - Distinct Substrings

## Solution 1: suffix array

We create an additional data structure for the suffix array: the LCP-array. It
contains, for each suffix array position $i>0$, the length of the longest common
prefix of suffixes whose positions in the suffix array are $i-1$ and $i$.

Let $\textrm{lcp}[i]$ denote the LCP value at position $i$. The answer to the
problem is

$$\frac{n(n+1)}{2} - \sum\_{i=1}^n \textrm{lcp}[i]$$

where we first count the number of all substrings and then subtract the number
of repeating substrings. Note that the length of the LCP-array is $n+1$ because
we add `$` to the string before creating the arrays.

Creating the suffix array takes $O(n \log^2 n)$ time and creating the LCP-array
takes $O(n)$ time. After that, we can calculate the answer in $O(n)$ time.

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

## Solution 2: suffix automaton

We calculate a value `count` for each automaton state: the number of paths that
begin at that state and end at some state. Since each path corresponds to a
distinct string, the answer to the problem is the number of such paths that
begin at the first state of the automaton.

Note that we should not count the empty string, so we decrease the number of
strings by one before printing the result.

We can both construct the automaton and count the paths in $O(n)$ time.

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

## References

* [Suffix array (Wikipedia)](https://en.wikipedia.org/wiki/Suffix_array)
* [LCP array (Wikipedia)](https://en.wikipedia.org/wiki/LCP_array)
* [Suffix automaton (Wikipedia)](https://en.wikipedia.org/wiki/Suffix_automaton)