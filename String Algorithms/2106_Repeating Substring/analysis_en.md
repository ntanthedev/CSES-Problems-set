# 2106 - Repeating Substring

## Solution 1: suffix array

We create an additional data structure for the suffix array: a LCP-array that
contains, for each suffix array position $i>0$, the length of the longest common
prefix of suffixes whose positions in the suffix array are $i-1$ and $i$.

The maximum length of a repeating pattern equals the maximum value in the
LCP-array. We can find the maximum value and the corresponding pattern by going
through the LCP-array.

Creating the suffix array takes $O(n \log^2 n)$ time and creating the LCP-array
takes $O(n)$ time. After that, we can calculate the answer in $O(n)$ time.

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

## Solution 2: suffix automaton

We calculate two values for each automaton state: `count` denotes the number of
paths that begin at the state and end at a final state, and `max` denotes the
maximum length of a path that begins at the state and ends at a state whose
`count` is at least two.

After calculating the values, the `max` value of the start state equals the
length of the longest repeating pattern. We can find the pattern step by step by
always moving to a next state whose `max` value is one smaller than the `max`
value of the current state.

We can construct the automaton, calculate the values and find the pattern in
$O(n)$ time.

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

## Solution 3: binary search and hashing

Here is yet another solution that finds the longest repeating pattern length
using binary search. To check if a length $k$ is valid, we create a set of all
hash values of substrings of length $k$. If the set contains the same hash value
two times, then we have found a repeating pattern.

In this problem a 32-bit hash value is not safe enough because we actually
compare hash values of *all* pairs of substrings of length $k$ and there could
easily be collisions (the birthday paradox problem). For this reason, we work
with 64-bit hash values.

The algorithm works in $O(n \log^2 n)$ time because it checks $O(\log n)$
pattern lengths and each check takes $O(n \log n)$ time. Note that this solution
is much slower than the two previous solutions and it barely fits in the time
limit.

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
    const ll M = 1111111111111111111;  // M is a prime.
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

    // Returns the hash of the substring [l, r)
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

## References

* [Suffix array (Wikipedia)](https://en.wikipedia.org/wiki/Suffix_array)
* [LCP array (Wikipedia)](https://en.wikipedia.org/wiki/LCP_array)
* [Suffix automaton (Wikipedia)](https://en.wikipedia.org/wiki/Suffix_automaton)