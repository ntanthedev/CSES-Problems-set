# 1731 - Word Combinations

## Solution 1 (trie)

We create a trie that contains all words in the dictionary. The root node of the
trie has index $0$, and `trie`$[i][x]$ points to a node we will move from node
$i$ after reading letter $x$. In addition, `final`$[i]$ is true if some word
ends at node $i$.

We use dynamic programming to count the combinations. We create an array `ways`
that stores, for each suffix of the string, the number of ways to create the
suffix using the dictionary. We go through each prefix of the suffix and follow
the links in the trie to find the prefixes that are in the dictionary.

The algorithm works in $O(n^2+N)$ time where $N$ is the total length of the
words in the dictionary.

```cpp
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

const int N = 1000000;
const int M = 1000000007;

int trie[N + 1][26];
int trie_pos;
bool final[N + 1];

int main() {
    string s;
    cin >> s;
    int n = s.size();

    int k;
    cin >> k;
    while (k--) {
        string w;
        cin >> w;
        int node = 0;
        for (auto c : w) {
            int idx = c - 'a';
            if (trie[node][idx] == 0) {
                trie[node][idx] = ++trie_pos;
            }
            node = trie[node][idx];
        }
        final[node] = true;
    }

    vector<ll> ways(n + 1);
    ways[n] = 1;
    for (int i = n - 1; i >= 0; i--) {
        ways[i] = 0;
        int node = 0;
        for (int j = i; j < n; j++) {
            node = trie[node][s[j] - 'a'];
            if (node == 0) break;
            if (final[node]) {
                ways[i] += ways[j + 1];
                ways[i] %= M;
            }
        }
    }

    cout << ways[0] << "\n";
}
```

## Solution 2 (hashing)

We create a set `hashes` that contains all hashes of the words in the
dictionary. Then, we can use dynamic programming to calculate the answer like in
the previous solution and use the set to check if a substring belongs to the
dictionary.

Since we compare each substring with all words, we need 64-bit hash values to
make sure there will be no collisions, due to the birthday paradox.

To make the solution more efficient, we use an additional trick: we create a
vector `lengths` which is used to check if the dictionary contains at least
one word with a given length. Using this vector, we don't have to check if a
substring appears in the dictionary if we know that there are no words of that
length in the dictionary. Since the total length of the words is at most $10^6$,
there will be only about $\sqrt{2 \cdot 10^6} \approx 1414$ distinct word
lengths, compared to $5000$ possible substring lengths.

The solution works in $O((n^2+k) C+N)$ time where $C$ denotes the time needed
for set operations and $N$ is the total length of the words.

```cpp
#include <chrono>
#include <iostream>
#include <random>
#include <unordered_set>
#include <vector>
using namespace std;
using ll = long long;

const int M = 1000000007;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const ll Z = 1111111111111111111;  // Z is a prime.
const ll C = uniform_int_distribution<ll>(Z / 10, Z / 10 * 9)(rng);

struct HashString {
    ll mul(ll a, ll b) { return __int128(a) * b % Z; }

    int n;
    vector<ll> pows, sums;

    HashString(string s) : n(s.size()), pows(n + 1, 1), sums(n + 1) {
        for (int i = 1; i <= n; i++) {
            pows[i] = mul(pows[i - 1], C);
            sums[i] = (mul(sums[i - 1], C) + s[i - 1]) % Z;
        }
    }

    // Returns the hash of the substring [l, r)
    ll hash(int l, int r) {
        ll h = sums[r] - mul(sums[l], pows[r - l]);
        return (h % Z + Z) % Z;
    }
};

int main() {
    string s;
    cin >> s;
    int n = s.size();
    HashString hs(s);
    int k;
    cin >> k;

    unordered_set<ll> hashes;
    vector<bool> lengths(n + 1);
    for (int i = 1; i <= k; i++) {
        string w;
        cin >> w;
        HashString hw(w);
        hashes.insert(hw.hash(0, w.size()));
        lengths[w.size()] = true;
    }

    vector<ll> ways(n + 1);
    ways[n] = 1;
    for (int i = n - 1; i >= 0; i--) {
        for (int j = i + 1; j <= n; j++) {
            if (lengths[j - i] && hashes.count(hs.hash(i, j))) {
                ways[i] += ways[j];
                ways[i] %= M;
            }
        }
    }

    cout << ways[0] << "\n";
}
```