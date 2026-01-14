# 2108 - Substring Order I

## Solution 1: suffix array

We go through the suffix array and calculate the number of distinct substrings
each suffix produces. This can be done using the formula

$$n - \textrm{sa}[i] - \textrm{lcp}[i]$$

where $n - \textrm{sa}[i]$ is the length of the suffix and $\textrm{lcp}[i]$
gives the number of prefixes that have already been counted.

We first locate the suffix that contains the $k$th smallest substring and then
print the prefix that has the correct length.

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

## Solution 2: suffix automaton

We calculate a value `count` for each automaton state: the number of paths that
begin at that state and end at some state. After that, we generate the $k$th
smallest substring step by step.

Suppose we are in some automaton state and we want to choose the next character.
We can go through the characters in alphabetical order and check, for each
character, the `count` value of the next state which corresponds to the number
of substrings that begin at that character. This allows us to determine the next
character in the substring and continue in the same way.

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

## References

* [Suffix array (Wikipedia)](https://en.wikipedia.org/wiki/Suffix_array)
* [LCP array (Wikipedia)](https://en.wikipedia.org/wiki/LCP_array)
* [Suffix automaton (Wikipedia)](https://en.wikipedia.org/wiki/Suffix_automaton)