# 1641 - Sum of Three Values

Assume that we know that the leftmost value in the sum is $a\_i$. Then the remaining problem is to create the sum $x-a\_i$ using two distinct values in the subarray $a\_{i+1} \dots a\_n$, which is an easier problem.

Using this idea, we can go through all possible ways to choose $a\_i$ and solve the problem. However, we first sort the array so that we can solve the subproblem of choosing two values in $O(n)$ time using the two pointers technique. The resulting algorithm works in $O(n^2)$ time.

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

    for (int i = 0; i < n; i++) {
        int y = x - v[i].first;
        int a = i + 1;
        int b = n - 1;
        while (a < b) {
            int s = v[a].first + v[b].first;
            if (s == y) {
                cout << v[i].second << " ";
                cout << v[a].second << " ";
                cout << v[b].second << "\n";
                return 0;
            } else if (s > y) {
                b--;
            } else {
                a++;
            }
        }
    }
    cout << "IMPOSSIBLE\n";
}
```

This problem is called the 3SUM problem and it is an important problem because many other problems can be reduced to it. For a long time it was assumed that it would not be possible to solve 3SUM more efficiently than in $O(n^2)$ time, but in 2014 a better algorithm was found.

## References

* [3SUM (Wikipedia)](https://en.wikipedia.org/wiki/3SUM)
* King, J.: [A survey of 3SUM-hard problems](http://www.cs.mcgill.ca/~jking/papers/3sumhard.pdf) (2004)
* Grønlund, A., Pettie, S.: Threesomes, degenerates, and love triangles. IEEE 55th Annual Symposium on Foundations of Computer Science (2014) ([arXiv version](https://arxiv.org/abs/1404.0799))