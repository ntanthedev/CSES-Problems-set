# 2110 - Substring Distribution

## Solution 1: suffix array

We go through the suffix array and determine, for each position $i$, the lengths
of prefixes that should be counted.

Since we want to count each distinct substring only once, the minimum prefix
length is $\textrm{lcp}[i]+1$. The maximum prefix length is $n-\textrm{sa}[i]$,
which is the length of the suffix. Thus, we always have a contiguous range of
lengths.

We first construct a vector `diff` that contains the differences between
consecutive lengths. By going through that vector, we can efficiently determine
the distribution of lengths.

The following code creates the suffix array in $O(n \log^2 n)$ time and the LCP
array in $O(n)$ time. Then, it calculates the distribution in $O(n)$ time.

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
    SuffixArray sa(s);

    vector<int> diff(n + 2);
    for (int i = 1; i <= n; i++) {
        diff[sa.lcp[i] + 1]++;
        diff[n - sa.sa[i] + 1]--;
    }
    ll count = 0;
    for (int i = 1; i <= n; i++) {
        count += diff[i];
        cout << count << " ";
    }
    cout << "\n";
}
```

## Solution 2: suffix automaton

Each suffix automaton state corresponds to a set of substrings whose lengths
form a contiguous range.

The field `len` contains the maximum length of a substring in a state, and all
other substrings are suffixes of that substring. Moreover, the field `link`
points to a previous state that contains smaller suffixes of the substring.

Using the fields `len` and `link`, we can construct a vector `diff` like in the
previous solution, and then construct the distribution of lengths.

The construction of the suffix automaton takes $O(n)$ time, and calculating the
distribution also takes $O(n)$ time.

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
        bool seen;
    };

    vector<int> diff;

    State *first, *last;

    SuffixAutomaton(string s) : diff(s.size() + 2) {
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
        if (cur->seen) return;
        cur->seen = true;
        if (cur != first) {
            diff[cur->len + 1]--;
            diff[cur->link->len + 1]++;
        }
        for (auto [c, p] : cur->next) {
            dfs(p);
        }
    }
};

int main() {
    string s;
    cin >> s;
    int n = s.size();
    SuffixAutomaton sa(s);

    ll count = 0;
    for (int i = 1; i <= n; i++) {
        count += sa.diff[i];
        cout << count << " ";
    }
    cout << "\n";
}
```

## References

* [Suffix array (Wikipedia)](https://en.wikipedia.org/wiki/Suffix_array)
* [LCP array (Wikipedia)](https://en.wikipedia.org/wiki/LCP_array)
* [Suffix automaton (Wikipedia)](https://en.wikipedia.org/wiki/Suffix_automaton)