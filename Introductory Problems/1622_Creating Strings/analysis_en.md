# 1622 - Creating Strings

The following code uses the C++ function `next_permutation` to generate all distinct permutations of a string in lexicographic order.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    string s;
    cin >> s;

    sort(s.begin(), s.end());
    vector<string> v;
    do {
        v.push_back(s);
    } while (next_permutation(s.begin(), s.end()));

    cout << v.size() << "\n";
    for (auto s : v) {
        cout << s << "\n";
    }
}
```