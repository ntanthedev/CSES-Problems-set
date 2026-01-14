# 1073 - Towers

We go through the cubes and maintain a multiset of towers. For each tower, we store the size of the topmost cube.

When we process a cube, we extend a tower whose topmost cube is larger than the new cube but as small as possible. If there is no tower we could extend, we create a new tower.

This is an optimal algorithm because if we would extend a tower whose topmost cube is larger or create a new tower instead of extending a tower, it would not allow us to create a smaller number of towers.

```cpp
#include <iostream>
#include <set>
using namespace std;

int main() {
    int n;
    cin >> n;
    multiset<int> towers;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        auto it = towers.upper_bound(x);
        if (it == towers.end()) {
            towers.insert(x);
        } else {
            towers.erase(it);
            towers.insert(x);
        }
    }
    cout << towers.size() << "\n";
}
```

We can also solve the problem just using a vector and binary search. The idea is to maintain an increasing sequence of towers and use binary search to find the tower that will be extended. The extension will never change the order of the towers.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> towers;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        if (towers.empty() || x >= towers.back()) {
            towers.push_back(x);
        } else {
            auto it = upper_bound(towers.begin(), towers.end(), x);
            *it = x;
        }
    }
    cout << towers.size() << "\n";
}
```