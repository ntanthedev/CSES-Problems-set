# 1113 - String Transform

The transformation used in this problem is called the Burrows–Wheeler transform,
and it is used in compression algorithms.
More precisely, the problem asks us to efficiently calculate the inverse
transformation.

We can consider the sorted list of rotations as a grid, where each row
is a rotation. In the example input, the grid is as follows:

```cpp
#babc
abc#b
babc#
bc#ba
c#bab
```

We know the last column of the grid because it is our input string.
We can also easily derive the first column of the grid, as it
contains all the characters of the input string in sorted order.

Using the first and last columns, we can reconstruct the original string.
Since `#` is the smallest character,
the last character of the original string is the first character in the last column.
After that, we can discover the other characters step by step in reverse order.

The crucial observation is that if we have two rotations that begin with the
same character and we rotate both of them one step to the left, their lexicographic order
does not change. For example, rotation `babc#` is smaller than `bc#ba`,
and rotation `abc#b` is smaller than `c#bab`.

Using this property, we can associate each character in the last column with
another character in the first column, allowing us to move from one rotation
to the next after rotating the string one step to the right.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size();

    vector<pair<char, int>> chars;
    for (int i = 0; i < n; i++) {
        chars.emplace_back(s[i], i);
    }
    sort(chars.begin(), chars.end());

    vector<int> link(n);
    for (int i = 0; i < n; i++) {
        link[chars[i].second] = i;
    }

    int pos = 0;
    string res;
    for (int i = 0; i < n - 1; i++) {
        res += s[pos];
        pos = link[pos];
    }
    reverse(res.begin(), res.end());
    cout << res << "\n";
}
```

# References

* [Burrows–Wheeler transform](https://en.wikipedia.org/wiki/Burrows%E2%80%93Wheeler_transform) (Wikipedia)