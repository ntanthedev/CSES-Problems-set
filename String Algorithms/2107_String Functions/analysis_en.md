# 2107 - String Functions

We first calculate the $z$ values using the Z-algorithm. After that, we calculate the $\pi$ values using the $z$ values.

Observation 1: If $z(i)>0$, then $\pi(i+z(i)-1) \ge z(i)$, because a prefix of length $z(i)$ ends at position $i+z(i)-1$.

Observation 2: $\pi(i) \ge \pi(i+1)-1$, because if a prefix of length $\pi(i+1)$ ends at position $i+1$, then also a prefix of length $\pi(i+1)-1$ ends at position $i$.

The following code calculates the $\pi$ values in two phases. First we calculate the "peak" values of $\pi$ using Observation 1, and after that the remaining values using Observation 2. Note that 0-indexing is used in the code.

The code works in $O(n)$ time, because the Z-algorithm works in $O(n)$ time and the $\pi$ values are calculated using two linear loops.

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

    vector<int> z = z_algo(s);

    vector<int> p(n);
    for (int i = n - 1; i > 0; i--) {
        p[i + z[i] - 1] = z[i];
    }
    for (int i = n - 2; i > 0; i--) {
        p[i] = max(p[i], p[i + 1] - 1);
    }

    for (auto x : z) {
        cout << x << " ";
    }
    cout << "\n";

    for (auto x : p) {
        cout << x << " ";
    }
    cout << "\n";
}
```