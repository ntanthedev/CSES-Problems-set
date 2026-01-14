# 1621 - Distinct Numbers

One way to solve the problem is to add the numbers to a set and then print the size of the set:

```cpp
#include <iostream>
#include <set>
using namespace std;

int main() {
    int n;
    cin >> n;
    set<int> s;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        s.insert(x);
    }
    cout << s.size() << "\n";
}
```

Another approach is to sort the numbers after which equal numbers are next to each other. The C++ function `unique` can then be used to select the first element of each group of equal elements.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    sort(v.begin(), v.end());
    auto pos = unique(v.begin(), v.end());
    cout << pos - v.begin() << "\n";
}
```