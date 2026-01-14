# 3225 - Inverse Suffix Array

We can use a greedy algorithm for constructing a string that corresponds to the
suffix array.

We go through the suffix array from left to right.
Let $\textrm{sa}[i]$ denote the $i$th suffix array value.
For $i=1,2,\dots,n$, we assign the smallest possible character
to the string position $\textrm{sa}[i]$.

Assume we want to assign a character to position $\textrm{sa}[i]$
and we have already assigned a character $x$ to position $\textrm{sa}[i-1]$.
If the suffix starting at position $\textrm{sa}[i-1]+1$ is smaller
than the suffix starting at position $\textrm{sa}[i]+1$,
we assign character $x$ to position $\textrm{sa}[i]$.
Otherwise we assign character $x+1$ to position $\textrm{sa}[i]$.

If we run out of characters, it is not possible to construct the string.

Note that this algorithm creates the lexicographically minimal string
that corresponds to the suffix array.

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> suffix_array(n + 1);
    vector<int> order(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> suffix_array[i];
        order[suffix_array[i]] = i;
    }

    vector<char> result(n + 1);
    result[suffix_array[1]] = 'a';
    char current_char = 'a';
    for (int i = 2; i <= n; i++) {
        if (order[suffix_array[i - 1] + 1] > order[suffix_array[i] + 1]) {
            current_char++;
        }
        if (current_char > 'z') {
            cout << "-1\n";
            return 0;
        }
        result[suffix_array[i]] = current_char;
    }

    for (int i = 1; i <= n; i++) {
        cout << result[i];
    }
    cout << "\n";
}
```