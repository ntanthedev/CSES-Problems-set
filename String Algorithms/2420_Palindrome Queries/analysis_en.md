# 2420 - Palindrome Queries

We use a segment tree that maintains a string and supports two operations:

* Set the character at position $k$ to $x$
* Calculate the hash value of a substring from position $l$ to position $r$

We create two such segment trees: one for the actual string and one for the
reverse string. Then we can efficiently calculate the hash value of a substring
and the hash value of its reverse. The substring is a palindrome exactly when
the hash values are the same.

The solution works in $O(n + m \log n)$ time.

```cpp
#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>
using namespace std;
using ll = long long;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const ll M = 991831889;
const ll C = uniform_int_distribution<ll>(0.1 * M, 0.9 * M)(rng);

struct HashTree {
    struct Hash {
        ll hash = 0;
        ll mul = 1;

        Hash operator+(Hash other) {
            return {(hash * other.mul + other.hash) % M, mul * other.mul % M};
        }
    };

    int n;
    vector<Hash> tree;

    HashTree(string s) {
        n = 1;
        while (n < s.size()) n *= 2;
        tree.resize(2 * n);
        for (int i = 0; i < s.size(); i++) {
            tree[n + i] = {s[i], C};
        }
        for (int i = n - 1; i >= 1; i--) {
            tree[i] = tree[2 * i] + tree[2 * i + 1];
        }
    }

    void set(int k, char x) {
        k += n;
        tree[k] = {x, C};
        for (k /= 2; k >= 1; k /= 2) {
            tree[k] = tree[2 * k] + tree[2 * k + 1];
        }
    }

    ll hash(int l, int r) {
        l += n;
        r += n;
        Hash left, right;
        while (l <= r) {
            if (l % 2 == 1) left = left + tree[l++];
            if (r % 2 == 0) right = tree[r--] + right;
            l /= 2;
            r /= 2;
        }
        return (left + right).hash;
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    string s;
    cin >> s;

    HashTree inc(s);
    reverse(s.begin(), s.end());
    HashTree dec(s);

    for (int mi = 1; mi <= m; mi++) {
        int t;
        cin >> t;
        if (t == 1) {
            int k;
            char x;
            cin >> k >> x;
            inc.set(k - 1, x);
            dec.set(n - k, x);
        } else {
            int a, b;
            cin >> a >> b;
            auto hash1 = inc.hash(a - 1, b - 1);
            auto hash2 = dec.hash(n - b, n - a);
            cout << (hash1 == hash2 ? "YES" : "NO") << "\n";
        }
    }
}
```