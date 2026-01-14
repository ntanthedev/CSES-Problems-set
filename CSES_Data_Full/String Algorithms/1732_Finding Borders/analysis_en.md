# 1732 - Finding Borders

We discuss two ways to solve the problem in $O(n)$ time.

## Solution 1 (Z-algorithm)

Let us construct the Z-array for the string using the Z-algorithm. After that, we go through all suffixes of the string. If a suffix is also a prefix of the string, we have found a border. We can check that using the Z-array: a suffix at position $i$ is a border exactly when the array value is $n-i$.

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
    string s;
    cin >> s;
    int n = s.size();

    auto z = z_algo(s);
    for (int i = n - 1; i > 0; i--) {
        if (z[i] == n - i) {
            cout << n - i << " ";
        }
    }
    cout << "\n";
}
```

## Solution 2 (hashing)

We can also solve the problem using hashing. Since we can calculate the hash value of any substring in $O(1)$ time, we can just go through every prefix and check if it equals the suffix of the same length.

Warning: a code that uses hashing may fail due to collisions (two strings are different but have the same hash value).

```cpp
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

struct HashString {
    const ll A = 31;
    const ll B = 991831889;

    vector<ll> pows, sums;

    HashString(string s) {
        int n = s.size();
        pows.resize(n + 1);
        pows[0] = 1;
        sums.resize(n + 1);
        sums[0] = 0;
        for (int i = 1; i <= n; i++) {
            pows[i] = pows[i - 1] * A % B;
            sums[i] = (sums[i - 1] * A + s[i - 1]) % B;
        }
    }

    ll hash(int a, int b) {
        ll h = sums[b + 1] - sums[a] * pows[b - a + 1];
        return (h % B + B) % B;
    }
};

int main() {
    string s;
    cin >> s;
    int n = s.size();

    HashString h(s);
    for (int i = 0; i < n - 1; i++) {
        if (h.hash(0, i) == h.hash(n - i - 1, n - 1)) {
            cout << i + 1 << " ";
        }
    }
    cout << "\n";
}
```