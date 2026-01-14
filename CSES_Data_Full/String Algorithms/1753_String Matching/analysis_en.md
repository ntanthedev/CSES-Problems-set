# 1753 - String Matching

We are given a string $s$ of length $n$ and a pattern $p$ of length $m$, and we
want to count the number of times $p$ appears in $s$.

We discuss two ways to solve the problem in $O(n+m)$ time.

## Solution 1 (Z-algorithm)

One way to solve the problem is to use the Z-algorithm. Given a string, the
algorithm constructs a Z-array that contains, for each suffix of the string, the
maximum length of a prefix that is also a prefix of the entire string. The
Z-algorithm works in linear time.

We create a new string $p\$s$ and construct its Z-array using the Z-algorithm.
After that, we go through the array and find the positions that have value $m$.
Each such position corresponds to an occurrence of $p$ in $s$.

```cpp
#include <iostream>
#include <vector>
using namespace std;

vector<int> z_algo(string s) {
    int n = s.size();
    vector<int> z(n);
    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        z[i] = max(0, min(z[i - l], r - i));
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }
    return z;
}

int main() {
    string s, p;
    cin >> s;
    int n = s.size();
    cin >> p;
    int m = p.size();

    string t = p + "$" + s;
    auto z = z_algo(t);
    int count = 0;
    for (int i = 0; i < n + m + 1; i++) {
        if (z[i] == m) count++;
    }
    cout << count << "\n";
}
```

## Solution 2 (hashing)

Another way to solve the problem is to use hashing. After preprocessing a
string, we can calculate the hash value of any substring on $O(1)$ time. Thus,
we can check all positions where the pattern can appear and compare the hash
values.

Warning: a code that uses hashing may fail due to collisions (two strings are
different but have the same hash value).

It is possible to deliberately find an input which causes a hashing solution to
break. Some care has been taken to protect the solution from that. The
coefficient used in the polynomial rolling hash algorithm is selected at random
and the random number generator uses the amount of *ticks* since
[epoch](https://en.wikipedia.org/wiki/Epoch_(computing)) as its seed.

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
    string s, p;
    cin >> s;
    int n = s.size();
    cin >> p;
    int m = p.size();

    HashString h(s);
    ll target = HashString(p).hash(0, m);

    int count = 0;
    for (int i = 0; i < n - m + 1; i++) {
        if (h.hash(i, i + m) == target) {
            count++;
        }
    }
    cout << count << "\n";
}
```

### References

* [Wikipedia, Polynomial rolling hash](https://en.wikipedia.org/wiki/Rolling_hash#Polynomial_rolling_hash)