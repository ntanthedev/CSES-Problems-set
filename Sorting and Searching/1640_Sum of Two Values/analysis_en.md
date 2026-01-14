# 1640 - Sum of Two Values

One way to solve the problem is to go through the array and use a map structure to store the index of each value. When the current value is $a$, we can check if we have already seen a value $x-a$, in which case we have found a solution.

```cpp
#include <iostream>
#include <map>
using namespace std;

int main() {
    int n, x;
    cin >> n >> x;
    map<int, int> m;
    for (int i = 1; i <= n; i++) {
        int a;  
        cin >> a;
        if (m[x - a]) {
            cout << m[x - a] << " " << i << "\n";
            return 0;
        }
        m[a] = i;
    }
    cout << "IMPOSSIBLE\n";
}
```

Another approach is to create a vector of pairs where each element has a value and its index in the array. Then, after sorting the vector, we can solve the problem using the two pointers technique.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, x;
    cin >> n >> x;

    vector<pair<int, int>> v;
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        v.emplace_back(a, i);
    }
    sort(v.begin(), v.end());

    int i = 0;
    int j = n - 1;
    while (i < j) {
        int s = v[i].first + v[j].first;
        if (s == x) {
            cout << v[i].second << " " << v[j].second << "\n";
            return 0;
        } else if (s > x) {
            j--;
        } else {
            i++;
        }
    }
    cout << "IMPOSSIBLE\n";
}
```