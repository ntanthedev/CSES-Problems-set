# 1074 - Stick Lengths

In this problem we are given $n$ numbers $p\_1,p\_2,\dots,p\_n$ and our task is to find a value $x$ that minimizes the sum $|x-p\_1|+|x-p\_2|+\dots+|x-p\_n|$.

It turns out that the optimal solution is to select $x$ so that it is the median of the numbers $p\_1,p\_2,\dots,p\_n$. Why? Let us consider two cases:

Case 1: $n$ is odd and the median is $m$. If $x<m$ and we increase $x$ by one, the value of $|x-p\_i|$ increases by one when $p\_i \le x$ and decreases by one when $p\_i>x$. The latter holds for more than half of the numbers, so the total cost decreases. Similarly, if $x>m$ and we decrease $x$ by one, the total cost decreases. Thus, $x=m$ yields the minimum cost.

Case 2: $n$ is even and the medians are $m\_1$ and $m\_2$ (assume that $m\_1 \le m\_2$). If $x<m\_1$ or $x>m\_2$, we can use the same argument as in Case 1. Then, if $m\_1 \le x < m\_2$ and we increase $x$ by one, or $m\_1 < x \le m\_2$ and we decrease $x$ by one, the total cost remains the same. Thus, any value $m\_1 \le x \le m\_2$ yields the minimum cost.

The following code solves the problem in $O(n \log n)$ time by sorting the array, after which the median is the middle element.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

int main() {
    int n;
    cin >> n;

    vector<int> lengths(n);
    for (int i = 0; i < n; i++) {
        cin >> lengths[i];
    }

    sort(lengths.begin(), lengths.end());
    int target = lengths[n / 2];

    ll cost = 0;
    for (int i = 0; i < n; i++) {
        cost += abs(target - lengths[i]);
    }
    cout << cost << "\n";
}
```

We can also find the median more efficiently without sorting. The following code uses the C++ `nth_element` function which works in $O(n)$ time (on average or even in worst case, depending on the implementation).

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

int main() {
    int n;
    cin >> n;

    vector<int> lengths(n);
    for (int i = 0; i < n; i++) {
        cin >> lengths[i];
    }

    nth_element(lengths.begin(), lengths.begin() + n / 2, lengths.end());
    int target = lengths[n / 2];

    ll cost = 0;
    for (int i = 0; i < n; i++) {
        cost += abs(target - lengths[i]);
    }
    cout << cost << "\n";
}
```

## References

* [Selection algorithm (Wikipedia)](https://en.wikipedia.org/wiki/Selection_algorithm)