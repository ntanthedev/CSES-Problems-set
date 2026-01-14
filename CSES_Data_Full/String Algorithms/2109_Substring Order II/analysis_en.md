# 2109 - Substring Order II

## Solution 1: suffix array

We create two additional data structures:

* `sums` is a prefix sum array, using which we can calculate the sum of the
  lengths of suffixes in a suffix array range
* `lcps` is a set of all LCP values, using which we can find the next suffix
  array position that has a given LCP value

We contruct the substring step by step using the data structures, and maintain
the corresponding suffix array range. When we have created a substring of length
$l$, we divide the range into subranges, each of which has suffixes with a
fixed character at position $l$. We create the subranges by finding positions
where the LCP value is $l$. Then, we can determine the next character by
calculating the total length of suffixes in each range.

Creating the suffix array takes $O(n \log^2 n)$ time and creating the LCP-array
takes $O(n)$ time. After that, we can calculate the answer in $O(n \log n)$
time.

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

## Solution 2: suffix automaton

We calculate two values for each automaton state: `count` denotes the total
number of (not necessarily distinct) substrings that begin at the state, and
`to_final` denotes the number of paths from the state to a final state (i.e.,
the number of suffixes that begin at the state).

We construct the substring step by step and we always determine the next
character by going through the characters in alphabetical order and checking the
`count` values. Since we consider all substrings, the `to_final` values
correspond to the number of substrings after adding a character.

We can both construct the automaton and generate the substring in $O(n)$ time.

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

## References

* [Suffix array (Wikipedia)](https://en.wikipedia.org/wiki/Suffix_array)
* [LCP array (Wikipedia)](https://en.wikipedia.org/wiki/LCP_array)
* [Suffix automaton (Wikipedia)](https://en.wikipedia.org/wiki/Suffix_automaton)