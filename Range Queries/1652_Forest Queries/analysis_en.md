# 1652 - Forest Queries

This problem can be solved with a 2d prefix sum array.

Let $S(P)$ be the area from the top-left corner to the point $P$.
Now the answer to a query can be calculated with the formula
$S((x\_2,y\_2))-S((x\_2,y\_1))-S((x\_1,y\_2))+S((x\_1,y\_1))$.

![](4f086ef2cc9dabf5e98299464950e70760e0b903251c03539a488c698c9d2c3e)

Notice, how the ranges are half-open in the picture and in the implementation.
In the picture, this can be seen in that the coordinates $y\_2$ and $x\_2$ point to the
bottom of the square and right side of the square, respectively.

```cpp
#include <iostream>
using namespace std;

const int N = 1001;
int sums[N][N];

int main() {
    int n, q;
    cin >> n >> q;

    for (int i = 0; i < n; ++i) {
        string row;
        cin >> row;

        for (int j = 0; j < n; ++j) {
            sums[i + 1][j + 1] = sums[i + 1][j] + sums[i][j + 1] - sums[i][j];
            sums[i + 1][j + 1] += (row[j] == '*');
        }
    }

    for (int qi = 0; qi < q; ++qi) {
        int y1, x1, y2, x2;
        cin >> y1 >> x1 >> y2 >> x2;
        // Make the range 0-indexed and half-open.
        y1--;
        x1--;
        // We're querying the range [y1, y2) x [x1, x2).
        int ans = sums[y2][x2] - sums[y1][x2] - sums[y2][x1] + sums[y1][x1];
        cout << ans << '\n';
    }
}
```

## References

* [CPHB (Competitive Programmer's Handbook)](http://cses.fi/book), Chapter 9
* [Codeforces, *Video about prefix sums, difference array and the power of half-closed intervals* by peltorator](https://codeforces.com/blog/entry/88474)