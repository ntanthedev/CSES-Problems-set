# 3406 - Triangle Number Sums

It can be shown that any positive integer can be represented as a sum of at most three triangle numbers. Thus, the answer is always $1$, $2$ or $3$.

First, we precalculate a list of all triangle numbers between $1 \dots 10^{12}$. The list contains about $1.4 \cdot 10^6$ numbers.

The answer is $1$ if the list contains $n$. Otherwise, the answer is $2$ if the list contains two numbers $a$ and $b$ that sum to $n$, which can be checked using a two-pointer approach. Otherwise, we know that the answer is $3$.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

int main() {
    int t;
    cin >> t;

    vector<ll> triangles;
    ll triangle = 0;
    for (int i = 1;; i++) {
        triangle += i;
        if (triangle > 1e12) break;
        triangles.push_back(triangle);
    }

    while (t--) {
        ll n;
        cin >> n;

        if (find(triangles.begin(), triangles.end(), n) != triangles.end()) {
            cout << "1\n";
            continue;
        }

        bool found = false;

        int right = triangles.size() - 1;
        for (int left = 0; left <= right; left++) {
            while (right > 0 && triangles[left] + triangles[right] > n) {
                right--;
            }
            if (triangles[left] + triangles[right] == n) {
                cout << "2\n";
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "3\n";
        }
    }
}
```

## References

* [Fermat polygonal number theorem](https://en.wikipedia.org/wiki/Fermat_polygonal_number_theorem)