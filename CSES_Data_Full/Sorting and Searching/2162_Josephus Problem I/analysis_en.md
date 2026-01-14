# 2162 - Josephus Problem I

We create a vector that initially consists of numbers $1,2,\dots,n$. After that we go through the vector and simulate the problem. We add every second number at the end of the vector and print every second number.

We will process a total of $n+n/2+n/4+\dots = O(n)$ numbers, so the algorithm works in $O(n)$ time.

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> v;
    for (int i = 1; i <= n; i++) {
        v.push_back(i);
    }

    for (int i = 0; i < v.size(); i++) {
        if (i % 2 == 0) {
            v.push_back(v[i]);
        } else {
            cout << v[i] << " ";
        }
    }
    cout << "\n";
}
```

## References

* [Josephus problem (Wikipedia)](https://en.wikipedia.org/wiki/Josephus_problem)