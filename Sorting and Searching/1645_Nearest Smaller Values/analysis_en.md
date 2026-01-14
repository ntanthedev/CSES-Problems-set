# 1645 - Nearest Smaller Values

The idea is to create a stack that has an increasing sequence of array values. We go through the array and, for each value $x$, remove all values from the stack that are not smaller than $x$. After that, either the topmost value of the stack is the nearest smaller value, or the stack is empty and there is no nearest smaller value. Finally, we add $x$ to the stack.

The algorithm works in $O(n)$ time, because we add and remove each array value at most once.

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<pair<int, int>> stack;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        while (!stack.empty() && stack.back().first >= x) {
            stack.pop_back();
        }
        if (!stack.empty()) {
            cout << stack.back().second << " ";
        } else {
            cout << 0 << " ";
        }
        stack.emplace_back(x, i);
    }
    cout << "\n";
}
```

## References

* [All nearest smaller values (Wikipedia)](https://en.wikipedia.org/wiki/All_nearest_smaller_values)