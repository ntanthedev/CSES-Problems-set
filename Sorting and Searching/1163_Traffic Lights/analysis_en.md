# 1163 - Traffic Lights

We maintain a set that has all positions of lights and a multiset that has all passage lengths between two lights.

First we add two dummy lights with positions $0$ and $x$ that will make the implementation easier, and a single passage whose length is $x$. Then we update the data structures after adding each new light. This can be done by finding the next and previous light for the new light and updating passage lengths.

```cpp
#include <iostream>
#include <set>
using namespace std;

int main() {
    int x, n;
    cin >> x >> n;

    set<int> lights;
    multiset<int> lengths;
    lights.insert(0);
    lights.insert(x);
    lengths.insert(x);

    for (int i = 1; i <= n; i++) {
        int p;
        cin >> p;
        auto it2 = lights.upper_bound(p);
        auto it1 = it2;
        it1--;
        lights.insert(p);
        lengths.erase(lengths.find(*it2 - *it1));
        lengths.insert(p - *it1);
        lengths.insert(*it2 - p);
        cout << *lengths.rbegin() << " ";
    }
    cout << "\n";
}
```