# 1110 - Minimal Rotation

A useful trick in this problem is to first create a new string that consists of
two copies of the original string. For example, if our input string is `acab`,
we create a string `acabacab`. After that, it suffices to find the
lexicographically minimal substring of length $n$ in the new string.

## Solution 1 (brute force)

A simple brute force solution is to go through the string and maintain a
value `pos`: the starting position of a minimal substring of length $n$ seen so
far.

Unfortunately, this solution requires $O(n^2)$ time and is too slow for solving
the problem efficiently.

```cpp
#include <iostream>
using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size();
    s = s + s;

    int pos = 0;
    for (int i = 1; i < n; i++) {
        if (s.substr(pos, n) > s.substr(i, n)) {
            pos = i;
        }
    }
    cout << s.substr(pos, n) << "\n";
}
```

## Solution 2 (hashing and binary search)

We can improve the brute force solution by using hashing and binary search.

To efficiently compare two substrings, we first find the length of the common
prefix of the substrings and then compare the next character after it. Using
hashing, we can check the equality of two substrings in $O(1)$ time. We
determine the length of the common prefix using binary search, so we only have
to check the equality of $O(\log n)$ prefixes.

Since we check $O(n)$ positions and each comparison takes $O(\log n)$ time, the
resulting algorithm works in $O(n \log n)$ time.

```cpp
#include <chrono>
#include <iostream>
#include <random>
#include <vector>
using namespace std;
using ll = long long;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const ll M = 991831889;
const ll C = uniform_int_distribution<ll>(0.1 * M, 0.9 * M)(rng);

struct HashString {
    int n;
    vector<ll> pows, sums;

    HashString(string s) : n(s.size()), pows(n + 1, 1), sums(n + 1) {
        for (int i = 1; i <= n; i++) {
            pows[i] = pows[i - 1] * C % M;
            sums[i] = (sums[i - 1] * C + s[i - 1]) % M;
        }
    }

    // Returns the hash of the substring [l, r)
    ll hash(int l, int r) {
        ll h = sums[r] - sums[l] * pows[r - l];
        return (h % M + M) % M;
    }
};

int main() {
    string s;
    cin >> s;
    int n = s.size();
    s = s + s;

    HashString h(s);

    auto cmp = [&](int a, int b) {
        int len = 0;
        for (int add = n; add >= 1; add /= 2) {
            while (len + add < n) {
                ll hash1 = h.hash(a, a + len + add);
                ll hash2 = h.hash(b, b + len + add);
                if (hash1 != hash2) break;
                len += add;
            }
        }
        return s[a + len] > s[b + len];
    };

    int pos = 0;
    for (int i = 1; i < n; i++) {
        if (cmp(pos, i)) pos = i;
    }
    cout << s.substr(pos, n) << "\n";
}
```

## Solution 3 (Lyndon factorization)

We maintain two values: `pos` denotes the starting position of a minimal
substring seen so far, and `cur` denotes our current starting position.

On each step, we determine a value $k$: the length of the common prefix of
the substrings starting at positions `pos` and `cur` (we make sure that $k$ is
at most $n$). Then we check the next character after the common prefix to
compare the substrings.

If the substring at position `pos` is not greater than the substring at position
`cur`, we increase `cur` by $k+1$. We can do that because no suffix of the
common prefix can start a new minimal substring.

Otherwise, we know that the substring starting at `cur` is smaller than the
substring starting at `pos`. To make the algorithm efficient, we always increase
`pos` by at least $k+1$. We can do that because if the common prefixes overlap,
they form a repetition which we can skip.

The solution works in $O(n)$ time because after matching $k$ characters in the
inner loop, either `pos` or `cur` always increases by $k$.

```cpp
#include <iostream>
using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size();
    s = s + s;

    int pos = 0;
    int cur = 1;
    while (cur < n) {
        int k = 0;
        while (k < n && s[pos + k] == s[cur + k]) k++;
        if (s[pos + k] <= s[cur + k]) {
            cur += k + 1;
        } else {
            pos = max(pos + k + 1, cur);
            cur = pos + 1;
        }
    }

    cout << s.substr(pos, n) << "\n";
}
```

## References

* [Lexicographically\_minimal\_string\_rotation (Wikipedia)](https://en.wikipedia.org/wiki/Lexicographically_minimal_string_rotation)
* [Lyndon word (Wikipedia)](https://en.wikipedia.org/wiki/Lyndon_word)
* [Lyndon factorization (CP-Algorithms)](https://cp-algorithms.com/string/lyndon_factorization.html)