# 1692 - De Bruijn Sequence

It turns out that we can always create a string that contains each distinct
substring of length $n$ exactly once. The length of such a string is $2^n + n - 1$.

This problem can be solved by constructing a directed graph where each node
corresponds to a substring of length $n-1$ and each edge contains the next character
to be added to the string. An Euler path in this graph corresponds to an optimal
De Bruijn sequence.

However, there is an easier way to construct the string.
The following code constructs the string using recursive backtracking.
Each substring of length $n$ is stored as a bitmask of $n$ bits.
This approach works very fast for $1 \le n \le 15$.

```cpp
#include <iostream>
#include <vector>
using namespace std;

vector<int> result;
vector<int> seen;

void search(int pos, int part, int n) {
    if (pos == (1 << n) + n - 1) {
        for (int i = 0; i < pos; i++) {
            cout << result[i];
        }
        cout << "\n";
        exit(0);
    }

    part = (part << 1) & ((1 << n) - 1);

    for (int i = 0; i < 2; i++) {
        if (!seen[part]) {
            seen[part] = true;
            result[pos] = i;
            search(pos + 1, part, n);
            seen[part] = false;
        }
        part++;
    }
}

int main() {
    int n;
    cin >> n;

    seen.resize(1 << n);
    seen[0] = true;

    result.resize((1 << n) + n - 1);
    search(n, 0, n);
}
```

## References

* [CPHB (Competitive Programmer's Handbook)](https://cses.fi/book), Chapter 19